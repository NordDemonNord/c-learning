/*
 * Name:    fw_update.c
 * Purpose: Estimate firmware update parameters for a UART bootloader:
 *          1. Flash pages the firmware occupies (a partial page counts as full).
 *          2. Unused bytes left in the last page.
 *          3. Number of 64-byte packets (an incomplete packet counts as a packet).
 *          4. Bytes in the last, incomplete packet.
 *          5. UART throughput in bytes per second.
 *          6. Transfer time in milliseconds, rounded up.
 * Author:  Nord
 */

#include <stdio.h>  /* header with declarations of I/O functions (printf) */

int main(void)      /* definition of main: program entry point, returns int status */
{
    /* Input data. const = value is fixed at declaration and cannot be changed.
       Try 44900 as firmware size to test the rounding. */
    const int firmware_size_bytes = 45000;
    const int page_size_bytes     = 2048;
    const int packet_size_bytes   = 64;
    const int uart_baud           = 115200;  /* UART: 1 baud = 1 bit per second */
    const int bits_per_frame      = 10;      /* 8N1 frame: start + 8 data + stop */

    /* Integer division truncates (rounds down). Adding (divisor - 1)
       turns it into rounding UP: (a + b - 1) / b. Valid for a >= 0. */
    int pages_firmware = (firmware_size_bytes + (page_size_bytes - 1)) / page_size_bytes;

    /* Space of all occupied pages minus the actual firmware size */
    int last_page_unused_bytes = (pages_firmware * page_size_bytes) - firmware_size_bytes;

    /* Same rounding-up technique as for pages */
    int packets_for_firmware = (firmware_size_bytes + (packet_size_bytes - 1)) / packet_size_bytes;

    /* Full packet size minus the "empty tail" of the last packet */
    int last_packet_size_bytes = packet_size_bytes
                               - ((packets_for_firmware * packet_size_bytes) - firmware_size_bytes);

    /* Each byte costs bits_per_frame bits on the line, not 8 */
    int uart_speed_bytes_per_sec = uart_baud / bits_per_frame;

    /* Multiply BEFORE dividing: dividing first would drop everything below
       one second. Rounded up with the same (a + b - 1) / b technique.
       Note: the intermediate value (~45 000 000) fits a 32-bit int,
       but would overflow a 16-bit int (max 32767). */
    int time_transfer_firmware_ms =
        (firmware_size_bytes * 1000 + (uart_speed_bytes_per_sec - 1)) / uart_speed_bytes_per_sec;

    /* %d = placeholder for an int argument, \n = newline */
    printf("Firmware size: %d bytes\n", firmware_size_bytes);
    printf("Flash pages needed: %d\n", pages_firmware);
    printf("Unused bytes in last page: %d\n", last_page_unused_bytes);
    printf("Packets: %d\n", packets_for_firmware);
    printf("Bytes in last packet: %d\n", last_packet_size_bytes);
    printf("UART speed: %d bytes/s\n", uart_speed_bytes_per_sec);
    printf("Transfer time: %d ms\n", time_transfer_firmware_ms);

    return 0;       /* 0 = success status for the operating system */
}