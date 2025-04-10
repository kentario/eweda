#include "ast.hpp"

#include <variant>

#include "token.hpp"

namespace eweda::ast {

  struct Visitor {
    std::string operator() (const Literal &literal) {return token::to_string(literal.value);}
    std::string operator() (const Binary &expr) {
      return "(" + to_string(expr.left) + " " + to_string(expr.right) + " " + expr.token.lexeme + ")";
    }
    std::string operator() (const Unary &expr) {
      return "(" + to_string(expr.expr) + " " + expr.token.lexeme + ")";
    }
    std::string operator() (const Group &expr) {
      return "(" + to_string(expr.expr) + " group)";
    }
  } visitor;
  
  std::string to_string (const Node_Ptr &node_ptr) {
    return std::visit(visitor, *node_ptr);
  }
  
} // namespace eweda::ast
