#include "token.hpp"

#include <unordered_map>
#include <map>
#include <type_traits>

namespace eweda::token {

  const std::unordered_map<Token_Type, std::string> token_to_string {
    {Token_Type::LEFT_PAREN,      "LEFT_PAREN"},
    {Token_Type::RIGHT_PAREN,     "RIGHT_PAREN"},
    {Token_Type::LEFT_BRACKET,    "LEFT_BRACKET"},
    {Token_Type::RIGHT_BRACKET,   "RIGHT_BRACKENT"},
    {Token_Type::LEFT_BRACE,      "LEFT_BRACE"},
    {Token_Type::RIGHT_BRACE,     "RIGHT_BRACE"},
    {Token_Type::COMMA,           "COMMA"},
    {Token_Type::DOT,             "DOT"},
    {Token_Type::STAR,            "STAR"},
    {Token_Type::SLASH,           "SLASH"},
    {Token_Type::SEMICOLON,       "SEMICOLON"},
    {Token_Type::PLUS,            "PLUS"},
    {Token_Type::PLUS_PLUS,       "PLUS_PLUS"},
    {Token_Type::MINUS,           "MINUS"},
    {Token_Type::MINUS_MINUS,     "MINUS_MINUS"},
    {Token_Type::BANG,            "Bang"},
    {Token_Type::BANG_EQUAL,      "BANG_EQUAL"},
    {Token_Type::EQUAL,           "EQUAL"},
    {Token_Type::EQUAL_EQUAL,     "EQUAL_EQUAL"},
    {Token_Type::GREATER,         "GREATER"},
    {Token_Type::GREATER_EQUAL,   "GREATER_EQUAL"},
    {Token_Type::LESS,            "LESS"},
    {Token_Type::LESS_EQUAL,      "LESS_EQUAL"},
    {Token_Type::AND,             "AND"},
    {Token_Type::AND_AND,         "AND_AND"},
    {Token_Type::OR,              "OR"},
    {Token_Type::OR_OR,           "OR_OR"},
    {Token_Type::STRING_LITERAL,  "STRING_LITERAL"},
    {Token_Type::INTEGER_LITERAL, "INTEGER_LITERAL"},
    {Token_Type::FLOAT_LITERAL,   "FLOAT_LITERAL"},
    {Token_Type::BOOLEAN_LITERAL, "BOOLEAN_LITERAL"},
    {Token_Type::NULL_LITERAL,    "NULL_LITERAL"},
    {Token_Type::BREAK,           "BREAK"},
    {Token_Type::ELSE,            "ELSE"},
    {Token_Type::FOR,             "FOR"},
    {Token_Type::IF,              "IF"},
    {Token_Type::LET,             "LET"},
    {Token_Type::PRINT,           "PRINT"},
    {Token_Type::RETURN,          "RETURN"},
    {Token_Type::WHILE,           "WHILE"},
    {Token_Type::IDENTIFIER,      "IDENTIFIER"},
    {Token_Type::END_OF_FILE,     "END_OF_FILE"}
  };

  Token::Token (const Token_Type type, const std::string lexeme, const std::optional<Literal> literal, const size_t line) :
    type {type}, lexeme {lexeme}, literal {literal}, line {line} {}

  Token::Token (const Token_Type type, const std::string lexeme, const size_t line) :
    type {type}, lexeme {lexeme}, line {line} {}

  std::string to_string (const Literal &literal) {
    switch (literal.index()) {
    case 0:
      return std::get<0>(literal);
    case 1:
      return std::to_string(std::get<1>(literal));
    case 2:
      return std::to_string(std::get<2>(literal));
    case 3:
      return std::to_string(std::get<3>(literal));
    }

    static_assert(std::variant_size_v<Literal> == 4, "You messed something up with the literal to string function, and got a value index other then the ones specified.\n");
    return "";
  }

  std::string to_string (const Token &token) {
    return "{" + std::to_string(token.line) + ", " + token_to_string.at(token.type) + ", \"" + token.lexeme + "\"" +
      (token.literal ?
       (", " + to_string(token.literal.value())) : "")
      + "}";
  }
} // namespace eweda::token
