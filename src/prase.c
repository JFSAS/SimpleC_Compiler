#include"global.h"
#include<stdio.h>
#include<stdlib.h>
int tmp_arg=0;
instr *idmain = NULL;
//the type of expression (NUM,INT,CHAR,VOID,PTR,ID)
int exp_type;
//arg3
//arg2
//arg1  
//return adderss  bp
//var1
//var2

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
int expression(int level){
    //use to check assignable
     int is_var = 0;  
     if(token == NUM){
        match(NUM);
        // 将NUM保存在tmp中
        code -> op = Plus;
        code -> arg1_value = token_val;
        code -> arg1_type = Num;
        code -> result_value = tmp_arg++;
        code -> result_type = Tmp;
        code ++;
     }else if(token == ID){
        match(ID);
        if(token == '['){
            //解析数组
            match('[');
            expression(ASSIGN);
            match(']');
            //计算指针长度: 数组类型
            int size  = 0;
            if(current_symbol->Type = INT){
                size = sizeof(INT);
            }else{
                size = sizeof(CHAR);
            }
            //计算指针偏移：数组偏移乘上指针长度
            code -> op = Mul;
            code -> arg1_type = Num;
            code -> arg1_value = size;
            code -> arg2_type = Tmp;
            code -> arg2_value = tmp_arg - 1;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            //计算指针地址： 数组加上偏移地址
            code -> op = Plus;
            code -> arg1_value = tmp_arg-1;
            code -> arg1_type = Tmp;
            code -> arg2_value = current_symbol -> Value;
            if(current_symbol->Class == LOC){
                code -> arg2_type = STACK;
            }else{
                code -> arg2_type = DATA;
            }
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++ ;
            //保存is_var 的赋值地址
            is_var = tmp_arg - 1;
            //load地址中的值
            code -> op = Load;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg-1;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
        }else if(token == '('){
            //解析函数
            match('(');
            int param_num=0;
            //保存函数传参
            while(token != ')'){
                param_num--;
                expression(Assign);
                //将传参存入栈
                code -> op = Assign;
                code -> arg1_type = Tmp;
                code -> arg1_value = tmp_arg - 1;
                code -> result_type = STACK;
                code -> result_value = param_num;
                code ++;
                if(token != ')'){
                    match(',');
                }
            }
            //保存return地址
            code -> op = Assign;
            code -> arg1_type = CODE;
            code -> arg1_value = (int)(code+1) - (int)first_instr;
            code -> result_type = STACK;
            code -> result_value = 0;
            match(')');
            code++;
        }else{
            //解析变量
            //保存变量地址
            code -> op = Plus;
            if(current_symbol -> Class == LOC){
                code -> arg1_type = STACK;
            }else{
                code -> arg1_type = DATA;
            }
            code -> arg1_value = current_symbol -> Value;
            code -> arg2_type = Num;
            code -> arg2_value = 0;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            is_var = tmp_arg - 1;
            //保存变量值
            code -> op = Load ;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg - 1;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
        }
     }else if(token == '('){
        //prase bracket use stack
        match('(');
        is_var = expression(ASSIGN);
     }else if(token == MUL){
        //解析指针
        match(MUL);
        expression(INC);
        is_var = tmp_arg - 1;
        //取变量值
        code -> op = Load;
        code -> arg1_type = Tmp;
        code -> arg1_value = tmp_arg-1;
        code -> result_type = Tmp;
        code -> result_value = tmp_arg ++;
        code ++;
     }else if(token == INC){
        //the inc and dec must follow the ID
        match(INC);
        if(token !=ID){
            printf("line %d,expect ID, get %c,Expression must be a modifiable lvalue",line,token);
            exit(-1);
        }
        int tmp_var;
        tmp_var = expression(INC+1);
        if(tmp_var){
            //先返回值是自增后的值
            //取值
            code -> op = Load ;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_var;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            //自增
            code -> op = Plus;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg-1;
            code -> arg2_type = Num;
            code -> arg2_value = 1;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            //存值
            code -> op = Assign;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg-1;
            code -> result_type = Tmp;
            code -> result_value = tmp_var;
            code ++;
            is_var = tmp_var;
        }else{
            printf("line %d,the value after \"++\" must be a assignable var,get %d",line, token);
            exit(-1);
        }
        
     }else if(token == DEC){
        match(DEC);
        if(token !=ID){
            printf("line %d,expect ID, get %c,Expression must be a modifiable lvalue",line,token);
            exit(-1);
        }
        int tmp_var;
        tmp_var = expression(INC+1);
        if(tmp_var){
            //先返回值是自减后的值
            //取值
            code -> op = Load ;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_var;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            //自减
            code -> op = Minus;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg-1;
            code -> arg2_type = Num;
            code -> arg2_value = 1;
            code -> result_type = Tmp;
            code -> result_value = tmp_arg++;
            code ++;
            //存值
            code -> op = Assign;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg-1;
            code -> result_type = Tmp;
            code -> result_value = tmp_var;
            code ++;
            is_var = tmp_var;
        }else{
            printf("line %d,the value after \"++\" must be a assignable var,get %d",line, token);
            exit(-1);
        }
        
     }else if(token == ')'){
        match(')');
        return is_var;
     }else if(token == NOT){
        match(NOT);
        expression(NOT);
        code -> op = Not;
        code -> arg1_type = Tmp;
        code -> arg1_value = tmp_arg -1;
        code -> result_type = Tmp;
        code -> result_value = tmp_arg++;
        code ++;
     }
     else{
        printf("line: %d ,bad expression,get %d ",line ,token);
        exit(-1);
     }
     while(token >= level){
        //保存左值
        int lvalue = tmp_arg-1;
        if(token == ASSIGN){
            match(ASSIGN);
            int tmp_var=0;
            tmp_var = expression(ASSIGN);
            //emit code
            //保存值
            code -> op = Assign;
            code -> arg1_type = Tmp;
            code -> arg1_value = tmp_arg - 1;
            code -> result_type = Tmp;
            code -> result_value = is_var;
            code ++;
            continue;
        }else if(token == OR){
            match(OR);
            expression(OR);
            //emit code;
            code -> op = Or;
        }else if(token == AND){
            match(AND);
            expression(AND);
            //emit code
            code -> op = And;
        }else if(token == EQ){
            match(EQ);
            expression(EQ);
            //emit code
            code -> op = Eq;
        }else if(token == NE){
            match(NE);
            int lvalue = tmp_arg-1;
            expression(NE);
            //emit code
            code -> op = Ne;
        }else if(token == GE){
            match(GE);
            int lvalue = tmp_arg-1;
            expression(GE);
            //emit code
            code -> op = Ge;
        }else if(token == LE){
            match(LE);
            int lvalue = tmp_arg-1;
            expression(LE);
            //emit code
            code -> op = Le;
        }else if(token == LT){
            match(LT);
            int lvalue = tmp_arg-1;
            expression(LT);
            //emit code
            code -> op = Lt;
        }else if(token == GT){
            match(GT);
            expression(GT);
            code -> op = Gt;
        }else if(token == PLUS){
            match(PLUS);
            expression(PLUS);
            code -> op = Plus;
        }else if(token == MINUS){
            match(MINUS);
            expression(MINUS);
            code -> op = Minus;
        }else if(token == INC){
            match(INC);
            if(is_var == 0){
                printf("line %d,expect var, get %d",line,token);
                exit(-1);
            }else{
                code -> op = Plus;
                code -> arg1_type = Tmp;
                code -> arg1_value = is_var;
                code -> arg2_type = Num;
                code -> arg2_value = 1;
                code -> result_type = Tmp;
                code -> result_value = tmp_arg++;
                code ++;
                code -> op = Assign;
                code -> arg1_type = Tmp;
                code -> arg1_value = tmp_arg-1;
                code -> result_type = Tmp;
                code -> result_value = is_var;
                code ++;
                
            }
            return is_var;
        }else if(token == DEC){
            match(DEC);
            if(is_var == 0){
                printf("line %d,expect var, get %d",line,token);
                exit(-1);
            }else{
                code -> op = Minus;
                code -> arg1_type = Tmp;
                code -> arg1_value = is_var;
                code -> arg2_type = Num;
                code -> arg2_value = 1;
                code -> result_type = Tmp;
                code -> result_value = tmp_arg++;
                code ++;
                code -> op = Assign;
                code -> arg1_type = Tmp;
                code -> arg1_value = tmp_arg-1;
                code -> result_type = Tmp;
                code -> result_value = is_var;
                code ++;
                
            }
            return is_var;  
        }else if(token == MUL){
            match(MUL);
            expression(MUL);
            code -> op = Mul;
        }else if(token == DIV){
            match(DIV);
            expression(DIV);
            code -> op = Div;
        }else{
            printf("line %d,bad expression op,get %d",line,token);
            exit(-1);
        }
        //emit code
        code -> arg1_type = Tmp;
        code -> arg1_value = lvalue;
        code -> arg2_type = Tmp;
        code -> arg2_value = tmp_arg - 1;
        code -> result_type = Tmp;
        code -> result_value = tmp_arg++;
        code ++;
     }
     //返回赋值地址
     return is_var;
     
}

