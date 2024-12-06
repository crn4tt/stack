#include <iostream>
#include "Formula.h"

// std::optional<std::string> create(bool b){
//     if (b)
//         return "Godzilla";
//     return std::nullopt;
//     }

int main(){
    std::string s="(a+b)+c+b-d";
    Formula f(s);
    std::cout<<f.Calculate();
    return 0;
}