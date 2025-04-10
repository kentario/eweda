#include <iostream>
#include <string>

namespace eweda::error {

  bool had_error {false};
  
  void error (const std::string &message);

  void lexer_error (const size_t line, const std::string &message);
    
} // namespace eweda::error