void if_statement(){
    int *a;
    int *b;
    match(IF);
    match('(');
    expression(ASSIGN);
    //false jump
    code->op = Jnz;
    code->arg1_type = Tmp;
    code->arg1_value = tmp_arg-1;
    a = &code->result_value;
    code->result_type = CODE;
    code++;
    match(')');
    match('{');
    while(token != '}'){
        statement();
    }
    match('}');
    //jump ifend
    code->op = Jump;
    b = &code->result_value;
    code->result_type = CODE;
    code++;
    //patchback false jump
    *a = (int)code-(int)first_instr;
    if(token == ELSE){
        match(ELSE);
        match('{');
        while(token != '}'){
            statement();
        }
        match('}');
    }
    *b= (int)code-(int)first_instr;
    return;
}
void while_statement(){
    int a;
    int * b;
    match(WHILE);
    match('(');
    a = (int)code-(int)first_instr;
    expression(ASSIGN);
    //jnz to false;
    code->op = Jnz;
    code->arg1_type = Tmp;
    code->arg1_value = tmp_arg;
    b = &code->result_value;
    code->result_type = CODE;
    code++;
    match(')');
    match('{');
    while(token != '}'){
        statement();
    }
    code->op = Jump;
    code->result_value = a;
    code->result_type = CODE;
    code ++;
    *b = (int)code-(int)first_instr;
    match('}');
    return;
}
void return_statement(){
    match(RETURN);
    expression(ASSIGN);
    code->op = Jump;
    code->result_value = 0; 
    code->result_type = STACK;
    code++;
    match(';');
    return;
}
void printf_statement(){
    match(PRINTF);
    match('(');
    if(token == STRING){
        match(STRING);
        code->op = Print;
        code->arg1_type = DATA;
        code->arg1_value = token_val;
        code++;
    }else if(token == ID){
        match(ID);
        //load form id
        code->op = 
        code->op = Print;
        code->arg1_type = Tmp;
        code->arg1_value = tmp_arg-1;
        code++;
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
    int tmp_type;
    int params=1;
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
    current_symbol -> Btype = current_symbol->Type;
    current_symbol -> Type = type;
    current_symbol -> Bclass = current_symbol -> Class;
    current_symbol -> Class = LOC;
    current_symbol -> Bvalue = current_symbol -> Value;
    current_symbol -> Value = params;
    params++;
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
        current_symbol -> Btype = current_symbol->Type;
        current_symbol -> Type = type;
        current_symbol -> Bclass = current_symbol -> Class;
        current_symbol -> Class = LOC;
        current_symbol -> Bvalue = current_symbol -> Value;
        current_symbol -> Value = params;
        params++;
    }
    match(';');
    return;
}
void params(){
    int type;
    int class;
    int param=-1;
    while(token != ')'){
        if(token == VOID && *src == ')'){
            //empty is void
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
            type = type + PTR;
        }
        match(ID);
        //store local var
            current_symbol->Btype = current_symbol ->Type;
            current_symbol->Type = type;
            current_symbol->Bvalue = current_symbol->Value;
            current_symbol->Value = param--;
            current_symbol->Bclass = current_symbol->Class;
            current_symbol->Class = LOC;
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
    current_symbol->Class = FUNC;
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
    int class = GLO;
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
        current_symbol->Value = (int)data - (int)first_data;
        current_symbol->Class = GLO;
        data+=token_val;
        match(']');
        return;
    
    }else if(token == '('){
        //prase fun
        match('(');
        fun_declaration();
        current_symbol = symbol_table;
        while(current_symbol -> Token ){
            if(current_symbol->Class == LOC){
                current_symbol->Class = current_symbol->Bclass;
                current_symbol->Value = current_symbol->Bvalue;
                current_symbol->Type = current_symbol->Btype;
            }
            current_symbol++;
        }
        return;
    }else{
        current_symbol->Type = type;
        current_symbol->Class = GLO;
        current_symbol->Value = (int)data - (int)first_data;
        data++;
    }
     if(token == ','){
        current_symbol->Type = type;
        current_symbol->Value = (int)data - (int)first_data;
        current_symbol->Class = GLO;
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
                current_symbol->Value = (int)data - (int)first_data;
                current_symbol->Class = GLO;
                data+=token_val;
                match(']');
            }else{
                current_symbol->Type = tmp_type;
                current_symbol->Value = (int)data - (int)first_data;
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
