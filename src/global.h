#define MAX_SIZE  128 * 1024 * 8
#define int long long int
enum{
ID=256,NUM,STRING,
ASSIGN,OR,AND,EQ,NE,LT,GT,LE,GE,PLUS,NOT,MINUS,MUL,DIV,INC,DEC,BRAK,
INT,VOID,CHAR,IF,ELSE,WHILE,RETURN,MAIN,PRINTF,PTR,FUNC,LOC,GLO
};
//op
enum{
Assign =1000 ,Load,Or,And,Eq,Ne,Lt,Gt,Le,Ge,Plus,Not,Minus,Mul,Div,Inc,Dec,Jump,Jnz,Call,Print

};
//arg_type 
enum{CODE=-5, DATA, STACK,Tmp,Num};
//calc   ||  op     ||    arg1   ||   arg2   ||   tmp_arg
//call  ||  call   ||    param  ||   func_addr||   
//jnz   ||  jnz    ||    arg1   ||    _     ||   addr
//jump  ||  jump   ||    _      ||    _     ||   addr
//assign||  assign ||    arg1   ||          ||   result
//printf||  parintf||string_addr||   var    ||  
//load  || load    ||  tmp     ||      ||   result (when Tmp is a addr)
//对于赋值，对tmp的操作是store，对id的操作是assign
typedef struct{
    int Token;
    int Type;
    int Value;
    int Hash;
    int Class;
    int Btype;
    int Bclass;
    int Bvalue;
} symbol;
typedef struct{
    int op;
    int arg1_type;
    int arg1_value;
//type NUM,Tmp,Addr,Stack
    int arg2_type;
    int arg2_value;
    int result_type;
    int result_value;
} instr;
extern int token;
extern int token_val;
extern char* src;
extern int line;
extern char *data;
extern instr *code;
extern int tmp_arg;
extern symbol *symbol_table;
extern symbol *current_symbol;
extern instr *idmain;
extern void GetToken();
extern void Keyword();
extern void program();
void write_as();
instr *first_instr;
extern char *first_data;