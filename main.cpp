#include <iostream>
#include <string>
#include "Stack.h"
#include "Table.h"
#include "Formula.h"


int main() {
    try {
        Formula formula("(a + 5) * (b - 2)");
        formula.Parse();
        std::cout << "Postfix expression: " << formula.GetRawExpr() << std::endl;

        std::cout << "Result: " << formula.Calculate() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
