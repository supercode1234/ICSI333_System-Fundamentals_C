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

// function to convert an integer to binary
void convertIntegerToBinary (int inputInt, int *binaryInt, int *bitCount) {
    int i = 0, quotient, remainder;
    do {
        quotient = inputInt / 2;
        remainder = inputInt % 2;
        binaryInt[i++] = (char)remainder;
        inputInt = quotient;
    } while (quotient != 0);

    binaryInt[i] = '\0'; // proper null termination
    *bitCount = i; // store the number of bits
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
        printf("debugging,%d",expBinary[j=i-1]);
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
    printf("printing:\n");
    for (int j =(*bitCount)-1;j>=0;j--) {
        //printf();
        printf("%d", expBinary[j]);
        fflush(stdout);
    }
    printf("\n");
}

/**
 * Get sign Bit
 * @param input
 * @return
 */
int getSignBit (float input) {
    return (input <0)? 1:0;
}

int main(int argc, const char * argv[]) {
    float userInput= 2.3;
    printf("Input a real number: ");
    scanf("%f", &userInput);

    // get sign bit
    int signBit = getSignBit(userInput);

    if (userInput == 0.0f) {
        printf("Everything is 0\n");
        printf("Sign: 0\n");
        printf("Exponent: 00000000\n");
        printf("Mantissa (24 bit): 000000000000000000000000\n");
        return 0;
    }


    // declare variables
    int i = 0,i2 = 0, countInt = 0, countD=0, quotient=0, remainder,
    exp = 0, countIntE = 0, countExp = 0, countManti=0;
    int binaryInt[30];
    char mantiInt[34], exp_Int[10], binaryD[40];

    float inputD = 0, inputManti = 0;
    // prompt the user for input


    printf("Input is: %f\n", userInput);


    int inputInt = (int)userInput;
    float inputFraction = userInput - inputInt;






    /* When user input is an integer */
    if(userInput == (int)userInput  && userInput!=0) {

        // Determine sign, convert negative to positive for ease of calculation
        if(userInput<0)
            inputInt = -inputInt;

        // Call the function to convert integer to binary
        convertIntegerToBinary(inputInt, binaryInt, &countInt);

        // print the binary representation of the integer part
        printf("binary (integer): ");
        for (int i=countInt-1; i>=0; i--) {
            printf("%d", binaryInt[i]);
        }
        printf("\n");

        mantiInt[0] = signBit;
        printf("Sign: %d\n", signBit);


        // Generating Mantissa
        i2 = 1;
        for (int i = countInt - 1; i > 0; i--){
            mantiInt[i2]=binaryInt[i];
            i2++;
        }




        // filling array with 0s
        while (i2<=23){
            mantiInt[i2]=0;
            i2++;
        }

        // print the mantissa
        i2=0;
        printf("Mantissa (24 bit): ");
        while (i2<=23){
            printf("%d", mantiInt[i2]);
            i2++;
        }
        printf("\n");
        //printf("Digit count is: %d\n", i2);





        // exponent
        exp = countInt-1; // unbiased exponent

        // inputInt = 127+exp; // biased exponent
        // do {
        //     quotient=inputInt/2;
        //     remainder=inputInt%2;
        //     exp_Int[i++]=remainder;
        //     inputInt=quotient;
        // } while(quotient!=0);
        //
        // // `i` now holds the number of bits in the exponent
        // countIntE = i;
        //
        // while (countIntE<8) {
        //     exp_Int[countIntE++]=0;
        // }

        // calculate with funciton
        calculateExponent(exp, exp_Int, &countIntE);
        printf("countIntE: %d\n", countIntE);

        // print Exponent
        printf("Exponent: ");
        printf("%d\n", exp_Int[countIntE-1]);

        // print in reverse order
        for (int j =countIntE-1;j>=0;j--) {
            //printf();
            printf("%d", exp_Int[j]);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }/* End of Integer */




    /* 0.[non-zero] */
    else if ((int)userInput - userInput != 0 && (int)userInput == 0){
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
        inputInt = 127-countDot;
        int countDE = 0; i = 0;
        char exp_D[10];
        do{
            quotient=inputInt/2;
            remainder=inputInt%2;
            exp_D[i]=remainder;
            inputInt=quotient;
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
    else if (userInput == 0){
        printf("Everything is 0\n");
    }
    /* [non-zero].[non-zero]*/
    else {
        i=0;
        printf("Input: %f\n", userInput);
        if (userInput<0)
            inputInt = userInput*-1;
        else
            inputInt = (int)userInput;

        // call method to convert the int part to bin
        convertIntegerToBinary(inputInt, binaryInt, &countInt);

        // print the bin version of the int part
        printf("binary (integer): ");
        for (int i=countInt-1; i>=0; i--) {
            printf("%d", binaryInt[i]);
        }
        printf("\n");



        char binary[60]; int b_i=0;
        for (i=countInt-1;i>=0;i--){
            binary[b_i]=binaryInt[i];
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
        i2=0;
        char mantiInt[34];
        for(i=countInt-2; i>= 0; i--){
            mantiInt[i2]=binaryInt[i];
            i2++;
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
        int exp = 0, exp_i;
        exp = countInt-1;
        inputInt=127+exp;
        int countIntE=0; i=0;
        char exp_Int[8];
        int countExp = 0;
        do {
            quotient=inputInt/2;
            remainder=inputInt%2;
            exp_Int[i]=remainder;
            inputInt=quotient;
            i++;
        } while (quotient!=0);
        exp_Int[i]='a';
        while(exp_Int[countIntE]!='a'){
            countIntE++;
        }
        while (countIntE<8){
            exp_Int[countIntE]=0;
            countInt=countInt+1;
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
