# 研究性文法——实现c语言的子程序的编译器

## 1. 问题描述

实现C语言子集的编译器，包括词法分析、语法分析、语义分析、中间代码生成、目标代码生成等功能。包含整型、函数的声明、赋值语句、if else语句、while语句、数组，支持//注释不支持/*... */注释。

## 2. 文法定义

``` ebnf
<NUM> ::= <digit>,{<digit>};
<digital> ::= 0|1|2|3|4|5|6|7|8|9;
<ID> ::= <letter>,{(<letter>|<digit>)};
<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z;
<string> ::= '"' <character> , {<character>}'"'; 
<character> ::= (*ALL ASCII CHARACTERS EXCEPT *);
<program> ::= {<declaration>};
<declaration> ::= <var-declaration> | <fun-declaration>;
<var-declaration> ::= <type> ['*'] ID ['['NUM']'] {',' ID ['['NUM']']};
<fun-declaration> ::= <type> ['*'] ID '(' <params> ')' '{' <body_decl> '}';
<type> ::= int | void | char;
<params> ::= void | type ['*'] ID {',' type ['*'] ID};
<body_decl> ::={var-declarations>}, {<statement>};
<statement> ::= <selection-stam> | <iteration-list> | <return_stam> | <print_stam> | <expression> ';';
<selection-stam> ::= 'if' '('<expression>')' '{'{<statement>}'}' | 'if' (<expression>) '{'{<statements>}'}' 'else' '{' {<statements>}'}';
<iteration-stam> ::= 'while' '(' <expression> ')' '{'<statements>'}';
<return-stam> ::= 'return'';' | return <expression>';';
<print-stam> ::= 'printf''('<string>')'';' | 'printf''('<var>')'';';
<expression> ::= [<var> '='] <or_expression> ';';
<var> ::= ID | ID[<expression>] ;
<or_expression> ::= <and_expression> '||', <or_expression> | <and_expression>;
<and_expression> ::= <simple_expression> '&&' <and_expression> | <simple_expression>;
<simple_expresion> ::= <additive_expression> <relop> <additive_expression> | <additive_expression>;
<relop> ::= <= | < | > | >= | == | != ;
<additive-expression> ::= <term> <addop> <additive_expression> | <term>;
<addop> ::= + | -;
<term> ::= <factor> <mulop> <term> | <factor>;
<mulop> ::= * | /;
<factor> ::= ( <expression> ) | <var> | NUM | <call>;
<call> ::= ID ( <args> )
<args> ::= <arg-list> | <empty>
<arg-list> ::= <arg-list> , <expression> | <expression>
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

### 静态语义检查
- 有无重复定义 complicated define
- 未定义的变量或函数 undefined id
- 赋值类型检查 type error
- 
## 学习参考

- [「700行手写编译器」Part 1：项目背景与设计思路](https://www.bilibili.com/video/BV1Kf4y1V783/?spm_id_from=333.337.search-card.all.click&vd_source=f1b40d4c8a7cccb5d8d3c3fae7ed593e)bilibili
- [手把手教你构建 C 语言编译器](https://lotabout.me/2015/write-a-C-interpreter-0/)blog
- [重构c4项目仓库](https://github.com/lotabout/write-a-C-interpreter)
