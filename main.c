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

  // Create the output file
  if ((Outfile = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  }

  scan(&Token);			// Get the first token from the input
  genpreamble();
  statements();
  genpostamble();

  if (fclose(Infile) == EOF) {
    fprintf(stderr, "Unable to close file stream %s: %s\n", argv[1], strerror(errno));
  }
  if (fclose(Outfile) == EOF) {
    fprintf(stderr, "Unable to close Outfile stream: %s\n", strerror(errno));
  }
  exit(EXIT_SUCCESS);
}