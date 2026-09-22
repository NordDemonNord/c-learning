/*
    Name: ch02_record.c
    Purpose: improve skills, learned in chapter 02
    Author: Nord
*/

/*
 * === THEORY ===
 *
 * Exercise 1 (hello, world without return 0):
 *   -std=c89: warning "control reaches end of non-void function".
 *     main returns int, but reaches } without return, so the exit
 *     status is undefined. Experiment: echo $? printed 39 = the value
 *     printf returned (number of characters), left in the return
 *     register (eax on x86-64). This is a coincidence, not a rule.
 *   -std=c99 and later: special rule ONLY for main: reaching its
 *     closing } is equivalent to return 0. No warning, echo $? = 0.
 *   Fix for any standard: write return 0; explicitly.
 */

#include <stdio.h>

int main( void )
{
    
    /* === Section 1: Sphere (PP2 + PP3) === */
    printf( "Enter radius(m): " );

    const float pi = 3.14159f; /* Use const instead of #define, because this variable is needed in calculations, not in arrays*/

    float radius = 0.0f;

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

    int fixed_cents = amount * 100 + 0.5f; /* Convert dollars to cents by +0.5f: round to nearest instead of truncating (valid for amount >= 0) */

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

        /*
     * Results (tax = 5%, half a cent rounds up):
     *
     *   input         float version    cents version    correct
     *   100.00        $105.00          $105.00          $105.00
     *   19.99         $20.99           $20.99           $20.99
     *   1.05          $1.10            $1.10            $1.10    (raw cents: 104)
     *   2.10          $2.20            $2.21            $2.21    (raw cents: 209)
     *   0.10          $0.10            $0.11            $0.11
     *   1000000.01    $1050000.00      $1050000.00      $1050000.01
     *
     * 1. Raw cents: float stores most decimal fractions inexactly
     *    (1.05f = 1.0499999...). amount * 100 gives 104.99999...,
     *    and conversion to int truncates it to 104.
     *    Adding 0.5f before conversion turns truncation into rounding
     *    to the nearest integer. Valid only for amount >= 0.
     *
     * 2. 2.10 and 0.10: the exact result is exactly half a cent
     *    (2.205 and 0.105). In binary these values are not exact, and
     *    float stores them slightly below (2.20499969...). %.2f rounds
     *    the STORED value correctly, so it goes down. The error comes
     *    from storage, not from rounding.
     *    In the cents version integers are exact: 210 * 5 = 1050, and
     *    +50 (half of the divisor 100) rounds half a cent up.
     *
     * 3. 1000000.01 has 9 significant digits, float keeps about 7.
     *    The cent is lost already in scanf("%f"), before any calculation,
     *    so the cents version cannot restore it.
     *    Fix: read dollars and cents as integers (chapter 3).
     */

    return 0;
}