#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "data.h"
#include "decl.h"

static int chrpos(char *s, int c) {
  char *p;
  p = strchr(s, c);
  return (p ? p - s : -1);
}

static int next(void) {
  int c;

  if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);
  if (c == '\n') {
    Line++;
  }
  return c;
}

static void putback(int c) {
  Putback = c;
}

int skip() {
  int c;
  c = next();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
    c = next();
  }
  return c;
}

int scanint(int c) {
  int val = 0, k = 0;
  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }
  putback(c);

  return val;
}

int scan(struct token *t) {
  int c;
  c = skip();
  switch (c) {
    case EOF:
      return 0;
    case '+':
      t->token = T_PLUS;
      break;
    case '-':
      t->token = T_MINUS;
      break;
    case '*':
      t->token = T_STAR;
      break;
    case '/':
      t->token = T_SLASH;
      break;

    default:
      if (isdigit(c)) {
        t->token = T_INTLIT;
        t->intvalue = scanint(c);
        break;
      }

      printf("Unrecognised character \'%c\' on line %d\n", c, Line);
      exit(EXIT_FAILURE);
  }

  return 1;
}