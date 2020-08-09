#include "defs.h"
#include "data.h"
#include "decl.h"

struct ASTnode *mkastnode(int operator, struct ASTnode *left, 
                          struct ASTnode *mid,
                          struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to malloc in mkASTnode");
    exit(EXIT_FAILURE);
  }

  n->op = operator;
  n->left = left;
  n->mid = mid;
  n->right = right;
  n->v.intvalue = intvalue;
  
  return n;
}

// Make an AST leaf node
struct ASTnode *mkastleaf(int op, int intvalue) {
  return (mkastnode(op, NULL, NULL, NULL, intvalue));
}

// Make a unary AST node: only one child
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue) {
  return (mkastnode(op, left, NULL, NULL, intvalue));
}