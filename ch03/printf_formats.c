/*
    Name: printf_formats.c
    Purpose: improve skills from ch03
    Author: Nord
*/

#include <stdio.h>

int main(void)
{

    printf("[%6d,%4d]\n", 86, 1040);          /* (a) */
    printf("[%12.5e]\n", 30.253);             /* (b) */
    printf("[%.4f]\n", 83.162);               /* (c) */
    printf("[%-6.2g]\n", .0000009979);        /* (d) */
    printf("[%6d,%4d]\n", 86, 1040);        /* (e) */

    /*  Program results
        [    86,1040]
        [ 3.02530e+01]
        [83.1620]
        [1e-06 ]
        [    86,1040]
   
    */

    /* My predictions
        [____86,1040]   
        [_3.02530e+001]
        [83.1620]       
        [9979.0]        
        [____86,1040] 

    */
    
    return 0;

}