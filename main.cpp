#include <iostream>
#include "Formula.h"

int main(){
    std::string s="(-11+bb*c/d-123)*(sin(1+3)+bb*sin(x+x))";
    Formula f(s);
    std::cout<<f.GetPostfix()<<"\n";
    std::cout<<f.Calculate();
    //ответ верный
    return 0;
}