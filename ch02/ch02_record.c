/*
 * Name:    ch02_record.c
 * Purpose: Report for chapter 2 of K. N. King, "C Programming: A Modern Approach".
 *          Exercises 1-2, 4-10 and programming projects 2-7.
 *          Only chapter 2 tools are used: printf, scanf, int, float,
 *          #define / const and + - * / (no if, no loops, no %).
 * Author:  Nord
 *
 * Not included:
 *   PP1 (picture of stars)  - plain printf, no new ideas.
 *   Exercise 3 (dweight.c)  - a mechanical edit of an existing program.
 *   PP8 (loan balance)      - same arithmetic as the sections below;
 *                             revisit it with loops in chapter 6.
 *
 * Build:
 *   gcc -std=c17 -Wall -Wextra -Wpedantic -Og -g \
 *       -fsanitize=address,undefined ch02_record.c -o record
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
 *
 * Exercise 2 (Parkinson's Law):
 *   (a) One directive: #include <stdio.h>.
 *       Four statements: three printf calls and return 0;
 *   (b) Output:
 *         Parkinson's Law:
 *         Work expands so as to fill the time
 *         available for its completion.
 *       The first printf ends without \n, so the second one continues
 *       the same line. Line breaks come from \n, not from separate calls.
 *
 * Exercise 5 (legal identifiers):
 *   (a) 100_bottles             - ILLEGAL: cannot start with a digit.
 *   (b) _100_bottles            - legal, but a bad idea: names starting
 *       with an underscore are reserved for the implementation
 *       (compiler and standard library), so they may clash.
 *   (c) one__hundred__bottles   - legal (see exercise 6).
 *   (d) bottles_by_the_hundred_ - legal; a trailing underscore is fine.
 *
 * Exercise 6 (adjacent underscores):
 *   current__balance and current___balance look identical on screen,
 *   so they are easy to confuse and to mistype. A double underscore is
 *   also reserved for the implementation.
 *
 * Exercise 7 (keywords):
 *   Keywords: for, while.
 *   If     - not a keyword: C is case-sensitive, the keyword is "if".
 *   main   - an ordinary identifier, not a keyword.
 *   printf - an ordinary identifier too (a library function name).
 *   Checked: "int printf;" inside a function compiles - it just hides
 *   the library function, so it can no longer be called.
 *
 * Exercise 8 (tokens in answer=(3*q-p*p)/3;):
 *   14 tokens:  answer  =  (  3  *  q  -  p  *  p  )  /  3  ;
 *
 * Exercise 9 (same statement, readable):
 *   answer = (3 * q - p * p) / 3;
 *
 * Exercise 10 (essential spaces in dweight.c):
 *   Only the spaces that keep two tokens apart, i.e. between a keyword
 *   or a type and an identifier: "int height", "return 0".
 *   Without them "intheight" would be a single token.
 *   Spaces around operators, parentheses and commas are optional -
 *   the compiler splits a+b into three tokens anyway - they only help
 *   a human reader.
 */
 
#include <stdio.h>
 
