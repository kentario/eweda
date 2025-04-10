#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "error.hpp"
#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"

using namespace eweda;

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [script]\n";
    return EXIT_FAILURE;
  }

  const std::string filename {argv[1]};
  std::ifstream file {filename};

  if (!file.is_open()) {
    std::cerr << "error: could not open file '" << filename << "'\n";
  }

  std::stringstream buff;
  buff << file.rdbuf();
  const std::string src {buff.str()};

  lexer::Lexer lexer {src};
  std::vector tokens {lexer.tokenize()};
  
  for (const auto &t : tokens) {
    std::cout << token::to_string(t) << '\n';
  } std::cout << '\n';

  if (error::had_error) {
    return EXIT_FAILURE;
  }

  parser::Parser parser {tokens};
  ast::Node_Ptr expr {parser.parse()};
  std::cout << ast::to_string(expr) << '\n';
  
  if (error::had_error) {
    return EXIT_FAILURE;
  }
  
  return 0;
}
