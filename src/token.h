#pragma once

#include <stddef.h>

typedef enum {
	TOKEN_ILLEGAL,
	TOKEN_EOF,
	TOKEN_IDENT,
	TOKEN_INT,
	TOKEN_ASSIGN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_BANG,
	TOKEN_ASTERISK,
	TOKEN_SLASH,
	TOKEN_LT,
	TOKEN_GT,
	TOKEN_EQ,
	TOKEN_NOT_EQ,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_FUNCTION,
	TOKEN_LET,
	TOKEN_IF,
	TOKEN_RETURN,
	TOKEN_ELSE,
	TOKEN_TRUE,
	TOKEN_FALSE,
} TokenType;

typedef struct {
	TokenType type;
	const char *const literal;
	size_t length;
} Token;

const char *token_type_string(TokenType type);
Token token_new(TokenType type, const char *literal, size_t length);
TokenType lookup_identifier_token_type(const char *identifier,
                                       const size_t length);
