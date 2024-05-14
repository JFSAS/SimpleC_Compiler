#include"global.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void GetToken(){
    char *ch_ptr;
    while(token = *src++){
        //merge spaces
        while(token == ' ' && *src == ' '){src++;}
        //recode line number
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
            sym_ptr = symbol_table;
            while(sym_ptr++ -> Token){
                if(sym_ptr -> Hash == token && memcmp(src,sym_ptr -> name, src - ch_ptr)){
                    char name_buf[100] ;
                    strncpy(name_buf,sym_ptr -> name, sym_ptr -> value );
                    printf("%d. token =  ID, name = %s, Hash = %d\n",line,name_buf,token);
                    token = ID;
                    return;
                }
            }
            sym_ptr -> Hash = token;
            sym_ptr -> Token = ID;
            sym_ptr -> name = ch_ptr;
            sym_ptr -> value = src - ch_ptr;
            token = ID;
            char name_buf[100] ;
            memset(name_buf,1,100);
            strncpy(name_buf,sym_ptr -> name, sym_ptr -> value );
            printf("%d. token = ID, name = %s, Hash = %d ,token_value : %d\n", line,name_buf,sym_ptr -> Hash,sym_ptr->value);
            return;
        }
        //identify NUM
        else if(token >='0' && token <= '9'){
            while(*src >= '0' && *src <= '9' ){
                token_val = token_val*10 + *src++ - '0';
            }
            token = NUM;
            printf("%d. token = NUM, val = %d\n",line, token_val);
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
            sym_ptr = symbol_table;
            while(sym_ptr++ -> Token);
            sym_ptr -> Token = STRING;
            sym_ptr -> name = ch_ptr;
            sym_ptr -> value = token_val; 
            char name_buf[1000];
            strncpy(name_buf,sym_ptr->name,sym_ptr->value);
            memset(name_buf,0,1000);
            printf("%d. token = STRING, name = %s ,token_value : %d\n",line,name_buf,sym_ptr->value);
            token = STRING;
            return ;
        }
        //identify other symbol
        else if(token == '+'){
            token = PLUS;
            printf("%d. + token = PLUS\n",line);
            return ;
        }
        else if(token == '-'){
            token = MINUS;
            printf("%d. - token = MINUS\n",line);
            return;
        }
        else if(token == '*'){
            token = MUL;
            printf("%d. * token = OVER\n",line);
            return;
        }
        else if(token == '/'){
            token =DIV;
            printf("%d. < token = DIV\n",line);
            return;
        }
        else if(token == '<'){
            if(*src == '='){
                src ++;
                token = LE;
                printf("%d. <= token = LE\n",line);
                return;
            }else{
                token = LT;
                printf("%d, < token = LT\n",line);
                return ;
            }
        }
        else if(token == '>'){
            if(*src == '='){
                src ++;
                token = GE;
                printf("%d,<= token = GE\n",line);
                return;
            }else{
                token = GT;
                printf("%d,> token = GT\n",line);
                return;
            }
        }
        else if(token == '!'){
            if(*src == '='){
                src ++;
                token = NE;
                printf("%d,!= token = NE\n",line);
                return;
            }
            printf("expect '=' after !");
            exit(-1);
        }
        else if(token == '='){
            if(*src == '='){
                src++;
                token = EQ;
                printf("%d,== token = EQ\n",line);
                return;
            }
            token = ASSIGN;
            printf("%d,= token = ASSIGN");
            return;
        }
        else if(token == '('){
            token = LPAREN;
            printf("%d,( token = LPAREN\n",line);
            return;
        }
        else if(token == ')'){
            token = RPAREN;
            printf("%d,) token = RPAREN\n",line);
            return;
        }
        else if(token == '{'){
            token = LBRACE;
            printf("%d,{ token = LBRACE\n",line);
            return;
        }
        else if(token == '}'){
            token = RBRACE;
            printf("%d,} token = RBRACE\n",line);
            return;
        }
        else if(token == '['){
            token = LBRACKET;
            printf("%d,[ token = LBRACKET\n",line);
            return;
        }
        else if(token == ']'){
            token = RBRACKET;
            printf("%d,] token = RBRACKET\n",line);
            return;
        }
        else if(token == ','){
            token = COMMA;
            printf("%d,, token = COMMA\n",line);
            return;
        }
        else if(token == ';'){
            token = SEMI;
            printf("%d,; token = SEMI\n",line);
        }

    }
        exit(0);

}

void Keyword()
{
    char *keyword= "int void if else while return ";
    char *sys = "printf";
    src = keyword;
    for(int i = INT;i <= RETURN;i ++){
        GetToken();
        sym_ptr->Token = i;
    }
    src = sys;
    GetToken();
    sym_ptr->Token = PRINTF;
    return;
}