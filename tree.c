#include "defs.h"
#include "data.h"
#include "decl.h"

struct ASTnode *mkastnode(int operator, struct ASTnode *left, 
                          struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to malloc in mkASTnode");
    exit(EXIT_FAILURE);
  }

  n->op = operator;
  n->left = left;
  n->right = right;
  n->v.intvalue = intvalue;
  
  return n;
}

struct ASTnode *mkastleaf(int operator, int intvalue) {
  return mkastnode(operator, NULL, NULL, intvalue);
}

struct ASTnode *mkastunary(int operator, struct ASTnode *left, int intvalue) {
  return (mkastnode(operator, left, NULL, intvalue));
}