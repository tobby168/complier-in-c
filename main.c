#include <stdio.h>
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <string.h>
#include <errno.h>

static char *tokstr[] = { "+", "-", "*", "/", "intlit" };

static void init() {
  Line = 1;
  Putback = '\n';
}

static void scanfile() {
  struct token T;
  while (scan(&T)) {
    printf("Token: %s", tokstr[T.token]);
    if (T.token == T_INTLIT) {
      printf(", Value: %d", T.intvalue);
    }
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  init();
  
  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  scanfile();

  if (fclose(Infile) == EOF) {
    fprintf(stderr, "Unable to close file stream %s: %s\n", argv[1], strerror(errno));
  }
  exit(EXIT_SUCCESS);
}