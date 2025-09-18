#include "../src/lexer.h"
#include "../src/token.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_next_token) {
	const char *input = "let five = 5;"
	                    "let ten = 10;"
	                    "let add = fn(x, y) {"
	                    "  x + y;"
	                    "};"
	                    "let result = add(five, ten);";
	struct {
		TokenType expected_type;
		const char *expected_literal;
	} tests[] = {
	    {TOKEN_LET, "let"},      {TOKEN_IDENT, "five"},  {TOKEN_ASSIGN, "="},
	    {TOKEN_INT, "5"},        {TOKEN_SEMICOLON, ";"}, {TOKEN_LET, "let"},
	    {TOKEN_IDENT, "ten"},    {TOKEN_ASSIGN, "="},    {TOKEN_INT, "10"},
	    {TOKEN_SEMICOLON, ";"},  {TOKEN_LET, "let"},     {TOKEN_IDENT, "add"},
	    {TOKEN_ASSIGN, "="},     {TOKEN_FUNCTION, "fn"}, {TOKEN_LPAREN, "("},
	    {TOKEN_IDENT, "x"},      {TOKEN_COMMA, ","},     {TOKEN_IDENT, "y"},
	    {TOKEN_RPAREN, ")"},     {TOKEN_LBRACE, "{"},    {TOKEN_IDENT, "x"},
	    {TOKEN_PLUS, "+"},       {TOKEN_IDENT, "y"},     {TOKEN_SEMICOLON, ";"},
	    {TOKEN_RBRACE, "}"},     {TOKEN_SEMICOLON, ";"}, {TOKEN_LET, "let"},
	    {TOKEN_IDENT, "result"}, {TOKEN_ASSIGN, "="},    {TOKEN_IDENT, "add"},
	    {TOKEN_LPAREN, "("},     {TOKEN_IDENT, "five"},  {TOKEN_COMMA, ","},
	    {TOKEN_IDENT, "ten"},    {TOKEN_RPAREN, ")"},    {TOKEN_SEMICOLON, ";"},
	    {TOKEN_EOF, ""},
	};

	Lexer *lexer = lexer_new(input);
	ck_assert_ptr_nonnull(lexer);

	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
		Token tok = lexer_next_token(lexer);
		printf("'%.*s'\n", (int)tok.length, tok.literal);
		ck_assert_str_eq(tok.literal, tests[i].expected_literal);
		ck_assert_int_eq(tok.type, tests[i].expected_type);
	}

	lexer_free(lexer);
}
END_TEST

START_TEST(test_lexer_new) {
	const char *input = "test";
	Lexer *lexer = lexer_new(input);

	ck_assert_ptr_nonnull(lexer);
	ck_assert_ptr_eq(lexer->input, input);
	ck_assert_int_eq(lexer->input_length, 4);
	ck_assert_int_eq(lexer->position, 0);
	ck_assert_int_eq(lexer->read_position, 1);
	ck_assert_int_eq(lexer->ch, 't');

	lexer_free(lexer);
}
END_TEST

START_TEST(test_empty_input) {
	Lexer *lexer = lexer_new("");
	ck_assert_ptr_nonnull(lexer);

	Token tok = lexer_next_token(lexer);
	ck_assert_int_eq(tok.type, TOKEN_EOF);
	ck_assert_str_eq(tok.literal, "");

	lexer_free(lexer);
}
END_TEST

Suite *lexer_suite(void) {
	Suite *s = suite_create("Lexer");
	TCase *tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_next_token);
	tcase_add_test(tc_core, test_lexer_new);
	tcase_add_test(tc_core, test_empty_input);

	suite_add_tcase(s, tc_core);
	return s;
}

int main(void) {
	Suite *s = lexer_suite();
	SRunner *sr = srunner_create(s);
	
	// Disable forking for debugging
	srunner_set_fork_status(sr, CK_NOFORK);
	
	srunner_run_all(sr, CK_NORMAL);
	int number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : 1;
}
