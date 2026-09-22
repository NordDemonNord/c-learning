/*
    Name: ch02_record.c
    Purpose: improve skills, learned in chapter 02
    Author: Nord
*/

#include <stdio.h>

int main( void )
{
    
    /* === Section 1: Sphere (PP2 + PP3) === */

    const float pi = 3.14159f; /* Use const instead of #define, because this variable is needed in calculations, not in arrays*/

    float radius = 0.0f;

    printf( "Enter radius(m): " );
    scanf( "%f", &radius );

    float volume_1 = 4 / 3 * pi * ( radius * radius * radius ); /* Calculating volume, using int division*/
    float volume_2 = 4.0f / 3.0f * pi * ( radius * radius * radius ); /* Do the same, using float division*/

    printf( "=== Sphere ===\n" );

    printf( "Integer division: %f\nFloat division: %f\n", volume_1, volume_2 );
    /*  In first output we get inncorrect answer, because the fractional part is discarded,
        in the second output we get correct answer, because we divide two floats, so we do not lose the fractional part
    */
    


    /* === Section 2: Tax (PP4) === */
    printf( "===Tax===\n" );

    const int tax = 5;

    float amount = 0.00f;

    /* Enter and print amount in float */

    printf( "Enter an amount($): " );
    scanf( "%f", &amount );

    float taxed_amount = amount * ( 1 + ( tax / 100.0f ) ); /* Calculating tax added amount */

    printf( "Float version: With tax added: $%.2f\n", taxed_amount ); /* Printing tax added amount */

    /* Conversion to raw cents */
    
    int raw_cents = amount * 100; /* Convert dollars to cents by multiplication */

    printf( "Cents(raw): %d\n", raw_cents );

    /* Conversion to fixed cents */

    int fixed_cents = amount * 100 + 0.5f; /* Convert dollars to cents by +0.5f: round to nearest instead of truncating (valid for amount ≥ 0) */

    printf( "Cents(fixed): %d\n", fixed_cents );

    /* Calculating taxes from fixed cents */

    int tax_fixed_cents = ( fixed_cents * tax + 50 ) / 100; /* Calculating taxes with +50 = half of the divisor: round to nearest cent */
    int total_fixed_cents = fixed_cents + tax_fixed_cents;
    printf( "Cents(fixed): tax added: %d\n", total_fixed_cents );

    /* === Printing results === */

    /* Fixed cents */

    int fixed_dollars = total_fixed_cents / 100;
    int cents_fixed = total_fixed_cents - fixed_dollars * 100;

    printf( "Cents version(fixed): With tax added: $%d.%02d\n", fixed_dollars, cents_fixed );

    return 0;
}