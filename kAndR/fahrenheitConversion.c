#include <stdio.h>

#define LOWER  0
#define UPPER  300
#define STEP  20

/*
print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300
*/

int main()
{
    // int fahr, celsius;
    float fahr, celsius;
    int lower, upper, step;

    lower = 0; // lower limit of temperature table
    upper = 300; // upper limit
    step = 20; // step size

    fahr = lower;
    printf("Temperature conversion table for Fahrenheit to Celsius\n");
    while (fahr <= upper) {
        // celsius = 5 * (fahr - 32) / 9;
        celsius = (5.0/9.0) * (fahr-32.0);
        // printf("%3d\t%6d\n", fahr, celsius);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    // The reverse
    celsius = lower;
    printf("\nTemperature conversion table for Celsius to Fahrenheit\n");
    while (celsius <= upper) {
        fahr = (9.0/5.0) * celsius + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

    // for version
    int fahr2 = 0;
    printf("\nTemperature conversion with a for\n");
    for (fahr2 = 0; fahr2 <= 300; fahr2 = fahr2 + 20)
        printf("%3d %6.1f\n", fahr2, (5.0/9.0)*(fahr2-32));


    // reverse
    printf("\nReversed (from 300)\n");
    for (fahr2 = 300; fahr2 >= 0; fahr2 = fahr2 - 20)
        printf("%3d %6.1f\n", fahr2, (5.0/9.0)*(fahr2-32));

    // using symbolic constants
    printf("\nUsing symbolic constants");

    for (fahr2 = LOWER; fahr2 <= UPPER; fahr2 += STEP) 
        printf("%3d %6.1f\n", fahr2, (5.0/9.0)*(fahr2-32));
    
}