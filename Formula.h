#pragma once
#include <iostream>
#include "Stack.h"


class Formula{
private:
    std::string _expression;
    std::string _postfix;
    Stack <std::string> _calcStack;

public:
    Formula(std::string exp);
    bool CheckBrackets();
    bool CheckFormula();
    void EnterVariableValues();//вводим значения переменных если они есть,если есть переменная, но нет значения-ошибка. можно перевести в приват
    std::string BuildPostfix();
    double Calculate();



};
