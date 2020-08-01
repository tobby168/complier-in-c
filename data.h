#ifndef extern_
#define extern_ extern
#endif

// Global variables
extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct token	Token;
extern_ char Text[TEXTLEN + 1];

#define NSYMBOLS 1024 // Numbers of symbol table entries
extern_ struct symtable Gsym[NSYMBOLS]; // Global symbol table
