#pragma once
#include <iostream>
#include "Stack.h"
#include <vector>
#include <map>

class Formula{
private:
    std::string _expression;
    std::string _postfix;
    std::vector<std::string> _analysis;
    double _result;
public:
    Formula(std::string exp){
        _expression = exp;
        Analysis();
        for (int i = 0; i < _analysis.size(); i++){
            std::cout<<_analysis[i]<<" ";
        }
        std::cout<<"\n";
        if (!CheckBrackets() || !CheckFormula()){
            throw "incorrect input";
        }
        EnterVariableValues();
        _analysis = BuildPostfix();
        for (int i = 0; i < _analysis.size(); i++){
            std::cout<<_analysis[i]<<" ";
        }
        std::cout<<"\n";
        _result = Calculate();
    }

    std::string GetPostfix(){
        return _postfix;
    }
    double GetResult(){
        return _result;
    }

private:
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

    std::vector<std::string> BuildPostfix(){
        std::vector<std::string> postfix;
        std::map<std::string, int> priorities = {{"(", 0}, {")", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};
        Stack<std::string> stack;
        for (int i = 0; i < _analysis.size(); i++){
            std::string lexem = _analysis[i];
            if (lexem == "+" || lexem == "-" || lexem == "*" || lexem == "/"){
                if (stack.IsEmpty()){
                    stack.Push(lexem);
                }
                else{
                    while (priorities[stack.Check()] >= priorities[lexem] && !stack.IsEmpty()){
                        postfix.push_back(stack.Pop());
                    }
                    stack.Push(lexem);
                }
            }
            else if (lexem == ")"){
                while (stack.Check() != "("){
                    postfix.push_back(stack.Pop());
                }
                lexem = stack.Pop();
            }
            else if (lexem == "("){
                stack.Push(lexem);
            }
            else{
                postfix.push_back(lexem);
            }

        }
        while (!stack.IsEmpty()){
            std::string lexem = stack.Pop();
            postfix.push_back(lexem);
        }
        return postfix;
    }

    double Calculate(){
        double number;
        double number1;
        Stack<double> stack;
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
            stack.Push(StrToDouble(_analysis[i]));
        }
        return stack.Pop();
    }

    double StrToDouble(std::string s){
        if (s.find(".") == std::string::npos){
            int res = 0;
            int count = 1;
            for (int i = s.length() - 1; i >= 0; i--){
                if (i == 0){
                    if (s[i] == '-'){
                        res *= -1;
                        return res;
                    }
                }
                res += ((s[i] - 48) * count);
                count *= 10;
            }
            return res;
        }
        else {
            double res;
            std::cout<<"Enter number "<<s<<" : ";
            std::cin>>res;
            return res;
        }
    }

    bool CheckBrackets(){
        int status = 0;
        int LeftBrackets = 0;
        int RightBracket = 0;
        for (int i = 0; i < _analysis.size(); i++){
            if (_analysis[i] == "("){
                status++;
                LeftBrackets++;
            }
            else if (_analysis[i] == ")"){
                status--;
                if (status < 0){
                    status = -1000;
                }
                RightBracket++;
            }
        }
        if (status == 0){
            return true;
        }
        int size = LeftBrackets + RightBracket;
        int matrix[size][2];
        for (int i = 0; i < size; i++){
            for (int j = 0; j < 2; j++){
                matrix[i][j] = -1;
            }
        }
        int row = 0;
        for (int i = 0; i < _analysis.size(); i++){
            if (_analysis[i] == "("){
                matrix[row][0] = i + 1;
                row++;
            }
            else if (_analysis[i] == ")"){
                int CopyRow = row - 1;
                while (CopyRow != -1){
                    if (matrix[CopyRow][1] == -1){
                        matrix[CopyRow][1] = i + 1;
                        break;
                    }
                    CopyRow--;
                }
                if (CopyRow == -1){
                    matrix[row][1] = i + 1;
                    row++;
                }
            }
        }
        std::cout<<"\ntable Brackers\n";
        row = 0;
        while ((matrix[row][0] != -1 || matrix[row][1] != -1) && row != size){
            std::cout<<"  "<<matrix[row][0]<<"     "<<matrix[row][1]<<"\n";
            row++;
        }
        return false;
    }

    bool CheckFormula(){
        bool status = 0;
        for (int i = 0; i < _analysis.size(); i++){
            if (_analysis[i] == "+" || _analysis[i] == "-" || _analysis[i] == "*" || _analysis[i] == "/" || _analysis[i] == "(" || _analysis[i] == ")"){
                if (status == 0) status = 1;
                else{
                    std::cerr<<"incorrect input\n";
                    break;
                }
            }
            else status = 0;
        }
        return true;
    }
    
    void EnterVariableValues(){
        for (int i = 0; i < _analysis.size(); i++){
            if ((_analysis[i][0] >= 65 && _analysis[i][0] >= 90) || (_analysis[i][0] >= 97 && _analysis[i][0] >= 122)){
                std::cout<<"Enter Value "<<_analysis[i]<<": ";
                std::cin>>_analysis[i];
                std::cout<<"\n";
            }
        }
    }
};


//почему нельзя при инициализации присвоить и почему не могу сразу а нужно создавать lexem