#pragma once
#include "Stack.h"
#include "Table.h"
#include <vector>
#include <iostream>

class CorrectChecker{
private:
    Stack<int> _brackets;//индексы открывающихся
    Table<int, int> _bracketsTable;
    Table<std::string, double> _varTable;
    bool _state=false;


public:
    CorrectChecker() : _bracketsTable("(", ")"), _varTable("variable", "value"){
    }
    bool CheckBrackets(const std::string& s);
    bool CheckVariable(const std::vector<std::string>& _analysis);
    bool CheckFormula(const std::vector<std::string>& _analysis);
    bool GetState(){
        return _state;
    }
    const Table<std::string, double>& GetVarTable(){
        return _varTable;
    }





};