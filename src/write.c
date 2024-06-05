#include"global.h"
#include<stdio.h>
#include<stdlib.h>

void write_as(){
    int idex = 0;
    FILE* file = fopen("a.s","w");
    if(file == NULL){
        printf("Could not open file a.s\n");
        return;
    }
    while(first_instr != code){
        printf("|%d",idex++);
        switch(first_instr->op){
            case Assign:
                printf("|Assign ");
                break;
            case Load:
                printf("|Load ");
                break;
            case Or:
                printf("|Or ");
                break;
            case And:
                printf("|And ");
                break;
            case Eq:
                printf("|Eq ");
                break;
            case Ne:
                printf("|Ne ");
                break;
            case Lt:
                printf("|Lt ");
                break;
            case Gt:
                printf("|Gt ");
                break;
            case Le:
                printf("|Le ");
                break;
            case Ge:
                printf("|Ge ");
                break;
            case Plus:
                printf("|Plus ");
                break;
            case Not:
                printf("|Not ");
                break;
            case Minus:
                printf("|Minus ");
                break;
            case Mul:
                printf("|Mul ");
                break;
            case Div:
                printf("|Div ");
                break;
            case Inc:
                printf("|Inc ");
                break;
            case Dec:
                printf("|Dec ");
                break;
            case Jump:
                printf("|Jump ");
                break;
            case Jnz:
                printf("|Jnz ");
                break;
            case Call:
                printf("|Call ");
                break;
            case Print:
                printf("|Print ");
                break;
        }
        switch(first_instr->arg1_type){
            case CODE:
                printf("|[CODE]");
                break;
            case DATA:
                printf("|[DATA]");
                break;
            case STACK:
                printf("|[STACK]");
                break;
            case Tmp:
                printf("|Tmp");
                break;
            case Num:
                printf("|");
                break;
            default :
                printf("|");
        }
        printf("%d ",first_instr->arg1_value);
        switch(first_instr->arg2_type){
            case CODE:
                printf("|[CODE]");
                break;
            case DATA:
                printf("|[DATA]");
                break;
            case STACK:
                printf("|[STACK]");
                break;
            case Tmp:
                printf("|Tmp");
                break;
            case Num:
                printf("|");
                break;
            default :
                printf("|");
        }
        printf("%d ",first_instr->arg2_value);
        switch(first_instr->result_type){
            case CODE:
                printf("|[CODE]");
                break;
            case DATA:
                printf("|[DATA]");
                break;
            case STACK:
                printf("|[STACK]");
                break;
            case Tmp:
                printf("|Tmp");
                break;
            case Num:
                printf("|");
                break;
            default :
                printf("|");
        }
        printf("%d ",first_instr->result_value);
        printf("|\n");
        first_instr++;
    }

}