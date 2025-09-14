#pragma once

#include <stddef.h>
typedef enum {
	TOKEN_ILLEGAL,
	TOKEN_EOF,
	TOKEN_IDENT,
	TOKEN_INT,
	TOKEN_ASSIGN,
	TOKEN_PLUS,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_FUNCTION,
	TOKEN_LET,
} TokenType;

typedef struct {
	TokenType type;
	const char *literal;
	size_t length;
} Token;

const char *token_type_string(TokenType type);
Token token_new(TokenType type, const char *literal, size_t length);
Token token_create(TokenType type, const char *literal);
void token_free(Token *token);
