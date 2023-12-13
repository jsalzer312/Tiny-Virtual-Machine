#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creating the Instruction Register Structure 
typedef struct IRStruct{
    int OP;
    int ADDR;
}IRStruct;

int main(){
    //create maximum size IM / DM
    int* IM=malloc(sizeof(int)*129);
    int* DM=malloc(sizeof(int)*11);
    //Creates tiny machines components
    int MAR,MDR,A='\0',PC=0;
    //creates additional variebles to store various information.
    int idx=0;
    //checks operator in switch case
    int execution;
    //stores string input from user, for showing VM updates
    char print;
    FILE *fp;
    //checking if file exits or not
    if((fp=fopen("elf.txt","r"))==NULL){
        printf("File 'elf.txt' does not exist, try again!\n");
        exit(-1);
    }
    //Open and reads exec txt
    fp = fopen("elf.txt","r");
    int integer=0;
    //creates maximum size IR struct
    IRStruct* IR=malloc(sizeof(IRStruct));
    //Reads input txt file, fills IM with instructions/addresses
    while(integer!=EOF){
        fscanf(fp,"%d %d",&IM[idx],&IM[idx+1]);
        idx+=2;
        integer=getc(fp);
        //stores the amount of instruction lines
    }
    //closes file after reading all instructions
    fclose(fp);

    //storing 1 in index 10 of Data Memory
    DM[10]=1;
    //storing 0 in index 3 for Total
    DM[3]=0;

    //asking user if they would like to display VM updates for every operation executed
    printf("\nWould you like to see the state of the VM when executing the program? (y/n): ");
    scanf("%c",&print);
    while(1){
        //FETCH Cycle, stores Operation & Address in Insturction Register
        IR->OP=IM[PC];
        IR->ADDR=IM[PC+1];
        //Increases PC by 2
        PC = PC + 2;
        //Reads IR Op-Code and executes, uses Address for instructions
        if(print=='y'){
            printf("PC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n\n",PC-2,A,DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);
        }
        switch(IR->OP){    
        //LOAD Operation, uses address to store value in accumulator
        case 1:
            MAR=IR->ADDR;
            MDR=DM[MAR];
            A=MDR;
            if(print=='y'){
                printf("LOAD <%d>\n",IR->ADDR);
            }
        break;

        //ADD Operation, uses address to add value to value in accumulator
        case 2:
            MAR=IR->ADDR;
            MDR=DM[MAR];
            A = A + MDR;
            if(print=='y'){
                printf("ADD <%d>\n",IR->ADDR);
            }
        break;

        //STORE Operation, uses address and stores value in specified data memory
        case 3:
            MAR=IR->ADDR;
            MDR=A;
            DM[MAR]=MDR;
            if(print=='y'){
                printf("STORE <%d>\n",IR->ADDR);
            }
        break;

        //SUB (Subtract) Operation, uses address to subtract from value in accumulator
        case 4:
            MAR=IR->ADDR;
            MDR=DM[MAR];
            A = A - MDR;
            if(print=='y'){
                printf("SUB <%d>\n",IR->ADDR);
            }
        break;

        //IN (Keyboard), recieves input from users keyboard
        case 5:
        if(print=='y'){
            printf("IN <5>\n");
        }
            printf("Input a value: ");
            scanf(" %d",&A);
            
        break;

        //OUT (Screen), displays value onto users compiler
        case 6: 
            if(print=='y'){
                printf("OUT <7>\n");
            }
            printf("Result is: %d\n",A);
        break;

        //HALT Operation, ends program
        case 7:

            printf("End of Program!\n");
            printf("PC = %d | A = %d | DM = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n\n",PC-2,A,DM[0],DM[1],DM[2],DM[3],DM[4],DM[5],DM[6],DM[7],DM[8],DM[9]);

            exit(-1);
        break;

        //JMP Operation, jumps to specified PC value
        case 8:
            if(print=='y'){
                printf("JUMP <%d>\n",IR->ADDR); 
            }
            PC=IR->ADDR;
        break;

        //SKIPZ, Compares value in A witht the following statement: A = 0
        case 9:
            if(print=='y'){
                printf("SKIPZ\n");
            }
            if(A==0){
                PC = PC + 2;
            }
        break;

        //SKIPG, Compares value in A witht the following statement: A > 0
        case 10:
            if(print=='y'){
                printf("SKIPG\n");
            }
            if(A > 0){
                PC = PC + 2;
            }
        break;

        //SKIPL, Compares value in A witht the following statement: A < 0
        case 11:
            printf("SKIPL\n");
            if(A < 0){
                PC = PC + 2;
            }
        break;
        }
    }
    //freeing all allocated memory
    free(IR);
    free(fp);
    free(DM);
    free(IM);
    //return 0 if program executed properly!
    return 0;
}