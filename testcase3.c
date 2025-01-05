//
// Created by Haolin Wang on 1/4/25.
//
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "project1.c" // Include the main program's functions for testing

void testGetSignBit() {
    assert(getSignBit(123.45) == 0);  // Positive number
    assert(getSignBit(-123.45) == 1); // Negative number
    assert(getSignBit(0.0) == 0);     // Zero
    printf("testGetSignBit passed.\n");
}

void testConvertIntegerToBinary() {
    int binaryArray[32];
    int bitCount;

    // Test 1: Integer 2
    convertIntegerToBinary(2, binaryArray, &bitCount);
    assert(bitCount == 2); // Binary: 10
    assert(binaryArray[0] == 1 && binaryArray[1] == 0);

    // Test 2: Integer 123
    convertIntegerToBinary(123, binaryArray, &bitCount);
    assert(bitCount == 7); // Binary: 1111011
    assert(binaryArray[0] == 1 && binaryArray[6] == 1);

    printf("testConvertIntegerToBinary passed.\n");
}

void testConvertFractionToBinary() {
    char binaryArray[MAX_FRACTION_BITS];

    // Test 1: Fractional part 0.5
    int bitCount = convertFractionToBinary(0.5, binaryArray, MAX_FRACTION_BITS);
    assert(bitCount == 1); // Binary: 1
    assert(binaryArray[0] == 1);

    // Test 2: Fractional part 0.25
    bitCount = convertFractionToBinary(0.25, binaryArray, MAX_FRACTION_BITS);
    assert(bitCount == 2); // Binary: 01
    assert(binaryArray[0] == 0 && binaryArray[1] == 1);

    printf("testConvertFractionToBinary passed.\n");
}

void testCalculateExponent() {
    int expBinary[8];
    int bitCount;

    // Test 1: Exponent for 2.0 (unbiased = 1, biased = 128)
    calculateExponent(1, expBinary, &bitCount);
    assert(bitCount == 8); // Exponent: 10000000
    int expected1[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) assert(expBinary[i] == expected1[i]);

    // Test 2: Exponent for 0.5 (unbiased = -1, biased = 126)
    calculateExponent(-1, expBinary, &bitCount);
    assert(bitCount == 8); // Exponent: 01111110
    int expected2[8] = {0, 1, 1, 1, 1, 1, 1, 0};
    for (int i = 0; i < 8; i++) assert(expBinary[i] == expected2[i]);

    printf("testCalculateExponent passed.\n");
}

void testGenerateMantissa() {
    int integerBinary[32] = {1, 1, 1, 1, 0, 1, 1}; // Binary of 123
    int intBitCount = 7;

    char fractionBinary[MAX_FRACTION_BITS] = {0};
    int fracBitCount = 0;

    int mantissaArray[MANTISSA_BITS];

    // Test: Mantissa for 123.0
    generateMantissa(integerBinary, intBitCount, fractionBinary, fracBitCount, mantissaArray);
    int expectedMantissa[MANTISSA_BITS] = {
        1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < MANTISSA_BITS; i++) assert(mantissaArray[i] == expectedMantissa[i]);

    printf("testGenerateMantissa passed.\n");
}

void testIntegration() {
    // Full IEEE-754 conversion for 123.45
    float input = 123.45;
    int signBit = getSignBit(input);
    assert(signBit == 0);

    // Integer and fractional parts
    int integerBinary[32];
    int intBitCount = 0;
    convertIntegerToBinary((int)fabs(input), integerBinary, &intBitCount);

    char fractionBinary[MAX_FRACTION_BITS];
    int fracBitCount = convertFractionToBinary(fabs(input) - (int)fabs(input), fractionBinary, MAX_FRACTION_BITS);

    // Exponent
    int unbiasedExp = intBitCount - 1;
    int expBinary[8];
    int expBitCount = 0;
    calculateExponent(unbiasedExp, expBinary, &expBitCount);

    // Mantissa
    int mantissaArray[MANTISSA_BITS];
    generateMantissa(integerBinary, intBitCount, fractionBinary, fracBitCount, mantissaArray);

    // Verify full IEEE-754 output
    assert(signBit == 0); // Sign bit
    int expectedExp[8] = {1, 0, 0, 0, 0, 1, 0, 1}; // Exponent for 123.45
    for (int i = 0; i < 8; i++) assert(expBinary[i] == expectedExp[i]);
    int expectedMantissa[MANTISSA_BITS] = {
        1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0};
    for (int i = 0; i < MANTISSA_BITS; i++) assert(mantissaArray[i] == expectedMantissa[i]);

    printf("testIntegration passed.\n");
}

int main() {
    testGetSignBit();
    testConvertIntegerToBinary();
    testConvertFractionToBinary();
    testCalculateExponent();
    testGenerateMantissa();
    testIntegration();

    printf("All tests passed!\n");
    return 0;
}
