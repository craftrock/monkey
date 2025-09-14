#include "lexer.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>

void lexer_read_char(Lexer *lexer) {
	if (lexer->read_position >= lexer->input_length) {
		lexer->ch = 0;
	} else {
		lexer->ch = lexer->input[lexer->read_position];
	}

	lexer->position = lexer->read_position;
	lexer->read_position++;
}

Lexer *lexer_new(const char *input) {
	const size_t len = strlen(input);
	Lexer *lexer = malloc(sizeof(Lexer));
	*lexer = (Lexer){.input = input,
	                 .input_length = len,
	                 .position = 0,
	                 .read_position = 0,
	                 .ch = 0};
	lexer_read_char(lexer);
	return lexer;
}

Token lexer_next_token(Lexer *lexer) {
	Token tok;

	switch (lexer->ch) {
	case '=':
		tok = token_create(TOKEN_ASSIGN, "=");
		break;
	case ';':
		tok = token_create(TOKEN_SEMICOLON, ";");
		break;
	case '(':
		tok = token_create(TOKEN_LPAREN, "(");
		break;
	case ')':
		tok = token_create(TOKEN_RPAREN, ")");
		break;
	case ',':
		tok = token_create(TOKEN_COMMA, ",");
		break;
	case '+':
		tok = token_create(TOKEN_PLUS, "+");
		break;
	case '{':
		tok = token_create(TOKEN_LBRACE, "{");
		break;
	case '}':
		tok = token_create(TOKEN_RBRACE, "}");
		break;
	case 0:
		tok = token_create(TOKEN_EOF, "");
		break;
	};

	lexer_read_char(lexer);
	return tok;
}

void lexer_free(Lexer *p) {
	if (p) {
		free(p);
	}
}
