#pragma once

#include <iostream>
#include <string>

#include "token.hpp"

namespace eweda::error {

  extern bool had_error;

  // error: message
  void error (const std::string &message);

  // line line: lexer error: message
  void lexer_error (const size_t line, const std::string &message);

  // line line: parse error at end: message
  // line line: parse error: message
  void parse_error (const token::Token &token, const std::string &message);
    
} // namespace eweda::error
