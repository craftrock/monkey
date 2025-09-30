CC=gcc
CFLAGS= -Wall -Wextra -Wno-microsoft-anon-tag -std=c23 -fms-extensions -D_GNU_SOURCE -g
LIBS= -lcheck -lm -lpthread -lrt
SRC_DIR=src
TEST_DIR=tests
BUILD_DIR=build
SOURCES=$(SRC_DIR)/lexer.c $(SRC_DIR)/token.c $(SRC_DIR)/repl.c

all: $(BUILD_DIR)/monkey

$(BUILD_DIR)/monkey: $(SRC_DIR)/main.c $(SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test: $(BUILD_DIR)/test_lexer
	$(BUILD_DIR)/test_lexer

$(BUILD_DIR)/test_lexer: $(TEST_DIR)/test_lexer.c $(SRC_DIR)/lexer.c $(SRC_DIR)/token.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean
