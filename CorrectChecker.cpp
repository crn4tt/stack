#include "CorrectChecker.h"
#include "Table.h"
#include <optional>


bool CorrectChecker::CheckBrackets (const std::string& s){
    Table<int, int> t1("(", ")");
    for (size_t i = 0; i < s.size(); i++){
        if(s[i] == '(')
            _brackets.Push(i);
        if (s[i] == ')') {
            try {
                t1.AppendRow(_brackets.Pop(), i);
            }
            catch(const char* error_message) {
                t1.AppendRow(std::nullopt, i);
                std::cout << "err brackets" << i << std::endl;
                std::cout << t1 << std::endl;
                return false;
            }
        }  
    }
    while(!_brackets.IsEmpty()) {
        t1.AppendRow(_brackets.Pop(), std::nullopt);
    }
    if (t1.GetCount()) {
        std::cout << t1 << std::endl;
    }
    return _brackets.IsEmpty();
}

bool CorrectChecker::CheckFormula(const std::vector<std::string>& _analysis) {
    bool status = 0;
    for (int i = 0; i < _analysis.size(); i++) {
        if (_analysis[i] == "+" || _analysis[i] == "-" || _analysis[i] == "*" || _analysis[i] == "/") {
            if (status == 0) 
                status = 1;
            else {
                std::cerr << "wrong inp";
                return false;
            }
        }
        else if (_analysis[i] == "(" || _analysis[i] == ")") {
            continue;
        }
        else status = 0;
    }
    return true;
}

bool CorrectChecker::CheckVariable(const std::vector<std::string>& _analysis) {
    double number;
        for (int i = 0; i < _analysis.size(); i++) {
            if ((_analysis[i][0] >= 65 && _analysis[i][0] >= 90) || (_analysis[i][0] >= 97 && _analysis[i][0] >= 122)) {
                if (_varTable.FindCol1(_analysis[i])) {
                    continue;
                }
                std::cout << _analysis[i];
                std::cin >> number;
                std::optional<std::string> elem1(_analysis[i]);
                _varTable.AddRow(elem1, number);
            }
        }
        return 1;
    }
