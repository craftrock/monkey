#include "lexer.h"
#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void lexer_read_char(Lexer *lexer);
bool is_letter(char ch);
const char *lexer_read_identifier(Lexer *lexer, size_t *out_length);
void lexer_skip_whitespace(Lexer *lexer);

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

	lexer_skip_whitespace(lexer);

	switch (lexer->ch) {
	case '=':
		tok = token_new(TOKEN_ASSIGN, &lexer->ch, 1);
		break;
	case ';':
		tok = token_new(TOKEN_SEMICOLON, &lexer->ch, 1);
		break;
	case '(':
		tok = token_new(TOKEN_LPAREN, &lexer->ch, 1);
		break;
	case ')':
		tok = token_new(TOKEN_RPAREN, &lexer->ch, 1);
		break;
	case ',':
		tok = token_new(TOKEN_COMMA, &lexer->ch, 1);
		break;
	case '+':
		tok = token_new(TOKEN_PLUS, &lexer->ch, 1);
		break;
	case '{':
		tok = token_new(TOKEN_LBRACE, &lexer->ch, 1);
		break;
	case '}':
		tok = token_new(TOKEN_RBRACE, &lexer->ch, 1);
		break;
	case 0:
		tok = token_new(TOKEN_EOF, "", 0);
		break;
	default:
		if (is_letter(lexer->ch)) {
			tok.literal = lexer_read_identifier(lexer, &tok.length);
			tok.type = lookup_identifier_token_type(tok.literal);
			return tok;
		} else {
			tok = token_new(TOKEN_ILLEGAL, &lexer->ch, 1);
		}
	};

	lexer_read_char(lexer);
	return tok;
}

void lexer_free(Lexer *p) {
	if (p) {
		free(p);
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
	size_t position = lexer->position;
	while (is_letter(lexer->ch)) {
		lexer_read_char(lexer);
	}
	*out_length = lexer->position - position + 1;
	return &lexer->input[position];
}

void lexer_skip_whitespace(Lexer *lexer) {
	while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' ||
	       lexer->ch == '\r') {
		lexer_read_char(lexer);
	}
}

bool is_letter(char ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == ' ';
}
