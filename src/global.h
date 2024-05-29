#define MAX_SIZE  128 * 1024 * 8
#define int long long int
enum{
ID=256,NUM,STRING,
ASSIGN,OR,AND,EQ,NE,LT,GT,LE,GE,PLUS,NOT,MINUS,MUL,DIV,INC,DEC,BRAK,
INT,VOID,CHAR,IF,ELSE,WHILE,RETURN,MAIN,PRINTF,PTR,FUN
};
enum{
Assign,Or,And,Eq,Ne,Lt,Gt,Le,Ge,Plus,Not,Minus,Mul,Div,Inc,Dec,Jump,Jnz,Call,
Tmp,Addr
};
//cal   ||  op     ||    arg1   ||   arg2   ||   tmp_arg
//cal   ||  call   ||    argc   ||   argv   ||   func_addr
//jnz   ||  jnz    ||    arg1   ||    _     ||   addr
//jump  ||  jump   ||    _      ||    _     ||   addr
//assign||  assign ||    arg1   ||          ||   result
typedef struct{
    int Token;
    char* Name;
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
    int arg2_type;
    int arg2_value;
    int result_type;
    int result_value;
} CODE;
extern int token;
extern int token_val;
extern char* src;
extern int line;
extern char *data;
extern CODE *code;
extern int tmp_arg;
extern symbol *symbol_table;
extern symbol *current_symbol;
extern CODE *idmain;
extern void GetToken();
extern void Keyword();
extern void program();