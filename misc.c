#include "defs.h"
#include "data.h"
#include "decl.h"

// Ensure that the current token is t,
// and fetch the next token.
void match(int t, char *what) {
  if (t == Token.token) {
    scan(&Token);
  }
  else {
    printf("%s expected on line %d\n", what, Line);
    exit(EXIT_FAILURE);
  }
}

void semi(void) {
  match(T_SEMI, ";");
}