int main( void )
{
    /* scanf returns the number of values it managed to read.
       Here the returns are only summed up and reported at the end.
       TODO (ch05): check every call and the range of the value with if. */
    int scanf_items_read = 0;
 
 
    /* === Section 1: Sphere (PP2 + PP3) === */
 
    printf( "=== Sphere ===\n" );
 
    /* const, not #define: the value is only needed during the calculation,
       never as a compile-time constant (array size, case label, #if). */
    const float pi = 3.14159f;
 
    float radius = 0.0f;
 
    printf( "Enter radius (m): " );
    scanf_items_read += scanf( "%f", &radius );
 
    float volume_int   = 4 / 3 * pi * ( radius * radius * radius );
    float volume_float = 4.0f / 3.0f * pi * ( radius * radius * radius );
 
    printf( "Integer division: %f\n", volume_int );
    printf( "Float division:   %f\n", volume_float );
 
    /*
     * The type of an operation is decided by its two operands only, and
     * * and / are evaluated left to right, so 4 / 3 is int / int = 1:
     * the fractional part is gone before pi and radius are even touched.
     * 4.0f / 3.0f is float / float = 1.33333, nothing is lost.
     * What matters is the ORDER of the operations, not how many floats
     * the expression contains: pi * r * r * r * 4 / 3 is correct too,
     * because by the time / 3 runs, the left operand is already a float.
     */
 
 
    /* === Section 2: Tax (PP4 + money in whole cents) === */
 
    printf( "=== Tax ===\n" );
 
    const int tax_percent = 5;
 
    float amount = 0.0f;
 
    printf( "Enter an amount ($): " );
    scanf_items_read += scanf( "%f", &amount );
 
    /* Float version, the one the book asks for.
       100.0f would be int / int = 0, hence 100.0f. */
    float taxed_amount = amount * ( 1 + tax_percent / 100.0f );
 
    printf( "Float version: With tax added: $%.2f\n", taxed_amount );
 
    /* Converting to cents WITHOUT rounding: shows the problem. */
    int raw_cents = amount * 100;
 
    printf( "Cents (raw):   %d\n", raw_cents );
 
    /* +0.5f turns truncation into rounding to the nearest integer.
       Valid only for amount >= 0. */
    int cents = amount * 100 + 0.5f;
 
    printf( "Cents (fixed): %d\n", cents );
 
    /* Integers only from here on. Multiply first, then divide.
       +50 is half of the divisor: rounds to the nearest cent. */
    int tax_cents   = ( cents * tax_percent + 50 ) / 100;
    int total_cents = cents + tax_cents;
 
    /* Dollars and cents are split only for printing.
       %02d pads with a leading zero, so 5 cents prints as .05 */
    int total_dollars_part = total_cents / 100;
    int total_cents_part   = total_cents - total_dollars_part * 100;
 
    printf( "Cents version: With tax added: $%d.%02d\n",
            total_dollars_part, total_cents_part );
 
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
     *    Adding 0.5f before the conversion rounds to the nearest integer.
     *
     * 2. 2.10 and 0.10: the exact result is exactly half a cent
     *    (2.205 and 0.105). In binary these values are not exact, and
     *    float stores them slightly below (2.20499969...). %.2f rounds
     *    the STORED value correctly, so it goes down. The error comes
     *    from storage, not from rounding.
     *    In the cents version integers are exact: 210 * 5 = 1050, and
     *    +50 rounds half a cent up.
     *
     * 3. 1000000.01 has 9 significant digits, float keeps about 7.
     *    The cent is lost already in scanf("%f"), before any calculation,
     *    so the cents version cannot restore it.
     *    Fix: read dollars and cents as integers (chapter 3).
     */
 
 
    /* === Section 3: Bills (PP7) === */
    /* Reads its own amount instead of reusing the total of section 2,
       so that a mistake in the tax does not propagate here. */
 
    printf( "=== Bills ===\n" );
 
    float bills_amount = 0.0f;
 
    printf( "Enter amount ($): " );
    scanf_items_read += scanf( "%f", &bills_amount );
 
    int bills_cents   = bills_amount * 100 + 0.5f;
    int bills_dollars = bills_cents / 100;
    int coins         = bills_cents - bills_dollars * 100;
 
    /* Take as many $20 bills as possible, then subtract their value
       and repeat with the next denomination. Integers only, no %. */
    int bill_20 = bills_dollars / 20;
    int remaining = bills_dollars - bill_20 * 20;
 
    int bill_10 = remaining / 10;
    remaining = remaining - bill_10 * 10;
 
    int bill_5 = remaining / 5;
    remaining = remaining - bill_5 * 5;
 
    int bill_1 = remaining;   /* whatever is left goes in $1 bills */
 
    printf( "$20 bills: %d\n", bill_20 );
    printf( "$10 bills: %d\n", bill_10 );
    printf( " $5 bills: %d\n", bill_5 );
    printf( " $1 bills: %d\n", bill_1 );
    printf( "Coins: $0.%02d\n", coins );
 
    /* Checked against the book: 93.47 -> 4 / 1 / 0 / 3 and $0.47 */
 
 
    /* === Section 4: Polynomial (PP5 + PP6) === */
 
    printf( "=== Polynomial ===\n" );
 
    float x = 0.0f;
 
    printf( "Enter x: " );
    scanf_items_read += scanf( "%f", &x );
 
    /* Direct method. C has no exponentiation operator, so the powers
       are built step by step to avoid repeating x * x * x * x * x. */
    float x2 = x * x;
    float x3 = x2 * x;
    float x4 = x3 * x;
    float x5 = x4 * x;
 
    float y_direct = 3.0f * x5 + 2.0f * x4 - 5.0f * x3 - x2 + 7.0f * x - 6.0f;
 
    /* Horner's rule: the same polynomial, no powers of x needed. */
    float y_horner = ( ( ( ( 3.0f * x + 2.0f ) * x - 5.0f ) * x - 1.0f ) * x + 7.0f ) * x - 6.0f;
 
    float diff = y_horner - y_direct;
 
    /* %g prints only the significant digits instead of 20 meaningless ones */
    printf( "Direct method:   %g\n", y_direct );
    printf( "Horner's method: %g\n", y_horner );
    printf( "Difference:      %g\n", diff );
 
    /*
     * Operation count (as written above):
     *   Direct:  8 multiplications (4 for the powers + 4 for the
     *            coefficients), 5 additions/subtractions.
     *   Horner:  5 multiplications, 5 additions/subtractions.
     *   Horner needs no powers of x at all, which is why it is cheaper.
     *   On an MCU without an FPU every float multiplication is a software
     *   routine, so the difference is real, not cosmetic.
     *
     * Results:
     *   x = 1.1      direct 1.594730      Horner 1.594731      diff  4.77e-07
     *                exact  1.5947300
     *   x = 100      direct 30194991104   Horner 30194989056   diff -2048
     *                exact  30194990694
     *   x = 10000    both   3.0002e+20                         diff  0
     *
     * Why the results differ:
     *   float keeps about 7 significant digits, so its RELATIVE error stays
     *   roughly constant while the ABSOLUTE error grows with the magnitude
     *   of the number. At x = 100 the gap between neighbouring float values
     *   is already 2048, and the two results are exactly one such step apart:
     *   both are correctly rounded, they simply round differently because the
     *   operations are performed in a different order.
     *
     *   At x = 10000 the difference is 0, but that is not accuracy. The term
     *   3*x^5 is about 3e20, where neighbouring floats are ~3.5e13 apart, so
     *   the smaller terms (-1e8, +7e4, -6) are below the resolution and are
     *   lost entirely. Both methods end up computing essentially 3*x^5.
     */
 
 
    printf( "scanf calls read %d value(s) in total (4 expected)\n",
            scanf_items_read );
 
    return 0;
}
 
 
/* === Exercise 4: uninitialized variables === */
/* Kept switched off with #if 0 so that the report builds without warnings.
   Comments do not nest, #if 0 does - that is why it is used here.
   Set it to #if 1 and move the block inside main to repeat the experiment. */
