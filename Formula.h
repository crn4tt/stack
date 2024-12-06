#pragma once
#include <iostream>
#include "Stack.h"
#include "Table.h"
#include <vector>
#include <optional>
#include "CorrectChecker.h"


class Formula{
private:
    std::string _expression;
    std::string _postfix;
    Stack <std::string> _calcStack;
    std::vector<std::string> _analysis;
    Table <std::string, int> _prior;
    CorrectChecker _checker;
public:
    Formula(const std::string& exp) : _prior("sym", "prior", 10), _expression(exp){
        std::optional<std::string> elem = std::optional<std::string>("(");
        _prior.AppendRow(elem, 0);
        elem = std::optional<std::string>(")");
        _prior.AppendRow(elem, 0);
        elem = std::optional<std::string>("+");
        _prior.AppendRow(elem, 1);
        elem = std::optional<std::string>("-");
        _prior.AppendRow(elem, 1);
        elem = std::optional<std::string>("*");
        _prior.AppendRow(elem, 2);
        elem = std::optional<std::string>("/");
        _prior.AppendRow(elem, 2);
        if (!_checker.CheckBrackets(_expression)){
            throw 1;
        }
        Analysis();
        if (!_checker.CheckFormula(_analysis) || !_checker.CheckVariable(_analysis)){
            throw 1;
        }
        _analysis = BuildPostfix();
        for (int i = 0; i < _analysis.size(); i++){
            _postfix += _analysis[i];
        }
        
    }

    std::vector<std::string> BuildPostfix(){
        std::vector<std::string> postfix;
        for (int i = 0; i < _analysis.size(); i++){
            std::string lexem = _analysis[i];
            if (lexem == "+" || lexem == "-" || lexem == "*" || lexem == "/"){
                if (_calcStack.IsEmpty()){
                    _calcStack.Push(lexem);
                }
                else{
                    while (_prior[_calcStack.Check()] >= _prior[lexem] && !_calcStack.IsEmpty()){
                        postfix.push_back(_calcStack.Pop());
                    }
                    _calcStack.Push(lexem);
                }
            }
            else if (lexem == ")"){
                while (_calcStack.Check() != "("){
                    postfix.push_back(_calcStack.Pop());
                }
                lexem = _calcStack.Pop();
            }
            else if (lexem == "("){
                _calcStack.Push(lexem);
            }
            else{
                postfix.push_back(lexem);
            }

        }
        while (!_calcStack.IsEmpty()){
            std::string lexem = _calcStack.Pop();
            postfix.push_back(lexem);
        }
        return postfix;
    }
    double Calculate(){
        double number;
        double number1;
        Stack<double> stack;
        Table<std::string, double> _varTable = _checker.GetVarTable();
        for (int i = 0; i < _analysis.size(); i++){
            if (_analysis[i] == "+"){
                stack.Push(stack.Pop() + stack.Pop()); 
                continue;
            }
            else if (_analysis[i] == "*"){
                stack.Push(stack.Pop() * stack.Pop()); 
                continue;
            } 
            else if (_analysis[i] == "-"){
                number = stack.Pop();
                stack.Push(stack.Pop() - number); 
                continue;
            } 
            else if (_analysis[i] == "/"){
                number = stack.Pop();
                stack.Push(stack.Pop() / number); 
                continue;
            }
            stack.Push(_varTable[_analysis[i]]);
        }
        return stack.Pop();
    }
    void Analysis(){
        std::string lexem;
        bool status = 0;
        for (int i = 0; i < _expression.length(); i++){
            if (_expression[i] == '+' || _expression[i] == '*' || _expression[i] == '/' || _expression[i] == '-'){
                if (i == 0 && _expression[i] == '-'){
                    lexem = _expression[i];
                    continue;
                }
                if (lexem.empty()){
                    lexem = _expression[i];
                    _analysis.push_back(lexem);
                    lexem.clear();
                }
                else {
                    _analysis.push_back(lexem);
                    lexem.clear();
                    lexem = _expression[i];
                    _analysis.push_back(lexem);
                    lexem.clear();
                }
            }
            else if (_expression[i] == ')' || _expression[i] == '('){
                if (i != _expression.length() - 1 && _expression[i] != ')'){
                    if (_expression[i + 1] == '-'){
                        lexem.push_back(_expression[i + 1]);
                        i++;
                        status = true;
                        continue;
                    }
                }
                else if (_expression[i] == ')' && status == true){
                    status = false;
                    _analysis.push_back(lexem);
                    lexem.clear();
                    continue;
                }        
                if (lexem.empty()){
                    lexem = _expression[i];
                    _analysis.push_back(lexem);
                    lexem.clear();
                }
                else {
                    _analysis.push_back(lexem);
                    lexem.clear();
                    lexem = _expression[i];
                    _analysis.push_back(lexem);
                    lexem.clear();
                }
            }
            else if (_expression[i] == ' '){
                continue;
            }
            else {
                lexem.push_back(_expression[i]);
            }
        }
        _analysis.push_back(lexem);
    }



};