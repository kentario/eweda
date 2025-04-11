#include "lexer.hpp"

#include <string>
#include <string_view>
#include <unordered_map>
#include <cctype>

#include "token.hpp"
#include "error.hpp"

namespace eweda::lexer {

  using token::Token_Type;

  const std::unordered_map<std::string_view, Token_Type> reserved {
    {"true",  Token_Type::BOOLEAN_LITERAL},
    {"false", Token_Type::BOOLEAN_LITERAL},
    
    {"break",  Token_Type::BREAK},
    {"else",   Token_Type::ELSE},
    {"for",    Token_Type::FOR},
    {"if",     Token_Type::IF},
    {"let",    Token_Type::LET},
    {"print",  Token_Type::PRINT},
    {"return", Token_Type::RETURN},
    {"while",  Token_Type::WHILE},
  };

  Lexer::Lexer (const std::string &src) :
    src {src} {}

  std::vector<token::Token> Lexer::tokenize () {
    while (current < src.size()) {
      start = current;

      scan_token();
    }

    tokens.push_back(token::Token {Token_Type::END_OF_FILE, "", line});
    
    return tokens;
  }

  void Lexer::scan_token () {
    char c {consume()};
    
    switch (c) {
      // Whitespace
    case '\n':
      line++;
    case ' ':
    case '\f':
    case '\r':
    case '\t':
    case '\v':
      break;

      // Single character
    case '(': add_token(Token_Type::LEFT_PAREN); break;
    case ')': add_token(Token_Type::RIGHT_PAREN); break;
    case '[': add_token(Token_Type::LEFT_BRACKET); break;
    case ']': add_token(Token_Type::RIGHT_BRACKET); break;
    case '{': add_token(Token_Type::LEFT_BRACE); break;
    case '}': add_token(Token_Type::RIGHT_BRACE); break;
    case ',': add_token(Token_Type::COMMA); break;
    case '.': add_token(Token_Type::DOT); break;
    case '*': add_token(Token_Type::STAR); break;
    case ';': add_token(Token_Type::SEMICOLON); break;
      // 1 or 2 character
    case '+': add_token(consume_if('+') ? Token_Type::PLUS_PLUS : Token_Type::PLUS); break;
    case '-': add_token(consume_if('+') ? Token_Type::MINUS_MINUS : Token_Type::MINUS); break;
    case '!': add_token(consume_if('=') ? Token_Type::BANG_EQUAL : Token_Type::BANG); break;
    case '=': add_token(consume_if('=') ? Token_Type::EQUAL_EQUAL : Token_Type::EQUAL); break;
    case '>': add_token(consume_if('=') ? Token_Type::GREATER_EQUAL : Token_Type::GREATER); break;
    case '<': add_token(consume_if('=') ? Token_Type::LESS_EQUAL : Token_Type::LESS); break;
    case '&': add_token(consume_if('&') ? Token_Type::AND_AND : Token_Type::AND); break;
    case '|': add_token(consume_if('|') ? Token_Type::OR_OR : Token_Type::OR); break;
      
    case '/':
      if (consume_if('/')) comment();
      else add_token(Token_Type::SLASH);
      break;
      
    case '"':
      string_literal();
      break;
      
    default:
      if (std::isalpha(c) || c == '_') {
	identifier();
      } else if (std::isdigit(c)) {
	number_literal();
      } else {
	std::cout << c;
	error::lexer_error(line, "unexpected character `" + std::string {c} + "`");
      }
    }
  }
  
  void Lexer::identifier () { // TODO: handle boolean literals.
    while (std::isalnum(peek()) || peek() == '_') {
      consume();
    }

    // Check if it is reserved.
    auto itr = reserved.find(src.substr(start, current - start));
    if (itr != reserved.end()) {
      // It is reserved.
      // Check if it is a boolean literal
      if (itr->second == Token_Type::BOOLEAN_LITERAL) {
	add_token(itr->second, src[start] == 't' ? true : false);
      } else {
	add_token(itr->second);
      }
    } else {
      // It is an identifier
      add_token(Token_Type::IDENTIFIER);
    }
  }

  void Lexer::string_literal () {
    while (peek() && peek() != '"') {
      if (consume() == '\n') line++;
    }

    // Since the `"` didn't get consumed, that means if it has reached the end, then the string was unterminated.
    if (!peek()) {
      error::lexer_error(line, "unterminated string");
    }

    consume(); // The closing `"`.

    add_token(Token_Type::STRING_LITERAL, src.substr(start + 1, current - start - 2));
  }
  
  void Lexer::number_literal () {
    while (std::isdigit(peek())) consume();

    // Floating point literal
    if (peek() == '.' && std::isdigit(peek(1))) {
      // Consume the `.` first, then the rest of the digits.
      do consume(); while (std::isdigit(peek()));

      add_token(Token_Type::FLOAT_LITERAL, std::stod(src.substr(start)));
    } else {
      // Integer literal.
      add_token(Token_Type::INTEGER_LITERAL, std::stoi(src.substr(start)));
    }
  }

  void Lexer::comment () {
    while (peek() && consume() != '\n');
    line++;
  }

  void Lexer::add_token (const Token_Type type) {
    tokens.push_back(token::Token {type, src.substr(start, current - start), line});
  }

  void Lexer::add_token (const Token_Type type, const token::Literal &literal) {
    tokens.push_back(token::Token {type, src.substr(start, current - start), literal, line});
  }

  char Lexer::consume () {
    return src[current++];
  }

  char Lexer::consume_if (const char expected) {
    return (current >= src.size() || peek() != expected) ? 0 : consume();
  }

  char Lexer::peek (const size_t offset) const {
    return (current + offset < src.size()) * src[current + offset];
  }
  
} // namespace eweda::lexer
