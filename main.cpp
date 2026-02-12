#include <iostream>
#include <iomanip>
#include "converter.h"

int main() {
    Converter conv;
    
    std::cout << "=== Currency Converter ===\n\n";
    
    std::string from, to;
    double amount;
    
    std::cout << "From (USD/EUR/RUB etc): ";
    std::cin >> from;
    
    std::cout << "To (USD/EUR/RUB etc): ";
    std::cin >> to;
    
    std::cout << "Amount: ";
    std::cin >> amount;
    
    double result = conv.convert(amount, from, to);
    
    if (result >= 0) {
        std::cout << "\nResult: " 
                  << std::fixed << std::setprecision(2)
                  << amount << " " << from 
                  << " = " << result << " " << to << std::endl;
    } else {
        std::cout << "Conversion failed!" << std::endl;
    }
    system("pause");
    return 0;
}
