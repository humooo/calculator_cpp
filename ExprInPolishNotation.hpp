#pragma once

#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

std::map<std::string, int> priority = {{"(", 0}, {"+", 1}, {"-", 1}, {"*", 2},
                                       {"/", 2}, {"~", 3},  // unary minus
                                       {"^", 3}};           // unary plus

class ExprInPolishNotation {
  public:
  ExprInPolishNotation(const std::string& expr) {
    std::vector<std::string> res = ExprOnVector(expr);
    std::stack<std::string> operators;
    for (size_t iii = 0; iii < res.size(); ++iii) {
      if (res[iii] == "(") {
        operators.push(res[iii]);
      } else if (res[iii] == ")") {
        while (operators.top() != "(") {
          tokens_.push_back(operators.top());
          operators.pop();
        }
        operators.pop();
      } else if (res[iii] == "+" or res[iii] == "-" or res[iii] == "*" or
          res[iii] == "/") {
        while (!operators.empty() and
            priority[operators.top()] >= priority[res[iii]]) {
          tokens_.push_back(operators.top());
          operators.pop();
        }
        operators.push(res[iii]);
      } else {
        tokens_.push_back(res[iii]);
      }
    }
    while (!operators.empty()) {
      tokens_.push_back(operators.top());
      operators.pop();
    }
  }
  const std::vector<std::string>& GetTokens() { return tokens_; }

  private:
  static std::vector<std::string> ExprOnVector(const std::string& expr) {
    std::vector<std::string> res;
    size_t jjj = 0;
    std::string tmp(1, ' ');
    std::set<std::string> operators = {"+", "-", "*", "/", "("};
    for (size_t iii = 0; iii < expr.size(); ++iii) {
      if (expr[iii] != '.' and !(expr[iii] >= '0' and expr[iii] <= '9')) {
        if (expr[iii] == '-' or expr[iii] == '+') {
          if (!res.empty() and operators.find(res.back()) != operators.end()) {
            continue;
          }
        }
        tmp[0] = expr[iii];
        if (iii != jjj) {
          res.push_back(expr.substr(jjj, iii - jjj));
        }
        if (tmp != " ") {
          res.push_back(tmp);
        }
        jjj = iii + 1;
      }
    }
    if (expr.size() != jjj) {
      res.push_back(expr.substr(jjj, expr.size() - jjj));
    }
    return res;
  }
  std::vector<std::string> tokens_;
};

template <typename T, char Op = '+'>
class Operator {
  public:
  static T Proc(T operand1, T operand2) { return operand1 + operand2; }
};

template <typename T>
class Operator<T, '-'> {
  public:
  static T Proc(T operand1, T operand2) { return operand1 - operand2; }
};

template <typename T>
class Operator<T, '*'> {
  public:
  static T Proc(T operand1, T operand2) { return operand1 * operand2; }
};

template <typename T>
class Operator<T, '/'> {
  public:
  static T Proc(T operand1, T operand2) { return operand1 / operand2; }
};

template <typename T>
static T Proc(T operand1, T operand2, char opr) {
  T res = Operator<T>().Proc(operand1, operand2);
  if (opr == '-') {
    res = Operator<T, '-'>().Proc(operand1, operand2);
  } else if (opr == '*') {
    res = Operator<T, '*'>().Proc(operand1, operand2);
  } else if (opr == '/') {
    res = Operator<T, '/'>().Proc(operand1, operand2);
  }
  return res;
}