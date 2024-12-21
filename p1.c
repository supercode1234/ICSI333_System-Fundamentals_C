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

/**
 * Converts an integer to binary
 * The binary digits are stored in 'binaryArray' in reverse order
 *
 * @param inputInt The integer to convert
 * @param binaryArray The array where the binary representation will be stored
 * @param bitCount pointer to an integer where the number of bits will be stored
 */
void convertIntegerToBinary (int inputInt, int *binaryArray, int *bitCount) {
    int bitIndex = 0, quotient, remainder;

    // perform the division and modulus operations
    do {
        quotient = inputInt / 2;
        remainder = inputInt % 2;
        binaryArray[bitIndex++] = (char)remainder; // store remainder
        inputInt = quotient;                       // update inputInt to quotient
    } while (quotient != 0);

    *bitCount = bitIndex; // store the number of bits
    binaryArray[bitIndex] = '\0'; // proper null termination

}

/**
 *Calculates Exponent
 */
void calculateExponent (int unbiasedExp, int *expBinary, int *bitCount) {
    int biasedExp = 127 + unbiasedExp; // bias the exponent
    printf("Biased Exponent (Decimal): %d\n", biasedExp);

    int i = 0, j=0,quotient1, remainder1;

    // convert biased exponent to binary
    do {
        quotient1 = biasedExp / 2;
        remainder1 = biasedExp % 2;
        expBinary[i++] = remainder1;
        printf("debugging, remainder: %d",expBinary[j=i-1]);
        biasedExp = quotient1;
        printf("quotient: %d\n",quotient1);
    } while (quotient1 != 0);

    *bitCount = i; // store the number of bits
    printf("i is: %d",i);
    printf("exponet [i-1] is: %d\n",expBinary[i-1]);

    // pad with zeros to ensure exactly 8 bits
    while (*bitCount < 8) {
        printf("hi, testing");
        expBinary [(*bitCount)++] = 0;
    }
}

/**
 * Returns 1 if number is negative, else 0
 */
int getSignBit (float input) {
    return (input <0)? 1:0;
}

