#pragma once

#include <string>
#include <variant>
#include <optional>

namespace eweda::token {

  enum class Token_Type {
    // Single character
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACKET, RIGHT_BRACKET, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, STAR, SLASH, SEMICOLON,

    // One or two character
    PLUS, PLUS_PLUS,
    MINUS, MINUS_MINUS,
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    AND, AND_AND, // These correspond to the symbols, not the words.
    OR, OR_OR,    // `and` and `or` are both used to refer to the keyboard symbols anyway.

    // Literals
    STRING_LITERAL, INTEGER_LITERAL, FLOAT_LITERAL, BOOLEAN_LITERAL, NULL_LITERAL,

    // Keywords
    BREAK, ELSE, FOR, IF, LET, PRINT, RETURN, WHILE,

    IDENTIFIER,

    END_OF_FILE
  };

  // No value is the same as a null literal.
  using Literal = std::optional<std::variant<std::string, int, double, bool>>;

  struct Token {
    const Token_Type type;
    const std::string lexeme;
    const Literal literal {};
    const size_t line; // Line number of the program at which the token appears.

    Token (const Token_Type type, const std::string &lexeme, const Literal &literal, const size_t line);

    Token (const Token_Type type, const std::string &lexeme, const size_t line);
  };

  std::string to_string (const Literal &literal);

  std::string to_string (const Token &token);

} // namespace eweda::token
