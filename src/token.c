#include "token.h"
#include <string.h>

Token token_create(TokenType type, const char *literal) {
	return (Token){
		.type = type,
		.literal = literal,
		.length = strlen(literal)
	};
}