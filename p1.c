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

// Function to calculate the biased exponent
void calculateExponent (int unbiasedExp, int *expBinary, int *bitCount) {
    int biasedExp = EXPONENT_BIAS + unbiasedExp;
    int i = 0, j=0,quotient, remainder;
    do {
        quotient = biasedExp / 2;
        remainder = biasedExp % 2;
        expBinary[i++] = remainder;
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

    int i = 0, integerBitCount = 0, countD=0, quotient=0, remainder,
    exponent = 0, exponentBitCount = 0, countExp = 0;
    int binaryD[40];

    int binaryInteger[32], binaryFraction[55], mantissa[23];
    float inputD = 0, inputManti = 0;

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
        //
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
        int countManti=0;
        if(userInput<0)
            inputD = userInput * -1;
        else
            inputD = userInput;
        inputManti = inputD;
        char binaryD[40];
        i=0;
        printf("Input is %f\n", userInput);
        while (inputD-(int)inputD != 0 && i<55){
            inputD = inputD * 2;
            binaryD[i]=(int)inputD;
            if(inputD>1){
                inputD = inputD-(int)inputD;
            }
            i++;
        }
        binaryD[35]='a';
        countD=0;
        while(binaryD[countD]!='a'){
            countD++;
        }

            i=-1;
            int countDot=0;
            while(binaryD[i]!=1){
                countDot++;
                i++;
            }
            i=countDot;
            countManti=0;
            if(userInput>=0){
                binaryD[countDot-1]=0;
                printf("Sign: 0\n");
            } else {
                binaryD[countDot-1]=1;
                printf("Sign: 1\n");
            }
        // mantissa
        printf("Mantissa (24 bit): ");
        for (i=countDot-1;i<=22+countDot;i++){
            printf("%d", binaryD[i]);fflush(stdout);
            countManti++;
        }
        printf("\n");fflush(stdout);
        //printf("Mantissa bits: %d\n", countManti);


        // exponent

        int exp = 0;
        exp = countDot;
        integerPart = 127-countDot;
        int countDE = 0; i = 0;
        char exp_D[10];
        do{
            quotient=integerPart/2;
            remainder=integerPart%2;
            exp_D[i]=remainder;
            integerPart=quotient;
            i++;
        } while(quotient!=0);
        exp_D[i]='a';
        while(exp_D[countDE]!='a'){
            countDE++;
        }
        while(countDE<8){
            exp_D[countDE]=0;
            countDE=countDE+1;
            exp_D[countDE]='a';
        }
        printf("Exponent: ");
        for (i=countDE-1;i>=0;i--){
            printf("%d", exp_D[i]);fflush(stdout);
        }
        printf("\n");
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
        inputD=userInput-(int)userInput;
        if(userInput<0)
            inputD=(userInput*-1)-((int)userInput*-1);
        else
            inputD=userInput-(int)userInput;
        inputManti=inputD;
        char binaryD[40];
        i=0;
        while (inputD-(int)inputD != 0 && i<50){
            inputD = inputD*2;
            binaryD[i]=(int)inputD;
            if(inputD>1){
                inputD=inputD-(int)inputD;
            }
            i++;
        }
        binaryD[39]='a';
        countD=0;
        while(binaryD[countD]!='a'){
            countD++;
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
