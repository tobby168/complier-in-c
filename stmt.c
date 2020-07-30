#include "defs.h"
#include "data.h"
#include "decl.h"

// statements: statement
//      | statement statements
//      ;
//
// statement: 'print' expression ';'
//      ;

void statements(void) {
  struct ASTnode *tree;
  int reg;

  while (1) {
    match(T_PRINT, "print");

    tree = binexpr(0);
    reg = genAST(tree);
    genprintint(reg);
    genfreeregs();

    semi();
    if (Token.token == T_EOF)
      return;
  }

}