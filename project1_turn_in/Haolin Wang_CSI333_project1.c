//
//  main.c
//  project1
//
//  Created by Haolin Wang on 2/25/23.
//ICSI333. System Fundamentals,
//Spring 2023,
// TA: Manasa Nannuru
// My name: Haolin Wang
// Student ID: 001536867

#include <stdio.h>

int main() {
    
    printf("Hello, World!\n");

    float c=1.53332211;
    char input2=6.5555;
    char binary[10];
    int i=0,count=0, countD=0, input,quotient, remainder;
    //for(i=0;i<8;i++)
    input=121;
    printf("Input is: %d\n",input);
    
    // algorithm to convert integer to binary number
    do{
        quotient=input/2;
        remainder=input%2;
        binary[i]=remainder;
        input=quotient;
        i++;
    }while(quotient!=0);
    //while(quotient>0);
    
    
    binary[i]='a';
    while(binary[count] !='a' ){
        count++;
    }
    printf("count: %d\n", count);
    printf("Int to binary: ");
    for (i=count-1; i>=0; i--){
        printf("%d",binary[i]);
    }
    //printf("%d\n", binary[0]);
    printf("\n");


    // algorithm to convert integer to binary number
    float inputD = 0.3;
    char binaryD[20];
    printf("Input is: %f\n", inputD);
    while(inputD-(int)inputD != 0 && i<12){
        inputD = inputD*2;
        binaryD[i]=(int)inputD;
        if(inputD>1){
            inputD = inputD-(int)inputD;
        }
        i++;
    }

    //printf("number of i is: %d\n", i);
    //printf("binary[3] is: %d\n", binaryD[3]);

    binaryD[i+1]='a'; // not i+1?
    countD=0;
    while(binaryD[countD]!='a'){
        countD++;
    }
    //printf("countD: %d\n", countD);

    printf("Decimal to binary: ");
    for (i=0;i<countD;i++){
        printf("%d",binaryD[i]);
    }
    printf("\n");

    return 0;
}

// insert code here...

//char binary[]={1,2,3,0,4,5,'a'};

//    while(binary[count] !='a' ){
//        count++;
//    }
//    for (i=count-1; i>=0; i--){
//        printf("%d",binary[i]);
//    }
