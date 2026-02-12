#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include "converter.h"

#pragma execution_character_set("utf-8")

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
        if (!std::isalpha(c)) return false;
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
            return false;
        }
    }
    return true;
}

int main() {
    // ВКЛЮЧАЕМ РУССКУЮ КОДИРОВКУ В КОНСОЛИ
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    Converter converter;
    std::string from, to, amountStr;
    double amount;
    
    std::cout << "=== 💱 ПРОСТОЙ КОНВЕРТЕР ВАЛЮТ ===\n";
    std::cout << "Поддерживаемые валюты: USD, EUR, RUB, GBP, JPY, CNY и другие\n";
    std::cout << "====================================\n\n";
    
    while (true) {
        // Ввод исходной валюты с проверкой
        while (true) {
            std::cout << "Из (USD/EUR/RUB и т.д.): ";
            std::cin >> from;
            from = toUpper(from);
            
            if (isValidCurrencyCode(from)) {
                break;
            } else {
                std::cout << "❌ ОШИБКА: '" << from << "' - это не код валюты!\n";
                std::cout << "   Введите 3 буквы, например: USD, EUR, RUB\n\n";
            }
        }
        
        // Ввод целевой валюты с проверкой
        while (true) {
            std::cout << "В (USD/EUR/RUB и т.д.): ";
            std::cin >> to;
            to = toUpper(to);
            
            if (isValidCurrencyCode(to)) {
                break;
            } else {
                std::cout << "❌ ОШИБКА: '" << to << "' - это не код валюты!\n";
                std::cout << "   Введите 3 буквы, например: USD, EUR, RUB\n\n";
            }
        }
        
        // Ввод суммы с проверкой
        while (true) {
            std::cout << "Сумма: ";
            std::cin >> amountStr;
            
            if (isValidAmount(amountStr)) {
                amount = std::stod(amountStr);
                if (amount > 0) {
                    break;
                } else {
                    std::cout << "❌ ОШИБКА: сумма должна быть больше 0!\n\n";
                }
            } else {
                std::cout << "❌ ОШИБКА: '" << amountStr << "' - это не число!\n";
                std::cout << "   Введите число, например: 100, 50.5, 1000\n\n";
            }
        }
        
        // Конвертация
        std::cout << "\n🔄 Конвертирую...\n";
        double result = converter.convert(amount, from, to);
        
        if (result > 0) {
            std::cout << "✅ РЕЗУЛЬТАТ: " << amount << " " << from << " = " << result << " " << to << "\n\n";
        } else {
            std::cout << "❌ Ошибка конвертации. Проверьте:\n";
            std::cout << "   - Подключение к интернету\n";
            std::cout << "   - Коды валют (USD, EUR, RUB...)\n\n";
        }
        
        // Продолжить?
        std::cout << "Конвертировать ещё? (д/н): ";
        char again;
        std::cin >> again;
        if (again != 'д' && again != 'Д' && again != 'y' && again != 'Y') {
            std::cout << "\n👋 До свидания!\n";
            break;
        }
        std::cout << "\n";
    }
    
    system("pause");
    return 0;
}
