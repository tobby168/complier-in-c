#include "defs.h"
#include "data.h"
#include "decl.h"

int arithop(int tokentype) {
  if (tokentype > T_EOF && tokentype < T_INTLIT) {
    return tokentype;
  }
  fatald("Syntax error, token", tokentype);
  return -1;
}

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode *primary(void) {
  struct ASTnode *n;
  int id;

  switch (Token.token) {
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      break;

    case T_IDENT:
      if ((id = findglob(Text)) == -1)
        fatals("Unknown variable", Text);
      n = mkastleaf(A_IDENT, id);
      break;

    default:
      fatald("Syntax error, token", Token.token);
  }

  scan(&Token);
  return n;
}

// Operator precedence for each token. Must
// match up with the order of tokens in defs.h
static int OpPrec[] = {
  0, 10, 10,			// T_EOF, T_PLUS, T_MINUS
  20, 20,			// T_STAR, T_SLASH
  30, 30,			// T_EQ, T_NE
  40, 40, 40, 40		// T_LT, T_GT, T_LE, T_GE
};

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
  return (prec);
}

struct ASTnode *binexpr(int ptp) {
  struct ASTnode *left, *right;
  int tokentype;

  left = primary();
  
  tokentype = Token.token;
  if (tokentype == T_SEMI) {
    return left;
  }

  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    right = binexpr(OpPrec[tokentype]);
    left = mkastnode(arithop(tokentype), left, right, 0);
    tokentype = Token.token;
    if (tokentype == T_SEMI)
      break;
  }

  return left;
}
