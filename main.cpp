#include <iostream>
#include "Formula.h"

int main(){
    std::string s="(a + b * (c + 4))";
    Formula f(s);
    std::cout<<f.GetPostfix()<<"\n";
    std::cout<<f.Calculate();
    return 0;
}