#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

static char *tokstr[] = { "+", "-", "*", "/", "intlit" };

static void init() {
  Line = 1;
  Putback = '\n';
}

int main(int argc, char* argv[]) {
  struct ASTnode *n;

  init();
  
  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  scan(&Token);			// Get the first token from the input
  n = binexpr();		// Parse the expression in the file
  printf("%d\n", interpretAST(n));

  if (fclose(Infile) == EOF) {
    fprintf(stderr, "Unable to close file stream %s: %s\n", argv[1], strerror(errno));
  }
  exit(EXIT_SUCCESS);
}