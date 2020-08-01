#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN	512

// Structure and enum definitions
// token types
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_EQUALS, T_IDENT,
  // Keywords
  T_PRINT, T_INT
};

struct token {
  int token;
  int intvalue;
};

// AST node types
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT,
  A_IDENT, A_LVIDENT, A_ASSIGN
};

struct ASTnode {
  int op; // operator to be performed in the tree
  struct ASTnode *left;
  struct ASTnode *right;
  union {
    int intvalue; // For A_INTLIT, the integer value
    int id; // For A_IDENT, the symbol slot number
  } v;
};

// structure of symbol table
struct symtable {
  char *name;
};
