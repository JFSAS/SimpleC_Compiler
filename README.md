# 研究性文法——实现c语言的子程序的编译器

## 1. 问题描述

实现C语言子集的编译器，包括词法分析、语法分析、语义分析、中间代码生成、目标代码生成等功能。包含整型、函数的声明、赋值语句、if else语句、while语句、数组。

## 2. 文法定义

```bnf
NUM ::= digit*
digital ::= 0|1|2|3|4|5|6|7|8|9
ID ::= letter(letter|digit)*
letter ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
<string> ::= "<character>*"
<character> ::= {ALL ASCII CHARACTERS EXCEPT }
<program> ::= <declaration-list>
<declaration-list> ::= <declaration-list><declaration> | <declaration> 
<declaration> ::= <var-declaration> | <fun-declaration>
<var-declaration> ::= <type-specifier> ID; | <type-specifier> ID[NUM];
<fun-declaration> ::= <type-specifier> ID (<params>) <compound-stam>
<type-specifier> ::= int | void 
<params> ::= <param-list> | void
<params-list> ::= <params-list> <param> | <param>
<param> ::= <type-specifier> ID | <typer-specifier> ID[]
<compound-stam> ::={<local-declarations><statement-list>}
<local-declarations> ::=<local-declarations><var-declaration> | <empty>
<statement-list> ::=<statement-list><statement> | <empty>\
<statement> ::= <expression-stam> | <compound-stam> | <selection-stam> | <iteration-list> | <return-list> | <print-stam>
<expression-stam> ::= <expression>; 
<selection-stam> ::= if (<expression>) <compound-stam> | if (<expression>) <compound-stam> else <compound-stam>
<iteration-stam> ::= while (<expression>) <compound-stam>
<return-stam> ::= return; | return <expression>;
<print-stam> ::= printf(<string>); | printf(<var>);
<expression> ::= <var> = <expression> | <simple-expression>
<var> ::= ID | ID[<expression>] 
<simple-expression> ::= <additive-expression> <relop> <additive-expression> | <additive-expression>
<relop> ::= <= | < | > | >= | == | !=
<additive-expression> ::= <additive-expression> <addop> <term> | <term>
<addop> ::= + | -
<term> ::= <term> <mulop> <factor> | <factor>
<mulop> ::= * | /
<factor> ::= ( <expression> ) | <var> | NUM | <call>
<call> ::= ID ( <args> )
<args> ::= <arg-list> | <empty>
<arg-list> ::= <arg-list> , <expression> | <expression>
<printf> ::= printf(<string>)
```

```
  |-<expression>
     |-<simple-expression> > < 
        |-<additive-expression> + -
           |-<term> * /
              |-<factor>
                 |-<var>
                 |-ID
                 |-NUM
                 |-(<expression>)
```

## 3. 单词列表

标识符：标识符由字母和数字组成，但必须以字母开头。  
常数：非负字符串。  
字符串：双引号括起来的字符序列。  
运算符：+ - * / < <= > >= != == =  
界符：( ) { } [ ] , ; :  " #  
关键字： int void if else while return  printf

标识符、常数、字符串按照一类一码，运算符、界符、关键字按照一符一码。
| 单词符号 | 内部编码 | 值|
| --------|---------|-------|
| ID | ID | name |
| NUM | NUM | value |
| STRING | STRING | address |
| + | PLUS | |
| - | MINUS | |
| * | MUL | |
| / | DIV | |
| < | LT | |
| <= | LE | |
| > | GT | |
| >= | GE | |
| != | NE | |
| == | EQ | |
| = | ASSIGN | |
| ( | LPAREN | |
| ) | RPAREN | |
| { | LBRACE | |
| } | RBRACE | |
| [ | LBRACKET | |
| ] | RBRACKET | |
| , | COMMA | |
| ; | SEMI | |
|int | INT | |
|void | VOID | |
|if | IF | |
|else | ELSE | |
|while | WHILE | |
|return | RETURN | |
|printf | PRINTF | |



## 4.程序举例

```c
int c[10];
int d;
void main()
{
    int e;
    e=1;
    if(e==1){
        e=2;
    }
    else{
        e=3;
    }
    while(e<10){
        e=e+1;
    }
    switch(e)
    {
        case 1:e=1;
        case 2:e=2;
        default:e=3;
    }
    return;
}
```

## 5.各部分的任务

### 词法分析

识别出程序中的各个单词，包括关键字、标识符、常量、运算符、界符等。

## 语法分析

分析程序的语法结构，判断程序是否符合文法规则。

## 语义分析

将语法分析的结果转换为四元组或者汇编代码。