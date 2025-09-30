#pragma once

#include "../token/token.h"

union ASTNode;

typedef enum {
  AST_NODE_PROGRAM,
  AST_NODE_LET_STATEMENT,
  AST_NODE_IDENTIFIER,
} ASTNodeType;

typedef struct ASTNodeBase {
  ASTNodeType type;
  Token token;
} ASTNodeBase; // base struct to embed

typedef struct ASTIdentifier {
  ASTNodeBase;
} ASTIdentifier;

typedef struct ASTLetStatement {
  ASTNodeBase;
  union ASTNode *name;  // ASTIdentifier
  union ASTNode *value; // Expression node: e.g. integer literal
} ASTLetStatement;

typedef struct ASTProgram {
  ASTNodeBase; // NOTE: here token will be the first parsed token
  union ASTNode **statements;
} ASTProgram;

union ASTNode {
  ASTNodeBase base;
  ASTIdentifier identifier;
  ASTLetStatement let_statement;
};

char *ast_token_literal(const union ASTNode *node);
char *ast_to_string(const union ASTNode *node);
bool ast_is_statement(const union ASTNode *node);
bool ast_is_expression(const union ASTNode *node);

union ASTNode *ast_create_identifier(const Token token);
union ASTNode *ast_create_let_statement(const Token token,
                                        const ASTIdentifier *name,
                                        const union ASTNode *value);

void ast_free(union ASTNode *node);
