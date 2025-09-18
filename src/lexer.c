#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void lexer_read_char(Lexer *lexer);
bool is_letter(char ch);
const char *lexer_read_identifier(Lexer *lexer, size_t *out_length);
void lexer_skip_whitespace(Lexer *lexer);

Lexer *lexer_new(const char *const input) {
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
	lexer_skip_whitespace(lexer);

	TokenType ttype;
	switch (lexer->ch) {
	case '=':
		ttype = TOKEN_ASSIGN;
		break;
	case ';':
		ttype = TOKEN_SEMICOLON;
		break;
	case '(':
		ttype = TOKEN_LPAREN;
		break;
	case ')':
		ttype = TOKEN_RPAREN;
		break;
	case ',':
		ttype = TOKEN_COMMA;
		break;
	case '+':
		ttype = TOKEN_PLUS;
		break;
	case '{':
		ttype = TOKEN_LBRACE;
		break;
	case '}':
		ttype = TOKEN_RBRACE;
		break;
	case 0:
		ttype = TOKEN_EOF;
		break;
	default:
		if (is_letter(lexer->ch)) {
			size_t length;
			const char *literal = lexer_read_identifier(lexer, &length);
			ttype = lookup_identifier_token_type(literal, length);
			return token_new(ttype, literal, length);
		}

		ttype = TOKEN_ILLEGAL;
	};

	const Token token = token_new(ttype, &lexer->input[lexer->position], 1);
	lexer_read_char(lexer);
	return token;
}

void lexer_free(Lexer *lexer) {
	if (lexer) {
		free(lexer);
	}
}

void lexer_read_char(Lexer *lexer) {
	if (lexer->read_position >= lexer->input_length) {
		lexer->ch = 0;
	} else {
		lexer->ch = lexer->input[lexer->read_position];
	}

	lexer->position = lexer->read_position;
	lexer->read_position++;
}

const char *lexer_read_identifier(Lexer *lexer, size_t *out_length) {
	const size_t position = lexer->position;
	while (is_letter(lexer->ch)) {
		lexer_read_char(lexer);
	}
	*out_length = lexer->position - position;
	return &lexer->input[position];
}

void lexer_skip_whitespace(Lexer *lexer) {
	while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' ||
	       lexer->ch == '\r') {
		lexer_read_char(lexer);
	}
}

bool is_letter(const char ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}
