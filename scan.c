#include "defs.h"
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

static int scanident(int c, char *buf, int lim) {
  int i = 0;

  while (isalpha(c) || isnumber(c) || c == '_') {
    if (i == lim-1) {
      printf("identifier too long on line %d\n", Line);
      exit(EXIT_FAILURE);
    }
    else if (i < lim - 1) {
      buf[i++] = c;
    }
    c = next();
  }

  putback(c);
  buf[i] = '\0';
  return i;
}

static int keyword(char *s) {
  switch (*s) {
    case 'p':
      if (!strcmp(s, "print"))
	      return T_PRINT;
      break;
  }
  return 0;
}

int scan(struct token *t) {
  int c, tokentype;
  c = skip();
  switch (c) {
    case EOF:
      t->token = T_EOF;
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
    case ';':
      t->token = T_SEMI;
      break;

    default:
      if (isdigit(c)) {
        t->token = T_INTLIT;
        t->intvalue = scanint(c);
        break;
      }
      else if (isalpha(c) || c == '_') {
        scanident(c, Text, TEXTLEN);
        if ((tokentype = keyword(Text))) {
          t->token = tokentype;
          break;
        }
        printf("Unrecognised symbol %s on line %d\n", Text, Line);
	      exit(EXIT_FAILURE);
      }

      printf("Unrecognised character \'%c\' on line %d\n", c, Line);
      exit(EXIT_FAILURE);
  }

  return 1;
}