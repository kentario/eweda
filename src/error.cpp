#include "error.hpp"

#include <iostream>
#include <string>

#include "token.hpp"

namespace eweda::error {

  bool had_error {false};
  
  void error (const std::string &message) {
    std::cerr << "error: " << message << '\n';
    had_error = true;
  }

  void lexer_error (const size_t line, const std::string &message) {
    std::cerr << "line " << line << ": lexer error: " << message << '\n';
    had_error = true;
  }

  void parse_error (const token::Token &token, const std::string &message) {
    if (token.type == token::Token_Type::END_OF_FILE) {
      std::cerr << "line " << token.line << ": parse error at end: " << message << '\n';
    } else {
      std::cerr << "line " << token.line << ": parse error: " << message << '\n';
    }
  }

} // namespace eweda::error
