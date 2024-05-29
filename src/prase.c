#include"global.h"
#include<stdio.h>
#include<stdlib.h>
int tmp_arg=0;
CODE *idmain;
void statement();
void match(int tk){
    if(token == tk){
        printf("line :%d token = %c,%d\n",line,tk,tk);
        GetToken();
        return;
    }else{
        printf("line: %d expect %d(%c),get %d(%c)",line,tk,tk,token,token);
        exit(-1);
    }
}
void expression(int level){
     if(token == NUM){
        match(NUM);
     }else if(token == ID){
        match(ID);
        if(token == '['){
            //array
            match('[');
            expression(ASSIGN);
            match(']');
        }else if(token == '('){
            //func
            match('(');
            int param_num=0;
            while(token != ')'){
                param_num++;
                expression(ASSIGN);
                if(token != ')'){
                    match(',');
                }
            //do something
            }
            match(')');
        }
     }else if(token == '('){
        match('(');
        expression(ASSIGN);
        match(')');
     }else if(token == MUL){
        match(MUL);
        expression(INC);
     }else if(token == INC){
        match(INC);
        expression(INC+1);
     }else if(token == DEC){
        match(DEC);
        expression(DEC+1);
     }else if(token == ')'){
        match(')');
        return;
     }else if(token == NOT){
        match(NOT);
        expression(NOT);
     }
     else{
        printf("line: %d ,bad expression,get %d ",line ,token);
        exit(-1);
     }
     while(token >= level){
        if(token == ASSIGN){
            match(ASSIGN);
            expression(ASSIGN);
            //emit code
        }else if(token == OR){
            match(OR);
            expression(OR);
            //emit code;
        }else if(token == AND){
            match(AND);
            expression(AND);
            //emit code
        }else if(token == EQ){
            match(EQ);
            expression(EQ);
            //emit code
        }else if(token == NE){
            match(NE);
            expression(NE);
        }else if(token == GE){
            match(GE);
            expression(GE);
        }else if(token == LE){
            match(LE);
            expression(LE);
        }else if(token == LT){
            match(LT);
            expression(LT);
        }else if(token == GT){
            match(GT);
            expression(GT);
        }else if(token == PLUS){
            match(PLUS);
            expression(PLUS);
        }else if(token == MINUS){
            match(MINUS);
            expression(MINUS);
        }else if(token == INC){
            match(INC);
            return;
        }else if(token == DEC){
            match(DEC);
            return;
        }else if(token == MUL){
            match(MUL);
            expression(MUL);
        }else if(token == DIV){
            match(DIV);
            expression(DIV);
        }else if(token == '['){
            match('[');
            match(NUM);
            match(']');
            return;
        }
        else{
            printf("line %d,bad expression op,get %d",line,token);
            exit(-1);
        }
     }
     
}

