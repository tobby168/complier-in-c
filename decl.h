// Function prototypes for all compiler files
int scan(struct token *t);

struct ASTnode *mkastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int ptp);

//gen.c
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);
int interpretAST(struct ASTnode *n);
int genAST(struct ASTnode *n, int reg);
void genglobsym(char *s);

//cg.c
void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgloadint(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
void cgglobsym(char *sym);
int cgloadglob(char *identifier);
int cgstorglob(int r, char *identifier);
int cgequal(int r1, int r2);
int cgnotequal(int r1, int r2);
int cglessthan(int r1, int r2);
int cggreaterthan(int r1, int r2);
int cglessequal(int r1, int r2);
int cggreaterequal(int r1, int r2);

//misc.c
void match(int t, char *what);
void semi(void);
void ident(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

//stmt.c
void statements(void);

//sym.c
int findglob(char *s);
int addglob(char *name);

//decl.c
void var_declaration();