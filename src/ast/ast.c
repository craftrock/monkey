#include "ast.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

char *ast_token_literal(const union ASTNode *node) {
  return node->base.token.literal;
}

char *ast_to_string(const union ASTNode *node) {
  switch (node->base.type) {
  case AST_NODE_IDENTIFIER:
    return strndup(node->identifier.token.literal,
                   node->identifier.token.length);
  case AST_NODE_LET_STATEMENT:
    char *result;
    asprintf(&result, "let %s = %s;", ast_to_string(node->let_statement.name),
             ast_to_string(node->let_statement.value));
    return result;
  case AST_NODE_PROGRAM:
    return strdup("program");
  default:
    assert(false); // this should not happen
  }
}
