//
// Created by Haolin Wang on 1/4/25.
//
#include <assert.h>
#include <stdio.h>
#include "project1.c" // Include your main program functions

void testGetSignBit() {
    assert(getSignBit(123.0) == 0); // Positive number
    assert(getSignBit(-45.0) == 1); // Negative number
    assert(getSignBit(0.0) == 0);   // Zero
    printf("testGetSignBit passed.\n");
}

void testConvertIntegerToBinary() {
    int binaryArray[32];
    int bitCount;

    // Test integer 5
    convertIntegerToBinary(5, binaryArray, &bitCount);
    assert(bitCount == 3); // Binary: 101
    assert(binaryArray[0] == 1 && binaryArray[1] == 0 && binaryArray[2] == 1);

    // Test integer 123
    convertIntegerToBinary(123, binaryArray, &bitCount);
    assert(bitCount == 7); // Binary: 1111011
    printf("testConvertIntegerToBinary passed.\n");
}

int main() {
    testGetSignBit();
    testConvertIntegerToBinary();

    printf("All tests passed!\n");
    return 0;
}
