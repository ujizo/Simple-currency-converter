#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "converter.h"

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool isValidCurrencyCode(const std::string& str) {
    if (str.empty() || str.length() > 3) return false;
    for (char c : str) {
        if (!std::isalpha(c)) return false;
    }
    return true;
}

bool isValidAmount(const std::string& str) {
    if (str.empty()) return false;
    int dots = 0;
    for (char c : str) {
        if (c == '.') {
            dots++;
            if (dots > 1) return false;
        } else if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    Converter converter;
    std::string from, to, amountStr;
    double amount;

    std::cout << "=== SIMPLE CURRENCY CONVERTER ===\n";
    std::cout << "Supported currencies: USD, EUR, RUB, GBP, JPY, CNY and others\n";
    std::cout << "==================================\n\n";

    while (true) {
        // Input source currency
        while (true) {
            std::cout << "From (USD/EUR/RUB etc): ";
            std::cin >> from;
            from = toUpper(from);

            if (isValidCurrencyCode(from)) {
                break;
            } else {
                std::cout << "ERROR: '" << from << "' is not a valid currency code!\n";
                std::cout << "Enter 3 letters, e.g.: USD, EUR, RUB\n\n";
            }
        }

        // Input target currency
        while (true) {
            std::cout << "To (USD/EUR/RUB etc): ";
            std::cin >> to;
            to = toUpper(to);

            if (isValidCurrencyCode(to)) {
                break;
            } else {
                std::cout << "ERROR: '" << to << "' is not a valid currency code!\n";
                std::cout << "Enter 3 letters, e.g.: USD, EUR, RUB\n\n";
            }
        }

        // Input amount
        while (true) {
            std::cout << "Amount: ";
            std::cin >> amountStr;

            if (isValidAmount(amountStr)) {
                amount = std::stod(amountStr);
                if (amount > 0) {
                    break;
                } else {
                    std::cout << "ERROR: Amount must be greater than 0!\n\n";
                }
            } else {
                std::cout << "ERROR: '" << amountStr << "' is not a valid number!\n";
                std::cout << "Enter a number, e.g.: 100, 50.5, 1000\n\n";
            }
        }

        // Convert
        std::cout << "\nConverting...\n";
        double result = converter.convert(amount, from, to);

        if (result > 0) {
            std::cout << "RESULT: " << amount << " " << from << " = " << result << " " << to << "\n\n";
        } else {
            std::cout << "Conversion failed. Please check:\n";
            std::cout << "  - Internet connection\n";
            std::cout << "  - Currency codes (USD, EUR, RUB...)\n\n";
        }

        // Continue?
        std::cout << "Convert another? (y/n): ";
        char again;
        std::cin >> again;
        if (again != 'y' && again != 'Y') {
            std::cout << "\nGoodbye!\n";
            break;
        }
        std::cout << "\n";
    }

    system("pause");
    return 0;
}
