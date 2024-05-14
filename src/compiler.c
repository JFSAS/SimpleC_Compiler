#include"global.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
symbol * symbol_table;
symbol * sym_ptr;
int token_val;
char *src;
int token;
char *data;
int line = 1;
int load_src(char* filename){
    int cnt;
    FILE* file=fopen(filename,"r");
    if(file == NULL){
        printf("Connot open this file!!\n");
        return -1;
    }
    if((cnt = fread(src, 1, MAX_SIZE,file)) <=0){
        printf("Could not read source code!!\n");
        return -1;
    }
    src[cnt] = 0;
    fclose(file);
    return 0; 

}
int main(int argc,char** argv){
    if(!(symbol_table = malloc(MAX_SIZE))){
        printf("Could not malloc %d memory to symbol_table",MAX_SIZE);
    }
    memset(symbol_table,0,MAX_SIZE);
    // add keyword to symbol;
    Keyword();
    if(!(data = malloc(MAX_SIZE))) {
        printf("Could not malloc %d memory to data",MAX_SIZE);
    }
    if(!(src = malloc(MAX_SIZE))){
        printf("Could not malloc %d memory to source code",MAX_SIZE);
    }
    memset(src,0,MAX_SIZE);
    if(load_src(*(argv+1)) != 0) return -1;
    while(1){GetToken();}
    
}