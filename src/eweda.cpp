#include <iostream>
#include <vector>

#include "token.hpp"

using namespace eweda;

int main (int argc, char *argv[]) {
  std::vector tokens {
    token::Token{token::Token_Type::COMMA, "(", 3},
    token::Token{token::Token_Type::STRING_LITERAL, "hello world", std::optional<token::Literal>("hello world"), 5},
  };

  for (const auto &t : tokens) {
    std::cout << token::to_string(t) << '\n';
  }
  
  return 0;
}
