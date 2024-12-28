#pragma once
#include <string>
#include <algorithm> 
#include <iostream>
#include <cstdlib>
#include "Stack.h"
#include "ExpressionChecker.h"
#include <vector>

class Formula{
private:
    std::string _expr;
    std::string _postfix;
    Table<char,int> _priority;
    ExpressionChecker _ec;
  
    bool IsDigit(char s)const{
        std::string str = "0123456789"; 
        for (size_t i = 0; i < str.size(); i++){
            if (s == str[i]) return 1;
        }
        return 0;
    }
    bool IsOperation(char s)const{
        for(size_t i = 0; i < 6; i++){
            if (s == _priority.GetValcol1(i)) return 1;
        }
        return 0;
    }
    bool IsWord(char s)const{return (s >= 'A' && s <= 'Z' || s >= 'a' && s <= 'z');}
public:
    Formula(std::string str) :  _priority("sym","pri"), _postfix(""), _ec(str){//_stack(15),
        _expr = str;
        _priority.AddRow('(',0);
        _priority.AddRow(')',1);
        _priority.AddRow('+',2);
        _priority.AddRow('-',2);
        _priority.AddRow('*',3);
        _priority.AddRow('/',3);
    }

    void Parse(){
        Stack<char> _stack(15);

        // Проверка скобок
        if (!_ec.CheckBrackets()) {
            std::vector<std::optional<int>> errorPositions;

            // Собираем позиции ошибок
            for (size_t i = 0; i < _ec.GetSizeBracket(); i++) {
                if (_ec.GetValueBracket1(i) == std::nullopt) {
                    errorPositions.push_back(_ec.GetValueBracket2(i));
                }
                if (_ec.GetValueBracket2(i) == std::nullopt) {
                    errorPositions.push_back(_ec.GetValueBracket1(i));
                }
            }

            // Визуализация ошибки
            std::cout << _expr << std::endl;
            std::string marker(_expr.size(), ' ');

            for (const auto& pos : errorPositions) {
                if (pos.has_value()) {
                    marker[pos.value()] = '^';
                }
            }

            std::cout << marker << std::endl;

            // Выбрасываем исключение
            throw std::runtime_error("Brackets error: unmatched or misplaced brackets.");
        }

        // Продолжение построения постфиксного выражения...
        for (size_t i = 0; i < _expr.size(); i++) {
            if (IsDigit(_expr[i])) {
                _postfix += _expr[i];
                if (!IsDigit(_expr[i + 1]) && _expr[i + 1] != '\n') _postfix += ' ';
            } else if (IsWord(_expr[i])) {
                _postfix += _expr[i];
                if (_expr[i + 1] != '\n') _postfix += " ";
            } else if (_expr[i] == ' ') {
                continue;
            } else if (IsOperation(_expr[i])) {
                int priority = _priority.GetValKey(_expr[i]);
                if (priority == 0 || _stack.isEmpty()) {
                    _stack.Push(_expr[i]);
                } else if (priority > _priority.GetValKey(_stack.Top())) {
                    _stack.Push(_expr[i]);
                } else {
                    while (_stack.GetIndexTop() >= 0 && priority <= _priority.GetValKey(_stack.Top())) {
                        _postfix += _stack.Pop();
                        _postfix += ' ';
                    }
                    if (_expr[i] != ')') _stack.Push(_expr[i]);
                }
            }
        }

        while (!_stack.isEmpty()) {
            if (_stack.Top() == '(') _stack.Pop();
            else {
                _postfix += _stack.Pop();
                _postfix += ' ';
            }
        }
    }


    double Calculate() const {
    if (_postfix.empty()) {
        throw std::runtime_error("Postfix is empty. Build postfix expression before calculating.");
    }

    double ans = 0;
    Stack<double> stack(15);
    std::string num = "";

    for (size_t i = 0; i < _postfix.size(); i++) {
        if (_postfix[i] == ' ') continue;


        if (IsWord(_postfix[i])) {
            double varValue = _ec.GetValueVartable(_postfix[i]);
            stack.Push(varValue);
        }

        else if (IsDigit(_postfix[i])) {
            num += _postfix[i];

            if (_postfix[i + 1] == ' ') {
                stack.Push(std::stod(num));
                num.clear();
            }
        }

        else if (IsOperation(_postfix[i])) {

            if (stack.GetIndexTop() < 1) {
                throw std::runtime_error("Invalid postfix expression: not enough operands for the operation.");
            }

            double op2 = stack.Pop();
            double op1 = stack.Pop();

            switch (_postfix[i]) {
                case '+':
                    stack.Push(op1 + op2);
                    break;
                case '-':
                    stack.Push(op1 - op2);
                    break;
                case '*':
                    stack.Push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        throw std::runtime_error("Division by zero.");
                    }
                    stack.Push(op1 / op2);
                    break;
                default:
                    throw std::runtime_error("Unknown operation in postfix expression.");
            }
        } else {
            throw std::runtime_error("Invalid character in postfix expression.");
        }
    }

    if (stack.GetIndexTop() != 0) {
        throw std::runtime_error("Invalid postfix expression: too many operands.");
    }

    ans = stack.Pop();
    return ans;
}


    std::string GetRawExpr()const{ return _expr; }
    std::string GetPostfixForm() const { return _postfix; }

};
