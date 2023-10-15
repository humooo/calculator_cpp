#pragma once

#include "ExprInPolishNotation.hpp"

template <typename T>
class Calculator {
  public:
  static T CalculateExpr(const std::string& expr) {
    std::vector<std::string> tokens = ExprInPolishNotation(expr).GetTokens();
    std::stack<T> values;
    for (const std::string& str : tokens) {
      if (str == "+" or str == "-" or str == "*" or str == "/") {
        T operand2 = values.top();
        values.pop();
        T operand1 = values.top();
        values.pop();
        values.push(Proc(operand1, operand2, str[0]));
      } else {
        values.push(static_cast<T>(std::atof(str.data())));
      }
    }
    if (values.size() != 1) {
      throw std::exception();
    }
    return values.top();
  }
};