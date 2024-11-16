#include "Formula.h"

int main(){
    Formula f("(1 + a / 3 + (-1) * 4) / (-5)");
    std::string postfix = f.GetPostfix();
    std::cout<<postfix<<"\n";
    std::cout<<f.GetResult()<<"\n";
    return 0;
}