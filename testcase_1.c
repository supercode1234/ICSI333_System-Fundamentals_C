//
// Created by Haolin Wang on 1/4/25.
//
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "project1.c" // Include your main project file

void testGetSignBit() {
    // Test positive numbers
    assert(getSignBit(123.0) == 0);
    assert(getSignBit(0.1) == 0);

    // Test negative numbers
    assert(getSignBit(-45.0) == 1);
    assert(getSignBit(-0.001) == 1);

    // Test zero
    assert(getSignBit(0.0) == 0);

    printf("testGetSignBit passed.\n");
}

void testConvertIntegerToBinary() {
    int binaryArray[32];
    int bitCount;

    // Test integer 1
    convertIntegerToBinary(1, binaryArray, &bitCount);
    assert(bitCount == 1); // Binary: 1
    assert(binaryArray[0] == 1);

    // Test integer 5
    convertIntegerToBinary(5, binaryArray, &bitCount);
    assert(bitCount == 3); // Binary: 101
    assert(binaryArray[0] == 1 && binaryArray[1] == 0 && binaryArray[2] == 1);

    // Test integer 123
    convertIntegerToBinary(123, binaryArray, &bitCount);
    assert(bitCount == 7); // Binary: 1111011
    assert(binaryArray[0] == 1 && binaryArray[1] == 1 && binaryArray[6] == 1);

    // Test large integer
    convertIntegerToBinary(1023, binaryArray, &bitCount);
    assert(bitCount == 10); // Binary: 1111111111
    assert(binaryArray[0] == 1 && binaryArray[9] == 1);

    // Test very large integer
    convertIntegerToBinary(2147483647, binaryArray, &bitCount); // Max 32-bit integer
    assert(bitCount == 31); // Binary: all 1s
    printf("testConvertIntegerToBinary passed.\n");
}

void testConvertFractionToBinary() {
    char binaryArray[55];
    int maxBits = 55;

    // Test fractional part 0.5
    int bitCount = convertFractionToBinary(0.5, binaryArray, maxBits);
    assert(bitCount == 1); // Binary: 1
    assert(binaryArray[0] == 1);

    // Test fractional part 0.25
    bitCount = convertFractionToBinary(0.25, binaryArray, maxBits);
    assert(bitCount == 2); // Binary: 01
    assert(binaryArray[0] == 0 && binaryArray[1] == 1);

    // Test fractional part 0.125
    bitCount = convertFractionToBinary(0.125, binaryArray, maxBits);
    assert(bitCount == 3); // Binary: 001
    assert(binaryArray[0] == 0 && binaryArray[2] == 1);

    // Test fractional part 0.1 (non-terminating in binary)
    bitCount = convertFractionToBinary(0.1, binaryArray, maxBits);
    assert(bitCount > 0); // Should produce a repeating binary fraction
    printf("testConvertFractionToBinary passed.\n");
}

void testCalculateExponent() {
    int exponentBinary[8];
    int bitCount;

    // Test unbiased exponent 4
    calculateExponent(4, exponentBinary, &bitCount);
    assert(bitCount == 8); // Exponent: 131 -> 10000011
    assert(exponentBinary[0] == 1 && exponentBinary[7] == 1);

    // Test unbiased exponent -2
    calculateExponent(-2, exponentBinary, &bitCount);
    assert(bitCount == 8); // Exponent: 125 -> 01111101
    assert(exponentBinary[0] == 0 && exponentBinary[7] == 1);

    printf("testCalculateExponent passed.\n");
}

void testIntegration() {
    // Integrate functions for a complete example: Convert 123.45 to IEEE-754
    int binaryArray[32], bitCount;
    char fractionArray[55];
    int fractionBitCount;

    // Sign bit
    int signBit = getSignBit(123.45);
    assert(signBit == 0); // Positive number

    // Integer part
    convertIntegerToBinary(123, binaryArray, &bitCount);
    assert(bitCount == 7); // Binary: 1111011

    // Fractional part
    fractionBitCount = convertFractionToBinary(0.45, fractionArray, 55);
    assert(fractionBitCount > 0); // Should produce a binary fraction

    // Exponent
    int exponentBinary[8];
    calculateExponent(bitCount - 1, exponentBinary, &bitCount);
    assert(bitCount == 8);

    printf("testIntegration passed.\n");
}

int main() {
    testGetSignBit();
    testConvertIntegerToBinary();
    testConvertFractionToBinary();
    testCalculateExponent();
    testIntegration();

    printf("All tests passed!\n");
    return 0;
}
