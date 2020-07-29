#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Structure and enum definitions
// token types
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

struct token {
  int token;
  int intvalue;
};

// AST node types
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

struct ASTnode {
  int op; // operator to be performed in the tree
  struct ASTnode *left;
  struct ASTnode *right;
  int intvalue;
};