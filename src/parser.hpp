#pragma once

#include <vector>
#include <string>

#include "token.hpp"
#include "ast.hpp"

namespace eweda::parser {

  class Parser {
  private:
    const std::vector<token::Token> tokens;
    size_t current {0};

    token::Token peek (const int offset = 0) const;
    // Returns true and increments currrent if the type of the current token is one of types.
    bool consume_if (const std::vector<token::Token_Type> &types);
    // Consumes if the current token matches the type, otherwise it is an error 
    token::Token consume (const token::Token_Type &type, const std::string &message);
    // Consumes the current token. If it is at the end, then doesn't move forward.
    token::Token consume ();
    
    // Calling any one of these functions will return an AST node that has everything starting from current,
    // to the first token that has a lower precedence (meaning higher up in list of declarations).
    
    // e.g. factor will parse primary, unary expressions, and `*` and `/` starting at current,
    // but it will not parse anything lower precedence, so it will stop at a `+` or `-` or anything else, with current pointing to it.
    ast::Node_Ptr parse_expression ();
    ast::Node_Ptr parse_equality ();
    ast::Node_Ptr parse_comparison ();
    ast::Node_Ptr parse_term ();
    ast::Node_Ptr parse_factor ();
    ast::Node_Ptr parse_unary ();
    ast::Node_Ptr parse_primary ();
    
  public:
    Parser (const std::vector<token::Token> &tokens);

    ast::Node_Ptr parse ();
  };
  
} // namespace eweda::parser
