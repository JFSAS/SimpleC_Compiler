#include"global.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
symbol* current_symbol;
void GetToken(){
    char *ch_ptr;
    while(token = *src++){
        //merge spaces
        while(token == ' ' && *src == ' '){src++;}
        //record line number
        if(token == '\n'){
            token = *src++;
            line ++;
        }
        //identify ID
        if(token >= 'a' && token <= 'z' || token >= 'A' && token <= 'Z'){
            ch_ptr = src-1;
            //calculate Hash
            while(*src >= 'a' && *src <= 'z' || *src >= 'A' && *src <= 'Z' || *src >= '0' && *src <= '9')
                token += token *127 + *src++;
            current_symbol = symbol_table;
            while(current_symbol -> Token){
                if(current_symbol -> Hash == token && memcmp(src,current_symbol -> Name, src - ch_ptr)){
                    token = current_symbol -> Token;
                    return;
                }
                current_symbol++;
            }
            current_symbol -> Hash = token;
            current_symbol -> Token = ID;
            current_symbol -> Name = ch_ptr;
            token = ID;
            return;
        }
        //identify NUM
        else if(token >='0' && token <= '9'){
            while(*src >= '0' && *src <= '9' ){
                token_val = token_val*10 + *src++ - '0';
            }
            token = NUM;
            return;
        }
        //identify STRING
        else if(token == '\"'){
            ch_ptr = data;
            token_val =0;
            while(*src != '\"'){
                *data++ = *src++;
                token_val ++;
            }
            src++;
            current_symbol = symbol_table;
            while(current_symbol++ -> Token);
            current_symbol -> Token = STRING;
            current_symbol -> Name = ch_ptr;
            current_symbol -> Value = token_val; 
            token = STRING;
            return ;
        }
        //identify other symbol
        else if(token == '+'){
            if(*src == '+'){
                src ++;
                token = INC;
                return;
            }
            token = PLUS;
            return ;
        }
        else if(token == '-'){
            if (*src == '-')
            {
                src++;
                token = DEC;
                return;
            } 
            token = MINUS;
            return;
        }
        else if(token == '*'){
            token = MUL;
            return;
        }
        else if(token == '/'){
            //skip comment
            if(*src == '/'){
                while(*src != '\n' && *src != 0){
                    ++src;
                }
            }else{
                token = DIV;
                return;
            }
        }
        else if(token == '<'){
            if(*src == '='){
                src ++;
                token = LE;
                return;
            }else{
                token = LT;
                return ;
            }
        }
        else if(token == '>'){
            if(*src == '='){
                src ++;
                token = GE;
                return;
            }else{
                token = GT;
                return;
            }
        }
        else if(token == '!'){
            if(*src == '='){
                src ++;
                token = NE;
                return;
            }else{
                token= NOT;
                return;
            }
        }
        else if(token == '='){
            if(*src == '='){
                src++;
                token = EQ;
                return;
            }
            token = ASSIGN;
            return;
        }else if(token == '&'){
            if(*src == '&'){
                src++;
                token = AND;
                return;
            }
            printf("line:%d expect : &&, missing &",line);
            exit(-1);
        }else if(token == '|'){
            if(*src == '|'){
                src++;
                token = OR;
                return;
            }
            printf("line:%d expect : ||, missing |",line);
            exit(-1);
        }else if(token == '(' || token == ')' || token == '{' || token ==  '}' || token == '[' || token == ']' || token ==  ',' || token == ';')
        {
            return;
        }else if(token != ' '){
            printf("line:%d,undefined symbol : %d",line,token);
            exit(-1);
        }

    }
}

void Keyword()
{
    char *keyword= "int void char if else while return main printf";
    src = keyword;
    for(int i = INT;i <= PRINTF;i ++){
        GetToken();
        current_symbol->Token = i;
    }
    return;
}