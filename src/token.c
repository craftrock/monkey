#include "token.h"
#include <stddef.h>
#include <string.h>

Token token_new(TokenType type, const char *literal, size_t length) {
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
    {"fn", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {NULL, TOKEN_IDENT}, // sentinel value
};

TokenType lookup_identifier_token_type(const char *identifier) {
	for (size_t i = 0; keywords[i].keyword != NULL; i++) {
		if (strcmp(keywords[i].keyword, identifier) == 0) {
			return keywords[i].type;
		}
	}

	return TOKEN_IDENT;
}