int main(int argc, const char * argv[]) {
    float userInputFloat= 2.3;

    // prompt the user for input
    printf("Input a real number: ");
    scanf("%f", &userInputFloat);

    // quick check for zero as user input
    if (userInputFloat == 0.0f) {
        printf("Everything is 0\n");
        printf("Sign: 0\n");
        printf("Exponent: 00000000\n");
        printf("Mantissa (24 bit): 000000000000000000000000\n");
        return 0;
    }

    // get sign bit
    int signBit = getSignBit(userInputFloat);


    // declare variables
    int i = 0, integerBitCount = 0, countD=0, quotient=0, remainder,
    exp = 0, countIntE = 0, countExp = 0, countManti=0;
    int exp_Int[10], binaryD[40];

    int binaryArray[32]; //32bit, max for most integers
    float inputD = 0, inputManti = 0;

    printf("Input is: %f\n", userInputFloat);

    int userInputInt = (int)userInputFloat;
    float userInputFraction = userInputFloat - userInputInt;



    /* When user input is an integer */
    if(userInputFloat == (int) userInputFloat  && userInputFloat!=0) {
        int mantissaArray[34];

        // Determine sign, convert negative to positive for ease of calculation
        if(userInputFloat<0) userInputInt = -userInputInt;

        // Call the function to convert integer to binary
        convertIntegerToBinary(userInputInt, binaryArray, &integerBitCount);

        // print the binary representation of the integer part
        printf("binary version of user input: ");
        for (int binaryIndex = integerBitCount-1; binaryIndex>=0; binaryIndex--) {
            printf("%d", binaryArray[binaryIndex]);
        }
        printf("\n");




        // Generating Mantissa
        mantissaArray[0] = signBit; // store the sign bit
        printf("Sign: %d\n", signBit);

        // copy binary digits of the integer part, skipping the leading bit
        int mantissaIndex = 1; // start filling from index 1
        for (int binaryIndex = integerBitCount - 2; binaryIndex >= 0; binaryIndex--){
            mantissaArray[mantissaIndex++]=binaryArray[binaryIndex];
        }


        // pad the remaining mantissa position with zeros up to 23 bits
        while (mantissaIndex<=23){
            mantissaArray[mantissaIndex++]=0;
        }

        // print the mantissa
        printf("Mantissa (24 bit): ");
        mantissaIndex=0;
        while (mantissaIndex<=23){
            printf("%d", mantissaArray[mantissaIndex]);
            mantissaIndex++;
        }
        printf("\n");
        printf("Digit count is: %d\n", mantissaIndex);



        // exponent
        exp = integerBitCount-1; // unbiased exponent


        // calculate with funciton
        calculateExponent(exp, exp_Int, &countIntE);

        // print Exponent
         printf("Exponent: ");

        // print in reverse order
        for (int j =countIntE-1;j>=0;j--) {
            printf("%d", exp_Int[j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }/* End of Integer */




    /* 0.[non-zero] */
    else if ((int)userInputFloat - userInputFloat != 0 && (int)userInputFloat == 0){
        if(userInputFloat<0)
            inputD = userInputFloat * -1;
        else
            inputD = userInputFloat;
        inputManti = inputD;
        char binaryD[40];
        i=0;
        printf("Input is %f\n", userInputFloat);
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
            if(userInputFloat>=0){
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
        userInputInt = 127-countDot;
        int countDE = 0; i = 0;
        char exp_D[10];
        do{
            quotient=userInputInt/2;
            remainder=userInputInt%2;
            exp_D[i]=remainder;
            userInputInt=quotient;
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
    else if (userInputFloat == 0){
        printf("Everything is 0\n");
    }
    /* [non-zero].[non-zero]*/
    else {
        i=0;
        printf("Input: %f\n", userInputFloat);
        if (userInputFloat<0)
            userInputInt = userInputFloat*-1;
        else
            userInputInt = (int)userInputFloat;

        // call method to convert the int part to bin
        convertIntegerToBinary(userInputInt, binaryArray, &integerBitCount);

        // print the bin version of the int part
        printf("binary (integer): ");
        for (int i=integerBitCount-1; i>=0; i--) {
            printf("%d", binaryArray[i]);
        }
        printf("\n");



        char binary[60]; int b_i=0;
        for (i=integerBitCount-1;i>=0;i--){
            binary[b_i]=binaryArray[i];
            b_i++;
        }


        // converting post decimal part
        inputD=userInputFloat-(int)userInputFloat;
        if(userInputFloat<0)
            inputD=(userInputFloat*-1)-((int)userInputFloat*-1);
        else
            inputD=userInputFloat-(int)userInputFloat;
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
            mantiInt[mantissaIndex]=binaryArray[i];
            mantissaIndex++;
        }
        char manti[34];
        i=0;
        if(userInputFloat>=0){
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
        int exp = 0, exp_i;
        exp = integerBitCount-1;
        userInputInt=127+exp;
        int countIntE=0; i=0;
        char exp_Int[8];
        int countExp = 0;
        do {
            quotient=userInputInt/2;
            remainder=userInputInt%2;
            exp_Int[i]=remainder;
            userInputInt=quotient;
            i++;
        } while (quotient!=0);
        exp_Int[i]='a';
        while(exp_Int[countIntE]!='a'){
            countIntE++;
        }
        while (countIntE<8){
            exp_Int[countIntE]=0;
            integerBitCount=integerBitCount+1;
            exp_Int[countIntE]='a';
        }
        printf("\n");
        printf("Exponent: ");
        for (i=countIntE-1;i>=0;i--){
            printf("%d", exp_Int[i]); fflush(stdout);
        }
        printf("\n");
    }
    
    return 0;
}
