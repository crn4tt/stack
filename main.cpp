#include "Formula.h"

int main(){
    Formula f("(3 + 3)**");
    std::string postfix = f.GetPostfix();
    std::cout<<postfix<<"\n";
    std::cout<<f.GetResult()<<"\n";
    return 0;
}