void if_statement(){
    match(IF);
    match('(');
    expression(ASSIGN);
    match(')');
    match('{');
    while(token != '}'){
        statement();
    }
    match('}');
    if(token == ELSE){
        match(ELSE);
        match('{');
        while(token != '}'){
            statement();
        }
        match('}');
    }
    return;
}
void while_statement(){
    match(WHILE);
    match('(');
    expression(ASSIGN);
    match(')');
    match('{');
    while(token != '}'){
        statement();
    }
    match('}');
    return;
}
void return_statement(){
    match(RETURN);
    expression(ASSIGN);
    match(';');
    return;
}
void printf_statement(){
    match(PRINTF);
    match('(');
    if(token == STRING){
        match(STRING);
    }else if(token == ID){
        match(ID);
    }else{
        printf("line :%d,syntax error,printf need string or var,got %c",token);
        exit(-1);
    }
    match(')');
    match(';');
    return;
}
void statement(){
    if(token == IF){
        if_statement();
        return;
    }else if(token == WHILE){
        while_statement();
        return;
    }else if(token == RETURN){
        return_statement();
        return;
    }else if(token == PRINTF){
        printf_statement();
        return;
    }else{
        expression(ASSIGN);
        match(';');
        return;
    }
    printf("line :%d,syntax error,unexpected symbol \'%c\'",line,token);
}
//<var-declaration> ::= <type> ['*'] ID ['['NUM']'] {',' ID ['['NUM']']};
void var_decl(){
    int type;
    int class = NUM;
    int ibp=0;
    int tmp_type;
    if(token == INT){
            match(INT);
            type = INT;
        }else if(token == CHAR){
            match(CHAR);
            type = CHAR;
        }else if(token == VOID){
            match(VOID);
            type = INT;
        }else{
            printf("line:%d,expect type ,get %d(%c) ",line,token,token );
            exit(-1);
        }
    if(token == MUL){
        match(MUL);
        tmp_type = type+PTR;
    }
    match(ID);
    if(token =='['){
        match('[');
        match(NUM);
        match(']');
        tmp_type = type +PTR;
    }
    while(token != ';' ){
        match(',');
        if(token == MUL){
            match(MUL);
            tmp_type = type + PTR;
        }else{
            tmp_type = type;
        }
        
        match(ID);
        if(token == '['){
            match('[');
            tmp_type = type + PTR;
            match(NUM);
            match(']');
        }
        current_symbol -> Type = tmp_type;
        current_symbol -> Value = ibp;
        ibp--;
    }
    match(';');
    return;
}
void params(){
    int type;
    int class;
    while(token != ')'){
        if(token == VOID && *src == ')'){
            match(VOID);
            match(')');   
            return;
        }else if(token == INT){
            match(INT);
            type = INT;
        }else if(token == CHAR){
            match(CHAR);
            type = CHAR;
        }else if(token == VOID){
            match(VOID);
            type = INT;
        }else{
            printf("line:%d,expect type ,get %c ",line,token );
            exit(-1);
        }
        if(token == MUL){
            match(MUL);
            class = PTR;
        }
        match(ID);
        //prase var
        if(token == ','){
            match(',');
        }
    }
    match(')');
    return;
}
//<body_decl> ::={local_var_declarations>}, {<statement>};
void body_decl(){
   while(token != '}'){
     if(token == INT || token == CHAR || token == VOID){
        var_decl();
     }else{
        statement();
     }
   }
   return;
}
void fun_declaration(){
    //add fun entry
    current_symbol->Class = FUN;
    current_symbol->Value = (int)code;
    if(token == INT || token == CHAR || token == VOID){
        params();
    }
    if(token == '{'){
        match('{');
        body_decl();
        match('}');
    }else{
        printf("line %d,func defien exprect '{',got %c",line, token);
        exit(-1);
    }
    return;
    
}
//parse declaration  
//<declaration> ::= <var-declaration> | <fun-declaration>;
//<var-declaration> ::= <type> ['*'] ID ['['NUM']'] {',' ID ['['NUM']']};
//<fun-declaration> ::= <type> ['*'] ID '(' <params> ')' '{' <body_decl> '}';
void declaration(){
    int type;
    int class = NUM;
    int tmp_type;
    //prase type
    if(token == INT ){
        type = INT;
        match(INT);
    }else if(token == CHAR){
        type = CHAR;
        match(CHAR);
    }else if(token == VOID){
        match(VOID);
        type = VOID;
    }else{
        printf("line %d,expect type,get %c",line, token);
        exit(-1);
    }
    
    if(token == MUL){
    //parse PTR
    //if is ptr type + PTR
        match(MUL);
        type = type + PTR;
    }
    if(token != ID){
        if(token == MAIN){
            idmain = code;
            match(MAIN);
        }else {
        printf("line :%d,declaration error,expect ID,get : %c",token);
        exit(-1);
        }
    }else{
        match(ID);
    }
    if(token == '['){
        //prase array and malloc memory in data segment, type is PTR,address stored in value, 
        match('[');
        if(token!=NUM){
            printf("line :%d,expect array size num,get :%c",token);
        }
        match(NUM);
        current_symbol->Type = PTR;
        current_symbol->Value = (int)data;
        current_symbol->Class = NUM;
        data+=token_val;
        match(']');
        return;
    
    }else if(token == '('){
        //prase fun
        match('(');
        fun_declaration();
        return;
    }else if(token == ','){
        current_symbol->Type = type;
        current_symbol->Value = (int)data;
        current_symbol->Class = NUM;
        data++;
        while(token != ';' ){
            match(',');
            if(token == MUL){
                match(MUL);
                tmp_type = type + PTR;
            }else{
                tmp_type = type;
            }

            match(ID);
            current_symbol ->Type = type;
            if(token == '['){
                match('[');
                tmp_type = type + PTR;
                match(NUM);
                current_symbol->Type = tmp_type;
                current_symbol->Value = (int)data;
                current_symbol->Class = NUM;
                data+=token_val;
                match(']');
            }else{
                current_symbol->Type = tmp_type;
                current_symbol->Value = (int)data;
                data++;
            }
            
        }
        match(';');
    }else if(token == ';'){
        match(';');
    }else{
        printf("line %d,expect ';',got %c",line, token);
        exit(-1);
    }
    return;

}
void program(){
    GetToken();
    while(token > 0){
        declaration();
    }
    return ;
}
