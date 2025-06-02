#include "computor.h"
#include <stdio.h>

// Function to compute the Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Convert float to irreducible fraction
void print_irreducible_fraction(float num) {
    const int precision = 1000000; // Increase for more precision
    int numerator = (int)(num * precision);
    int denominator = precision;

    int divisor = gcd(numerator, denominator);

    numerator /= divisor;
    denominator /= divisor;

    // If denominator is 1, it's a whole number
    if (denominator == 1)
        printf("The irreducible fraction is: %d\n", numerator);
    else
        printf("The irreducible fraction is: %d/%d\n", numerator, denominator);
}
