#pragma once

#include <vector>
#include <string>

#include "token.hpp"
#include "error.hpp"

namespace eweda::lexer {
  
  class Lexer {
  private:
    const std::string src;
    std::vector<token::Token> tokens {};
    // The start of the lexeme being tokenized.
    size_t start {0};
    // The current character being considered.
    size_t current {0};
    // The line number the current lexeme.
    size_t line {1};

    // Return the current character and move on to the next one. Assumes that current is valid.
    char consume ();
    // Consume the current character if it matches the one expected. null if current is out of bounds, or it doesn't match.
    char consume_if (const char expected);
    // Returns the current character. null char if current is out of bounds.
    char peek (const size_t offset = 0) const;

    void add_token (const token::Token_Type type);
    void add_token (const token::Token_Type type, const token::Literal &literal);

    void scan_token ();
    void identifier ();
    void string_literal ();
    void number_literal ();
    void comment ();
    
  public:
    Lexer (const std::string &src);

    std::vector<token::Token> tokenize ();
  };
  
} // namespace ewedad::lexer
