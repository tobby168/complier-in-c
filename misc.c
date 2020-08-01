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

// Match a semicolon and fetch the next token
void semi(void) {
  match(T_SEMI, ";");
}

// Match an identifer and fetch the next token
void ident(void) {
  match(T_IDENT, "identifier");
}

// Print out fatal messages, and exit with code 1
void fatal(char *s) {
  fprintf(stderr, "%s on line %d\n", s, Line); 
  exit(EXIT_FAILURE);
}

void fatals(char *s1, char *s2) {
  fprintf(stderr, "%s:%s on line %d\n", s1, s2, Line); 
  exit(EXIT_FAILURE);
}

void fatald(char *s, int d) {
  fprintf(stderr, "%s:%d on line %d\n", s, d, Line);
  exit(EXIT_FAILURE);
}

void fatalc(char *s, int c) {
  fprintf(stderr, "%s:%c on line %d\n", s, c, Line);
  exit(EXIT_FAILURE);
}