#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "converter.h"

// Функция для преобразования строки в верхний регистр
std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Функция проверки, что строка состоит только из букв (код валюты)
bool isValidCurrencyCode(const std::string& str) {
    if (str.empty() || str.length() > 3) return false;
    for (char c : str) {
        if (!std::isalpha(c)) return false;  // только буквы!
    }
    return true;
}

// Функция проверки, что строка - это число
bool isValidAmount(const std::string& str) {
    if (str.empty()) return false;
    int dots = 0;
    for (char c : str) {
        if (c == '.') {
            dots++;
            if (dots > 1) return false;
        } else if (!std::isdigit(c)) {
            return false;  // только цифры и одна точка!
        }
    }
    return true;
}

int main() {
    Converter converter;
    std::string from, to, amountStr;
    double amount;
    
    std::cout << "=== 💱 Simple Currency Converter ===\n";
    std::cout << "Поддерживаемые валюты: USD, EUR, RUB, GBP, JPY, CNY и другие\n";
    std::cout << "====================================\n\n";
    
    while (true) {
        // Ввод исходной валюты с проверкой
        while (true) {
            std::cout << "From (USD/EUR/RUB etc): ";
            std::cin >> from;
            from = toUpper(from);
            
            if (isValidCurrencyCode(from)) {
                break;
            } else {
                std::cout << "❌ Ошибка: '" << from << "' - это не код валюты!\n";
                std::cout << "   Введите 3 буквы, например: USD, EUR, RUB\n\n";
            }
        }
        
        // Ввод целевой валюты с проверкой
        while (true) {
            std::cout << "To (USD/EUR/RUB etc): ";
            std::cin >> to;
            to = toUpper(to);
            
            if (isValidCurrencyCode(to)) {
                break;
            } else {
                std::cout << "❌ Ошибка: '" << to << "' - это не код валюты!\n";
                std::cout << "   Введите 3 буквы, например: USD, EUR, RUB\n\n";
            }
        }
        
        // Ввод суммы с проверкой
        while (true) {
            std::cout << "Amount: ";
            std::cin >> amountStr;
            
            if (isValidAmount(amountStr)) {
                amount = std::stod(amountStr);
                if (amount > 0) {
                    break;
                } else {
                    std::cout << "❌ Ошибка: сумма должна быть больше 0!\n\n";
                }
            } else {
                std::cout << "❌ Ошибка: '" << amountStr << "' - это не число!\n";
                std::cout << "   Введите число, например: 100, 50.5, 1000\n\n";
            }
        }
        
        // Конвертация
        std::cout << "\n🔄 Конвертирую...\n";
        double result = converter.convert(amount, from, to);
        
        if (result > 0) {
            std::cout << "✅ " << amount << " " << from << " = " << result << " " << to << "\n\n";
        } else {
            std::cout << "❌ Не удалось конвертировать. Проверьте:\n";
            std::cout << "   - Интернет подключен?\n";
            std::cout << "   - Валюты существуют? (USD, EUR, RUB...)\n\n";
        }
        
        // Продолжить?
        std::cout << "Конвертировать ещё? (y/n): ";
        char again;
        std::cin >> again;
        if (again != 'y' && again != 'Y') {
            std::cout << "\n👋 До свидания!\n";
            break;
        }
        std::cout << "\n";
    }
    
    system("pause");
    return 0;
}
