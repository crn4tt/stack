#pragma once
#include <string>
#include "Table.h"
#include "Stack.h"
#include <vector>


class ExpressionChecker{
private:
    Table<char, double> _vartable;
    Table<int, int> _bracketTable;
    
    bool IsUniqueVar(char s){
        for(size_t i = 0; i < _vartable.GetCount(); i++){
            if (s == _vartable.GetValcol1(i)) return 0;
        }
        return 1;
    }

    void FillVal(std::string str){
        for (size_t i = 0; i < str.size(); i++){
            if(((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') ) && IsUniqueVar(str[i] )){
                double in = 0;
                std::cout << "val " << str[i] << " - ";
                std::cin >> in;
                _vartable.AddRow(str[i],in);
                std::cout << std::endl;
            }
            else continue; 
        }
        std::cout<< _vartable << std::endl;
    }
    void FillBrackets(std::string str){
        Stack<int> stack(15);
        for (size_t i = 0; i < str.size();i++){
            if (str[i] == '('){
                stack.Push(i);
            }
            else if(str[i] == ')'){
                if(stack.isEmpty()) _bracketTable.AddRow(std::nullopt, i);
                else _bracketTable.AddRow(stack.Pop(),i);
            }
        }
        while(!stack.isEmpty()) _bracketTable.AddRow(stack.Pop(),std::nullopt);
    }
public: 
    ExpressionChecker(std::string str): _vartable("var","val",10), _bracketTable("(",")") {
        size_t flag = 0;
        for (int i = 0; i < str.size(); i++) { 
            if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z'){ 
                flag = 1;
                break;
            }
        }
        if (flag) FillVal(str);
        FillBrackets(str);
  
}

    bool CheckBrackets()const{
        for (size_t i = 0; i < _bracketTable.GetCount(); i++){
            if(_bracketTable.GetValcol1(i) == std::nullopt || _bracketTable.GetValcol2(i) == std::nullopt){
                std::cout << _bracketTable << std::endl;
                return 0;
            } 
        }
        return 1;
    }

    size_t GetSizeBracket()const{
        return _bracketTable.GetCount();
    }

    std::optional<int> GetValueBracket1(size_t i){
        return _bracketTable.GetValcol1(i);
    }

    std::optional<int> GetValueBracket2(size_t i){
        return _bracketTable.GetValcol2(i);
    }

    int GetVal12(int i){
        return _bracketTable.GetValKey(i);
    }

    int GetVal21(int i){
        return _bracketTable.GetValKey21(i);
    }

    double GetValueVartable(char s)const{
        return _vartable.GetValKey(s);
    }

    void CheckVar()const{
        std::cout << _vartable << std::endl;
    }
};
