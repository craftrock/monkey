#pragma once

#include "../token/token.h"
#include <stddef.h>

typedef struct {
  char *input;
  size_t input_length;
  size_t position;
  size_t read_position;
  char ch;
} Lexer;

Lexer *lexer_new(char *input);
void lexer_free(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);
