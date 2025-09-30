#include "repl.h"
#include "../lexer/lexer.h"
#include "../token/token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const char *REPL_PROMPT = ">> ";

void repl_start(FILE *in, FILE *out) {
  char buf[512];
  for (;;) {
    fputs(REPL_PROMPT, out);

    char *line;
    size_t length;
    getline(&line, &length, in);

    Lexer *lexer = lexer_new(line);
    for (Token token = lexer_next_token(lexer); token.type != TOKEN_EOF;
         token = lexer_next_token(lexer)) {
      token_sprintf(buf, sizeof(buf), token);
      fputs(buf, out);
    }

    lexer_free(lexer);
    free(line);
  }
}
