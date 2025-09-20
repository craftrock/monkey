#include "token.h"
#include <stddef.h>
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
