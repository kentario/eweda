#include "error.hpp"

#include <iostream>
#include <string>

namespace eweda::error {

  bool had_error {false};
  
  void error (const std::string &message) {
    std::cerr << "error: " << message << '\n';
    had_error = true;
  }

  void lexer_error (const size_t line, const std::string &message) {
    std::cerr << "lexer error at ["  << line << "]: " << message << '\n';
    had_error = true;
  }

} // namespace eweda::error
