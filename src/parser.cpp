#include "parser.hpp"

#include <vector>
#include <string>
#include <variant>
#include <memory>

#include "token.hpp"
#include "error.hpp"
#include "ast.hpp"

namespace eweda::parser {

  using token::Token_Type;
  
  Parser::Parser (const std::vector<token::Token> &tokens) :
    tokens {tokens} {}

  ast::Node_Ptr Parser::parse () {
    return parse_expression();
  }

  ast::Node_Ptr Parser::parse_expression () {
    return parse_equality();
  }

  ast::Node_Ptr Parser::parse_equality () {
    // equality -> comparison (("==" | "!=") comparison)*
    // One comparison, and then any number of further equalities chained on.
    
    // The right hand side, guaranteed to exist.
    ast::Node_Ptr expr {parse_comparison()};

    // Checking if there is another equality.
    while (consume_if({Token_Type::BANG_EQUAL, Token_Type::EQUAL_EQUAL})) {
      // The operation.
      const token::Token op {peek(-1)};
      // The right hand side.
      ast::Node_Ptr right {parse_comparison()};

      expr = std::make_unique<ast::Node>(std::in_place_type<ast::Binary>,
					 std::move(expr),  // left
					 std::move(right), // right
					 op);              // token
    }

    return expr;
  }

  ast::Node_Ptr Parser::parse_comparison () {
    // comparison -> term ((">" | ">=" | "<" | "<=") term)*
    // One term, then any number of further comparisons of terms chained on.

    ast::Node_Ptr expr {parse_term()};

    while (consume_if({Token_Type::GREATER, Token_Type::GREATER_EQUAL, Token_Type::LESS, Token_Type::LESS_EQUAL})) {
      const token::Token op {peek(-1)};
      ast::Node_Ptr right {parse_comparison()};

      expr = std::make_unique<ast::Node>(std::in_place_type<ast::Binary>,
					 std::move(expr),  // left
					 std::move(right), // right
					 op);              // token
    }

    return expr;
  }

  ast::Node_Ptr Parser::parse_term () {
    // term -> factor (("+" | "-") factor)*
    // One factor, then any sum/subtraction of factors chained on.

    ast::Node_Ptr expr {parse_factor()};

    while (consume_if({Token_Type::PLUS, Token_Type::MINUS})) {
      const token::Token op {peek(-1)};
      ast::Node_Ptr right {parse_factor()};

      expr = std::make_unique<ast::Node>(std::in_place_type<ast::Binary>,
					 std::move(expr),  // left
					 std::move(right), // right
					 op);              // token
    }

    return expr;
  }

  ast::Node_Ptr Parser::parse_factor () {
    // factor -> unary (("*" | "/") unary)*
    // One unary, then any product/divison of unaries chained on.

    ast::Node_Ptr expr {parse_unary()};

    while (consume_if({Token_Type::STAR, Token_Type::SLASH})) {
      const token::Token op {peek(-1)};
      ast::Node_Ptr right {parse_unary()};

      expr = std::make_unique<ast::Node>(std::in_place_type<ast::Binary>,
					 std::move(expr),  // left
					 std::move(right), // right
					 op);              // token
    }

    return expr;
  }

  ast::Node_Ptr Parser::parse_unary () {
    // unary -> ("!" | "-") unary | primary
    // Either a unary operator in front of a unary, or just a primary.

    // If there was a prefix operation,
    if (consume_if({Token_Type::BANG, Token_Type::MINUS})) {
      // Then consume another unary.
      const token::Token op {peek(-1)};
      ast::Node_Ptr right {parse_unary()};

      return std::make_unique<ast::Node>(std::in_place_type<ast::Unary>,
					 std::move(right), // right
					 op);              // token

    }

    // If there wasn't a prefix operation, then it must be a unary postfix (or something of higher precedence).
    return parse_primary();
  }

  ast::Node_Ptr Parser::parse_primary () {
    // Literal value.
    if (consume_if({Token_Type::STRING_LITERAL, Token_Type::INTEGER_LITERAL, Token_Type::FLOAT_LITERAL, Token_Type::BOOLEAN_LITERAL, Token_Type::NULL_LITERAL}))
      return std::make_unique<ast::Node>(std::in_place_type<ast::Literal>,
					 peek(-1).literal); // value. Since this is an optional, it can have no value, which corresponds to a null literal.
    
    if (consume_if({Token_Type::LEFT_PAREN})) {
      // If there is an open parenthesis, then parse the expression within and expect a close parenthesis after it.
      ast::Node_Ptr expr {parse_expression()};
      consume(Token_Type::RIGHT_PAREN, "Expect `)` after expression.");
      return std::make_unique<ast::Node>(std::in_place_type<ast::Group>,
					 std::move(expr)); // expr

    }

    error::parse_error(peek(), "I have no idea what happened here");
    return nullptr;
  }

  bool Parser::consume_if (const std::vector<Token_Type> &types) {
    for (const auto type : types) {
      if (peek().type == type) {
	consume();
	return true;
      }
    }

    return false;
  }

  token::Token Parser::consume (const token::Token_Type &type, const std::string &message) {
    if (peek().type == type) return consume();

    error::parse_error(peek(), message);
    std::cerr << "figure this out later\n";
    exit(EXIT_FAILURE);
  }

  token::Token Parser::consume () {
    if (peek().type != Token_Type::END_OF_FILE) current++;
    return peek(-1);
  }
  
  token::Token Parser::peek (const int offset) const {
    return tokens[current + offset];
  }
  
} // namespace eweda::parser
