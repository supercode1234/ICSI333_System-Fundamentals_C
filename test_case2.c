//
// Created by Haolin Wang on 1/4/25.
//
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "project1.c" // Include your project code

void testIEEE754Representation() {
    // Structure to hold expected results
    struct TestCase {
        float input;           // Input float number
        char signBit;          // Expected sign bit (0 or 1)
        char exponent[9];      // Expected 8-bit exponent
        char mantissa[24];     // Expected 23-bit mantissa (plus hidden bit)
    };

    // Define test cases
    struct TestCase testCases[] = {
        {2.0, '0', "10000000", "00000000000000000000000"}, // Simple positive integer
        {-2.0, '1', "10000000", "00000000000000000000000"}, // Negative integer
        {0.5, '0', "01111110", "00000000000000000000000"}, // Fractional number
        {4.0, '0', "10000001", "00000000000000000000000"}, // Larger integer
        {123.45, '0', "10000101", "11101101100110011001100"}, // Mixed integer and fractional
        {-0.1, '1', "01111011", "10011001100110011001101"}, // Small negative fractional
        {0.0, '0', "00000000", "00000000000000000000000"}, // Zero case
        {INFINITY, '0', "11111111", "00000000000000000000000"}, // Positive infinity
        {-INFINITY, '1', "11111111", "00000000000000000000000"}, // Negative infinity
        {NAN, '0', "11111111", "10000000000000000000000"} // NaN
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTests; i++) {
        struct TestCase tc = testCases[i];

        printf("Testing input: %f\n", tc.input);

        // Run your functions to generate IEEE-754 components
        int signBit = getSignBit(tc.input);
        int exponentBinary[8];
        int bitCount = 0;
        int unbiasedExp;
        if (tc.input != 0.0) {
            unbiasedExp = (tc.input >= 1.0) ? (int)log2(fabs(tc.input)) : (int)(-1 * ceil(-log2(fabs(tc.input))));
            calculateExponent(unbiasedExp, exponentBinary, &bitCount);
        } else {
            for (int j = 0; j < 8; j++) exponentBinary[j] = 0; // Zero exponent
        }

        char mantissaBinary[23] = {0};
        if (tc.input != 0.0 && !isinf(tc.input) && !isnan(tc.input)) {
            int integerBinary[32], fractionBinary[55];
            int integerBitCount = 0, fractionBitCount = 0;

            int integerPart = (int)fabs(tc.input);
            float fractionalPart = fabs(tc.input) - integerPart;

            convertIntegerToBinary(integerPart, integerBinary, &integerBitCount);
            convertFractionToBinary(fractionalPart, fractionBinary, 55);

            generateMantissa(integerBinary, integerBitCount, fractionBinary, fractionBitCount, mantissaBinary);
        }

        // Verify the sign bit
        assert(signBit == (tc.signBit - '0'));

        // Verify the exponent
        char actualExponent[9] = {0};
        for (int j = 0; j < 8; j++) {
            actualExponent[j] = exponentBinary[j] + '0'; // Convert int to char
        }
        actualExponent[8] = '\0';
        assert(strcmp(actualExponent, tc.exponent) == 0);

        // Verify the mantissa
        char actualMantissa[24] = {0};
        for (int j = 0; j < 23; j++) {
            actualMantissa[j] = mantissaBinary[j] + '0'; // Convert int to char
        }
        actualMantissa[23] = '\0';
        assert(strcmp(actualMantissa, tc.mantissa) == 0);

        printf("Test passed for input: %f\n", tc.input);
    }

    printf("All rigorous tests passed!\n");
}

int main() {
    testIEEE754Representation();
    return 0;
}
