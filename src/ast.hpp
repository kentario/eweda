#pragma once

#include <variant>
#include <memory>

#include "token.hpp"

namespace eweda::ast {

  struct Literal;
  struct Binary;
  struct Unary;
  struct Group;
  
  using Node = std::variant<Literal, Binary, Unary, Group>;
  using Node_Ptr = std::unique_ptr<Node>;

  struct Literal {
    const token::Literal value;

    Literal (const token::Literal &value);
  };

  struct Binary {
    const Node_Ptr left;
    const Node_Ptr right;
    const token::Token token;

    Binary (Node_Ptr &&left, Node_Ptr &&right, const token::Token &token);
  };
  
  struct Unary {
    const Node_Ptr expr;
    const token::Token token;

    Unary (Node_Ptr &&expr, const token::Token &token);
  };
  
  struct Group {
    const Node_Ptr expr;

    Group (Node_Ptr &&expr);
  };

  // In reverse Polish notation.
  std::string to_string (const Node_Ptr &node);
  
} // namespace eweda::ast
