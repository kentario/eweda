#pragma once

#include <iostream>
#include <string>

namespace eweda::error {

  extern bool had_error;
  
  void error (const std::string &message);

  void lexer_error (const size_t line, const std::string &message);
    
} // namespace eweda::error
