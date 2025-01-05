//
// Created by Haolin Wang on 1/4/25.
//
/**
 * Program: Float to IEEE-754 Single-Precision Representation
 * Author: Haolin Wang
 * Description:
 * This program takes a floating-point number as input and computes its IEEE-754 single-precision (32-bit) representation.
 * It outputs the sign bit, exponent, and mantissa as per the standard.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EXPONENT_BIAS 127
#define MANTISSA_BITS 23
#define MAX_FRACTION_BITS 55

// function to convert an integer to binary
void convertIntegerToBinary(int inputInt, int *binaryArray, int *bitCount){
  int bitIndex = 0;
  while (inputInt > 0) {
    binaryArray[bitIndex++] = inputInt % 2;
    inputInt /= 2;
  }
  *bitCount = bitIndex;

  // Reverse the array to store MSB-first
  for (int i = 0; i < *bitCount / 2; i++) {
    int temp = binaryArray[i];
    binaryArray[i] = binaryArray[*bitCount - i - 1];
    binaryArray[*bitCount - i - 1] = temp;
  }

  // Print the binary representation
  printf("Binary (integer part): ");
  for (int i = 0; i < *bitCount; i++) {
    printf("%d", binaryArray[i]);
  }
  printf("\n");


  // printf("Binary (integer part): ");
  // for (int i = *bitCount - 1; i >= 0; i--){
  //   printf("%d", binaryArray[i]);
  // }
  // printf("\n");

}

// function to convert a fractional part to binary
int convertFractionToBinary(float fractionalPart, char *binaryArray, int maxBits) {
  int index = 0;
  while (fractionalPart > 0 && index < maxBits) {
    fractionalPart *= 2;
    binaryArray[index++] = (int) fractionalPart;
    fractionalPart -= (int)fractionalPart;
  }
  // print the binary representation
  printf("Binary (fractional part): ");
  for (int i = 0; i < index; i++) {
    printf("%d", binaryArray[i]);
  }
  printf("\n");
  return index;
}


// function to calculate the biased exponent
void calculateExponent (int unbiasedExp, int *expBinary, int *bitCount) {
  int biasedExp = EXPONENT_BIAS + unbiasedExp;
  int bitIndex = 0;

  while (biasedExp > 0) {
    expBinary[bitIndex++] = biasedExp % 2;
    biasedExp /= 2;
  }
  *bitCount = bitIndex;
  // pad with zeros to ensure 8 bits
  while (*bitCount < 8) {
    expBinary[(*bitCount)++] = 0;
  }

  // rever the array to make it MSB-first
  for (int i = 0; i < *bitCount/2; i++) {
    int temp = expBinary[i];
    expBinary[i] = expBinary[*bitCount - 1 - i];
    expBinary[*bitCount - 1 - i] = temp;
  }
  // Print the exponent
  printf("Exponent: (biased): ");
  for (int i = 0; i < *bitCount; i++) {
    printf("%d", expBinary[i]);
  }

  // for (int i = *bitCount - 1; i >= 0; i--) {
  //   printf("%d", expBinary[i]);
  // }
  printf("\n");
}


// function to generate the mantissa
void generateMantissa(int *integerBinary, int intBitCount, char *fractionBinary, int fracBitCount, int *mantissaArray) {
  int mantissaIndex = 0;

  // add binary digits from the integer part (excluding leading 1)
  if (intBitCount > 1) {
    for (int i = 1; i < intBitCount; i++) { // Skip the first bit (leading 1)
      mantissaArray[mantissaIndex++] = integerBinary[i];
    }
  // for (int i = intBitCount -2; i >= 0; i--) {
  //   mantissaArray [mantissaIndex++] = integerBinary[i];
  // }
  }

  // add binary digits from the fractional part
  for (int i = 0; i < fracBitCount && mantissaIndex < MANTISSA_BITS; i++) {
    mantissaArray [mantissaIndex++] = fractionBinary[i];
  }

  // pad with zeros if necessary
  while (mantissaIndex < MANTISSA_BITS) {
    mantissaArray [mantissaIndex++] = 0;
  }

  // print the mantissa
  printf("Mantissa: ");
  for (int i = 0; i < MANTISSA_BITS; i++) {
    printf("%d", mantissaArray[i]);
  }
  printf("\n");
}


// get the sign bit
int getSignBit(float input){
  return (input < 0) ? 1 : 0;
}

/*
// main function
int main() {
  float userInput;

  // Get user input
  printf("Enter a floating-point number: ");
  if (scanf("%f", &userInput) != 1) {
    printf("Invalid input. Please try again.\n");
    return 1;
  }

  // Handle zero case
  if (userInput == 0) {
    printf("Sign: 0\nExponent: 0000000\nMantissa: 00000000000000000000000\n");
    return 0;
  }

  // Determine sign bit
  int signBit = getSignBit (userInput);
  printf("Sign Bit: %d\n", signBit);

  // Work with absolute value
  float absInput = fabs(userInput);
  int integerPart = (int) absInput;
  float fractionalPart = absInput - integerPart;


  // Convert integer part to binary
  int integerBinary [32], intBitCount = 0;
  if (integerPart > 0 ) {
    convertIntegerToBinary (integerPart, integerBinary, &intBitCount);
  }

  // Convert fractional part to binary
  char fractionBinary [MAX_FRACTION_BITS];
  int fracBitCount = convertFractionToBinary(fractionalPart, fractionBinary, MAX_FRACTION_BITS);

  // Calculate the unbiased exponent
  int unbiasedExp = (integerPart > 0) ? intBitCount - 1 : (fracBitCount - 1);

  // Calculate the biased exponent
  int exponentBinary[8], expBitCount = 0;
  calculateExponent (unbiasedExp, exponentBinary, &expBitCount);



  // Generate the mantissa
  int mantissaArray [MANTISSA_BITS];
  generateMantissa (integerBinary, intBitCount, fractionBinary, fracBitCount, mantissaArray);


  return 0;

 }
*/