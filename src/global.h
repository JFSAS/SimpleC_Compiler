#define MAX_SIZE  128 * 1024 * 8
#define DEBUG
typedef enum{ID=256,NUM,STRING,PLUS,MINUS,MUL,DIV,
LT,LE,GT,GE,NE,EQ,ASSIGN,LPAREN,RPAREN, LBRACE, 
RBRACE, LBRACKET, RBRACKET,COMMA,SEMI,QUOTE,INT,
VOID,IF,ELSE,WHILE,RETURN,PRINTF} TokenType;
typedef struct{
    TokenType Token;
    char* name;
    int value;
    int Hash;
} symbol;
extern int token;
extern int token_val;
extern char* src;
extern int line;
extern char *data;
extern symbol *symbol_table;
extern symbol *sym_ptr;
extern void GetToken();
extern void Keyword();