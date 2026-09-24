/*
    Name:    addfrac.c
    Purpose: King ch. 3, exercise 6 and PP6: reading fractions with
             scanf("%d/%d"). Shows how ordinary characters and spaces
             in the format string are matched against the input, and
             what stays in the buffer when matching fails.
             Part A - book version, sentinel -999 marks unwritten variables.
             Part B - exercise 6: spaces allowed around '/'.
             Part C - PP6: two fractions in one input, "a/b+c/d".
    Author:  Nord
*/

#include <stdio.h>

int main(void)

{

    /* Exercise 6 + PP6 */

    /* === A part === */
    printf( "=== A part ===\n" );

    int num1 = -999; /* To indicate clear absence of a value assigned to the variable */
    int denom1 = -999;
    int num2 = -999;
    int denom2 = -999;

    /* Input part */

    printf( "Enter first fraction: " );
    int input_read_1 = scanf( "%d/%d", &num1, &denom1 );
    printf( "scanf #1 read %d\n", input_read_1 );

    printf( "Enter second fraction: " );
    int input_read_2 = scanf( "%d/%d", &num2, &denom2 );
    printf( "scanf #2 read %d\n", input_read_2 );

    /* Output part */

    printf( "num1 = %d, denom1 = %d, num2 = %d, denom2 = %d\n", num1, denom1, num2, denom2 );
    
    int denom = denom1 * denom2;
    int num = num1 * denom2 + num2 * denom1;
    
    printf( "The sum is %d/%d\n", num, denom );




    /* === B part === */
    printf( "=== B part ===\n" );

    int num3 = -999;
    int denom3 = -999;
    int num4 = -999;
    int denom4 = -999;

    /* Input part */

    printf( "Enter first fraction: " );
    int input_read_3 = scanf( "%d /%d", &num3, &denom3 );
    printf( "scanf #3 read %d\n", input_read_3 );

    printf( "Enter second fraction: " );
    int input_read_4 = scanf( "%d /%d", &num4, &denom4 );
    printf( "scanf #4 read %d\n", input_read_4 );

    /* Output part */

    printf( "num3 = %d, denom3 = %d, num4 = %d, denom4 = %d\n", num3, denom3, num4, denom4 );
    
    int sum_num_b = num3 * denom4 + num4 * denom3;
    int sum_denom_b = denom3 * denom4;
    
    printf( "The sum is %d/%d\n", sum_num_b, sum_denom_b );

 


    /* === C part === */
    printf( "=== C part ===\n" );

    int num5 = -999;
    int denom5 = -999;
    int num6 = -999;
    int denom6 = -999;

    /* Input part */

    printf( "Enter two fractions separated by a plus sign: " );
    int input_read_5 = scanf( "%d/%d +%d/%d", &num5, &denom5, &num6, &denom6 );
    printf( "scanf #5 read %d\n", input_read_5 );

    /* Output part */

    printf( "num5 = %d, denom5 = %d, num6 = %d, denom6 = %d\n", num5, denom5, num6, denom6 );
    
    int sum_num_c = num5 * denom6 + num6 * denom5;
    int sum_denom_c = denom5 * denom6;
    
    printf( "The sum is %d/%d\n", sum_num_c, sum_denom_c );

    return 0;

}