/**
*  main.c
*  p1_lib
* Program: Float to IEEE-754 Single-Precision Representation
*
* This program takes a floating-point number as input
* and manually computes the sign bit, exponent, and
* mantissa (fraction) bits as specified by the IEEE-754
* single-precision (32-bit) standard.
*
* This is a revision on Dec 21, 2024
* Course: ICSI333. System Fundamentals,Spring 2023,
*
* Author: Haolin Wang
* NetID: HW479779
*  Created by Haolin Wang on 3/18/23.
* TA: Manasa Nannuru

*
*/

#include <stdio.h>
#include <math.h> // for fabs, etc.
#include <stdlib.h>

#define EXPONENT_BIAS 127

// Function to convert an integer to binary
void convertIntegerToBinary (int inputInt, int *binaryArray, int *bitCount) {
    int bitIndex = 0, quotient, remainder;
    do {
        quotient = inputInt / 2;
        remainder = inputInt % 2;
        binaryArray[bitIndex++] = remainder;
        inputInt = quotient;
    } while (quotient != 0);

    *bitCount = bitIndex;

    printf("binary version of user input: ");
    for (int binaryIndex = *bitCount-1; binaryIndex>=0; binaryIndex--) {
        printf("%d", binaryArray[binaryIndex]);
    }
    printf("\n");

}
void calculateExponentForFraction(float fractionPart, int *exponentArray) {

}
int convertFractionToBinary(float fractionalPart, char *binaryArray, int maxBits) {
    int index = 0;
    while (fractionalPart != 0 && index < maxBits) {
        fractionalPart *= 2; // shift left
        binaryArray[index++] = (int)fractionalPart; // store the integer part
        if (fractionalPart >= 1) {
            fractionalPart -= (int)fractionalPart; // remove integer part for next calculation
        }
    }
    printf("binary version of user input: ");
    for (int binaryIndex = 0; binaryIndex < index; binaryIndex++) {
        printf("%d", binaryArray[binaryIndex]);
    }
    printf("\n");
    return index;

}

