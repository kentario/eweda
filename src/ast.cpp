#include "ast.hpp"

#include <variant>

#include "token.hpp"

namespace eweda::ast {

  struct To_String_Visitor {
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
  } to_string_visitor;
  
  std::string to_string (const Node_Ptr &node_ptr) {
    return std::visit(to_string_visitor, *node_ptr);
  }
  
} // namespace eweda::ast
