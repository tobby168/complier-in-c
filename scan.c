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
    case 'e':
      if (!strcmp(s, "else"))
      return T_ELSE;
    case 'i':
      if (!strcmp(s, "int"))
        return T_INT;
      if (!strcmp(s, "if"))
        return T_IF;
    case 'p':
      if (!strcmp(s, "print"))
	      return T_PRINT;
    case 'w':
      if (!strcmp(s, "while"))
        return T_WHILE;
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
    case '{':
      t->token = T_LBRACE;
      break;
    case '}':
      t->token = T_RBRACE;
      break;
    case '(':
      t->token = T_LPAREN;
      break;
    case ')':
      t->token = T_RPAREN;
      break;
    case '=':
      if ((c = next()) == '=') {
        t->token = T_EQ;
      }
      else {
        putback(c);
        t->token = T_ASSIGN;
      }
      break;
    case '!':
      if ((c = next()) == '=') {
        t->token = T_NE;
      }
      else {
        fatalc("Unrecognised character", c);
      }
      break;
    case '<':
      if ((c = next()) == '=') {
        t->token = T_LE;
      }
      else {
        putback(c);
        t->token = T_LT;
      }
      break;
    case '>':
      if ((c = next()) == '=') {
        t->token = T_GE;
      }
      else {
        putback(c);
        t->token = T_GT;
      }
      break;

    default:
      if (isdigit(c)) {
        t->token = T_INTLIT;
        t->intvalue = scanint(c);
        break;
      }
      else if (isalpha(c) || c == '_') {
        scanident(c, Text, TEXTLEN);
        // if no keyword identidied, keyword() return 0
        if ((tokentype = keyword(Text))) {
          t->token = tokentype;
          break;
        }
        t->token = T_IDENT;
        break;
      }

      printf("Unrecognised character \'%c\' on line %d\n", c, Line);
      exit(EXIT_FAILURE);
  }

  return 1;
}