#if 0
    int   i1, i2, i3;
    float f1, f2, f3;
 
    printf( "=== Uninitialized (exercise 4) ===\n" );
    printf( "ints:   %d %d %d\n", i1, i2, i3 );
    printf( "floats: %f %f %f\n", f1, f2, f3 );
#endif
 
/*
 * Exercise 4 results (gcc, x86-64, Ubuntu):
 *   -O0  ints: -575616272 29642 -769955696   floats: 0.0 -1.67e11 0.0
 *   -Og  ints: 0 0 0                         floats: 0.0 0.0 0.0
 *   -O2  ints: 0 0 0                         floats: 0.0 0.0 0.0
 *
 * No pattern. At -O0 the values are leftovers on the stack from earlier
 * calls; some of them happen to look like a valid 0, which is exactly why
 * "it printed 0" proves nothing.
 * At -Og/-O2 everything is 0: reading an uninitialized variable is
 * undefined behaviour, so the compiler is free to skip the storage
 * altogether. The bug becomes INVISIBLE with optimization enabled - more
 * dangerous than the garbage at -O0.
 *
 * gcc warns at every level here (-Wuninitialized): the variables are used
 * without ever being written, which needs no data-flow analysis.
 * ASan/UBSan do NOT catch this - valgrind or clang's MemorySanitizer do.
 *
 * Lesson: always initialize.
 */