#pragma once

#include <vector>

#include "token.hpp"
#include "ast.hpp"

namespace eweda::parser {

  class Parser {
  private:
    const std::vector<token::Token> tokens;
    size_t current {0};
    
  public:
    Parser (const std::vector<token::Token> &tokens);

    ast::Node_Ptr parse ();
  };
  
} // namespace eweda::parser
