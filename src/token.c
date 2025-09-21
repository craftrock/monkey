#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

Token token_new(const TokenType type, const char *literal,
                const size_t length) {
	return (Token){
	    .type = type,
	    .literal = literal,
	    .length = length,
	};
}

typedef struct {
	const char *keyword;
	TokenType type;
} KeywordEntry;

static const KeywordEntry keywords[] = {
    {"fn", TOKEN_FUNCTION},   {"let", TOKEN_LET},     {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},   {"if", TOKEN_IF},       {"else", TOKEN_ELSE},
    {"return", TOKEN_RETURN}, {nullptr, TOKEN_IDENT}, // sentinel value
};

TokenType lookup_identifier_token_type(const char *identifier,
                                       const size_t length) {
	for (size_t i = 0; keywords[i].keyword != nullptr; i++) {
		if (strncmp(keywords[i].keyword, identifier, length) == 0) {
			return keywords[i].type;
		}
	}

	return TOKEN_IDENT;
}

const char *token_type_string(TokenType type) {
	switch (type) {
	case TOKEN_ILLEGAL:
		return "ILLEGAL";
	case TOKEN_EOF:
		return "EOF";
	case TOKEN_IDENT:
		return "IDENT";
	case TOKEN_INT:
		return "INT";
	case TOKEN_ASSIGN:
		return "ASSIGN";
	case TOKEN_PLUS:
		return "PLUS";
	case TOKEN_MINUS:
		return "MINUS";
	case TOKEN_BANG:
		return "BANG";
	case TOKEN_ASTERISK:
		return "ASTERISK";
	case TOKEN_SLASH:
		return "SLASH";
	case TOKEN_LT:
		return "LT";
	case TOKEN_GT:
		return "GT";
	case TOKEN_EQ:
		return "EQ";
	case TOKEN_NOT_EQ:
		return "NOT_EQ";
	case TOKEN_COMMA:
		return "COMMA";
	case TOKEN_SEMICOLON:
		return "SEMICOLON";
	case TOKEN_LPAREN:
		return "LPAREN";
	case TOKEN_RPAREN:
		return "RPAREN";
	case TOKEN_LBRACE:
		return "LBRACE";
	case TOKEN_RBRACE:
		return "RBRACE";
	case TOKEN_FUNCTION:
		return "FUNCTION";
	case TOKEN_LET:
		return "LET";
	case TOKEN_IF:
		return "IF";
	case TOKEN_RETURN:
		return "RETURN";
	case TOKEN_ELSE:
		return "ELSE";
	case TOKEN_TRUE:
		return "TRUE";
	case TOKEN_FALSE:
		return "FALSE";
	default:
		return "UNKNOWN";
	}
}

int token_sprintf(char *buf, size_t buf_size, Token token) {
	return snprintf(buf, buf_size,
	                "Token{type=%s, literal=\"%.*s\", length=%zu\n",
	                token_type_string(token.type), (int)token.length,
	                token.literal, token.length);
}