// Function to calculate the biased exponent
void calculateExponent (int unbiasedExp, int *expBinary, int *bitCount) {
    int biasedExp = EXPONENT_BIAS + unbiasedExp;
    int i = 0, j=0,quotient, remainder;
    do {
        quotient = biasedExp / 2;
        //printf("quotient = %d\n", quotient);
        remainder = biasedExp % 2;
        //printf("remainder = %d\n", remainder);
        expBinary[i++] = remainder;
        //printf("remainder %d\n", remainder);
        biasedExp = quotient;
    } while (quotient != 0);

    *bitCount = i;

    while (*bitCount < 8) { // pad to 8 bits
        expBinary [(*bitCount)++] = 0;
    }
    printf("Exponent: ");
    // print in reverse order of array
    for (int j = *bitCount-1;j>=0;j--) {
        printf("%d", expBinary[j]);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}


// Function to generate the mantissa
void generateMantissa (int signBit, int *binaryArray, int integerBitCount, int *mantissaArray) {
    mantissaArray[0] = signBit;
    printf("Sign: %d\n", signBit);

    // copy binary digits of the integer part
    int mantissaIndex = 1; // start filling from index 1, skips leading bit
    for (int binaryIndex = integerBitCount - 2; binaryIndex >= 0; binaryIndex--){
        mantissaArray[mantissaIndex++]=binaryArray[binaryIndex];
    }


    // pad with zeros to fill 23 bits
    while (mantissaIndex<=23){
        mantissaArray[mantissaIndex++]=0;
    }

    printf("Mantissa (24 bit): ");
    mantissaIndex=0;
    while (mantissaIndex<=23){
        printf("%d", mantissaArray[mantissaIndex]);
        mantissaIndex++;
    }
    printf("\n");
    printf("Digit count is: %d\n", mantissaIndex);
}

// Get the sign bit
int getSignBit (float input) {
    return (input <0)? 1:0;
}

// Main function
int main(int argc, const char * argv[]) {
    float userInput;

    // Get input
    printf("Input a real number: ");
    if (scanf("%f", &userInput) != 1) {
        printf("Invalid input. Please enter a valid number.\n ");
        return 1;
    }

    // Handle zero case
    if (userInput == 0.0f) {
        printf("Everything is 0\n");
        printf("Sign: 0\n");
        printf("Exponent: 00000000\n");
        printf("Mantissa (24 bit): 000000000000000000000000\n");
        return 0;
    }


    // Extract sign bit
    int signBit = getSignBit(userInput);
    printf("Sign Bit: %d\n", signBit);

    // Work with absolute value of input
    float absInput = fabs(userInput);

    int i = 0, integerBitCount = 0, fractionlBitCount=0, quotient=0, remainder,
    exponent = 0, exponentBitCount = 0, countExp = 0;
    int binaryD[40];

    int binaryInteger[32], binaryFraction[55], mantissa[23];
    float inputManti = 0;

    printf("Input is: %f\n", userInput);
    int integerPart = (int)absInput;
    float fractionalPart = absInput - integerPart;
    int exponentBinary[8];



    // Convert integer part to binary
    if (integerPart > 0) {
        convertIntegerToBinary(integerPart, binaryInteger, &integerBitCount);
    }

    // Convert fractional part to binary
    if (fractionalPart > 0) {
        int fractionalBitCount = convertFractionToBinary(fractionalPart, binaryFraction, 55);
    }





    /* When user input is an integer */
    if(userInput == (int) userInput  && userInput!=0) {

        // Determine sign, convert negative to positive for ease of calculation
        if(userInput<0) integerPart = -integerPart;

        // Convert integer to binary
        convertIntegerToBinary(integerPart, binaryInteger, &integerBitCount);

        // Generating Mantissa
        generateMantissa(signBit, binaryInteger, integerBitCount, mantissa);


        // get the unbiased exponent
        int unbiasedExponent = integerBitCount-1;

        // calculate biased exponent (binary form)
        calculateExponent(unbiasedExponent, exponentBinary, &exponentBitCount);


    }/* End of Integer */




    /* 0.[non-zero] */
    else if ((int)userInput - userInput != 0 && (int)userInput == 0){
        int mantissaBitCount=0;


        if(userInput<0) userInput = absInput;

        char binaryFraction[40]; // Array to hold fractional binary digits
        int index = 0;

        printf("Input is %f\n", userInput);

        // Convert fractional part to binary
        while (fractionalPart != 0 && index <55){
            fractionalPart *= 2; // calculation
            binaryFraction[index++]=(int)fractionalPart; // store integer part
            if(fractionalPart>=1){
                fractionalPart -= (int)fractionalPart; // Remove integr part
            }
        }
        printf("Binary Fraction: ");
        for (int j=0;j<index;j++) {
            printf("%d", binaryFraction[j]);
        }
        printf("\n");

        int fractionalBitCount = index;

        // Find position of the first '1' in the fractional binary
        int leadingOneIndex = 0;
        while(binaryFraction[leadingOneIndex]!=1 && leadingOneIndex<fractionalBitCount){
            leadingOneIndex++;
        }


        // Generate Sign Bit
        if(userInput>=0){
            printf("Sign: 0\n");
        } else {
            printf("Sign: 1\n");
        }




        // mantissa
        printf("Mantissa (24 bit): ");
        printf("leadingOneIndex: %d\n", leadingOneIndex);
        mantissaBitCount=0;
        for (int i = leadingOneIndex+1; mantissaBitCount < 23; i++, mantissaBitCount++){
            if (i < fractionalBitCount) {
                printf("%d", binaryFraction[i]);fflush(stdout);
            } else {
                printf("0"); // pad with zero if fractional binary is shorter
            }

            //printf("mantissaBitCount: %d\n", mantissaBitCount);
        }

        printf("\n");fflush(stdout);
        printf("Mantissa bits: %d\n", mantissaBitCount);

        // exponent
        //int exp = 0;
        int unbiasedExponent = -(leadingOneIndex +1);
        int exponentBinary[8] = {0}; // array to store the 8-bit binary expression
        exponentBitCount = 0;
        printf("leadingOneIndex: %d\n", leadingOneIndex);
        printf("biased Exponent: %d\n", unbiasedExponent);

        // generate the binary representation of exponent
        calculateExponent(unbiasedExponent, exponentBinary, &exponentBitCount);

    } /* End of 0.[non-zero] */



    /* [non-zero].[non-zero]*/
    else {
        i=0;
        printf("Input: %f\n", userInput);
        if (userInput<0)
            integerPart = userInput*-1;
        else
            integerPart = (int)userInput;

        // call method to convert the int part to bin
        convertIntegerToBinary(integerPart, binaryInteger, &integerBitCount);

        // print the bin version of the int part
        printf("binary (integer): ");
        for (int i=integerBitCount-1; i>=0; i--) {
            printf("%d", binaryInteger[i]);
        }
        printf("\n");



        char binary[60]; int b_i=0;
        for (i=integerBitCount-1;i>=0;i--){
            binary[b_i]=binaryInteger[i];
            b_i++;
        }


        // converting post decimal part
        userInput=userInput-(int)userInput;
        if(userInput<0)
            userInput=(userInput*-1)-((int)userInput*-1);
        else
            userInput=userInput-(int)userInput;
        inputManti=userInput;
        char binaryD[40];
        i=0;
        while (userInput-(int)userInput != 0 && i<50){
            userInput = userInput*2;
            binaryD[i]=(int)userInput;
            if(userInput>1){
                userInput=userInput-(int)userInput;
            }
            i++;
        }
        binaryD[39]='a';
        fractionlBitCount=0;
        while(binaryD[fractionlBitCount]!='a'){
            fractionlBitCount++;
        }



        // combining 2 arrays
        for(i=0;i<35;i++){
            binary[b_i]=binaryD[i];
            b_i++;
        }

        // mantissa
        int mantissaIndex=0;
        char mantiInt[34];
        for(i=integerBitCount-2; i>= 0; i--){
            mantiInt[mantissaIndex]=binaryInteger[i];
            mantissaIndex++;
        }
        char manti[34];
        i=0;
        if(userInput>=0){
            manti[0]=0;
            printf("Sign: 1\n");
        } else {
            manti[0]=1;
            printf("Sign: 0\n");
        }
        //mantissa printing
        printf("Mantissa (24 bit): ");
        for (i=0; i<=23; i++){
            manti[i+1]=binary[i+1];
            printf("%d", manti[i]);fflush(stdout);
        }
        printf("\n");
        printf("Number of mantissa digit is: %d", i);

        // exponent
        int unbiasedExponent = 0, exp_i;
        unbiasedExponent = integerBitCount-1;

        // Calculate biased exponent and print
        calculateExponent(unbiasedExponent, exponentBinary, &exponentBitCount);
    }
    
    return 0;
}
