/*
    Name: printf_formats.c
    Purpose: King ch. 3, exercises 1-2: printf conversion specifications (%-m.pX)
    Author: Nord
*/

#include <stdio.h>

int main(void)
{

    /* A part (exercise) */

    printf("[%6d,%4d]\n", 86, 1040);          /* (a) */
    printf("[%12.5e]\n", 30.253);             /* (b) */
    printf("[%.4f]\n", 83.162);               /* (c) */
    printf("[%-6.2g]\n", .0000009979);        /* (d) */




    /* B part */ 

    float x = 0.0f;

    printf( "Enter x: " );
    int items_read = scanf( "%f", &x ); /* x is printed below in four formats */
    printf( "scanf read %d items\n", items_read );

    printf( "[%-8.1e]\n", x ); /* a */
    printf( "[%10.6e]\n", x); /* b */
    printf( "[%-8.3f]\n", x ); /* c */
    printf( "[%6.0f]\n", x ); /* d */

   /* Predictions and results: printf_formats.md */
    
    return 0;

}