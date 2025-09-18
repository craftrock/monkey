#pragma once

#include "token.h"
#include <stddef.h>

typedef struct {
	const char *input;
	size_t input_length;
	size_t position;
	size_t read_position;
	char ch;
} Lexer;

Lexer *lexer_new(const char *input);
void lexer_free(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);
