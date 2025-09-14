CC=gcc
CFLAGS= -Wall -Wextra -std=c23 -g
LIBS= -lcheck -lm -lpthread -lrt

SRC_DIR=src
TEST_DIR=tests

test: test_lexer
	./test_lexer

test_lexer: $(TEST_DIR)/test_lexer.c $(SRC_DIR)/lexer.c $(SRC_DIR)/token.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f test_*

.PHONY: test clean
