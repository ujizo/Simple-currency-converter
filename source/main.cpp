#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include "converter.h"

#ifdef _WIN32
#include <windows.h>
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_RED 12
#define COLOR_CYAN 11
#define COLOR_WHITE 15
#define COLOR_MAGENTA 13
#define COLOR_BLUE 9
#else
#define COLOR_GREEN 32
#define COLOR_YELLOW 33
#define COLOR_RED 31
#define COLOR_CYAN 36
#define COLOR_WHITE 37
#define COLOR_MAGENTA 35
#define COLOR_BLUE 34
#endif

void setColor(int color) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    #else
    std::cout << "\033[1;" << color << "m";
    #endif
}

void resetColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
    #else
    std::cout << "\033[0m";
    #endif
}

// ============================================
// АНИМАЦИЯ - ПРЫГАЮЩИЕ $
// ============================================
void convertAnimation(int duration_seconds = 2) {
    const int width = 50;
    const int height = 5;

    auto start = std::chrono::steady_clock::now();

    while (std::chrono::duration_cast<std::chrono::seconds>
           (std::chrono::steady_clock::now() - start).count() < duration_seconds) {

        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        std::cout << "+--------------------------------------------------+\n";
        std::cout << "|              CURRENCY CONVERTER                  |\n";
        std::cout << "+--------------------------------------------------+\n";

        int frame = std::chrono::duration_cast<std::chrono::milliseconds>
                   (std::chrono::steady_clock::now() - start).count() / 100;

        for (int row = 0; row < height; row++) {
            std::cout << "|";
            for (int col = 0; col < width - 2; col++) {
                int jump = (frame + col + row * 3) % 10;

                if (jump < 2 && row == 3) {
                    setColor(COLOR_GREEN);
                    std::cout << "$";
                    resetColor();
                } else if (jump >= 2 && jump < 4 && row == 2) {
                    setColor(COLOR_YELLOW);
                    std::cout << "$";
                    resetColor();
                } else if (jump >= 4 && jump < 6 && row == 1) {
                    setColor(COLOR_GREEN);
                    std::cout << "$";
                    resetColor();
                } else if (jump >= 6 && jump < 8 && row == 2) {
                    setColor(COLOR_YELLOW);
                    std::cout << "$";
                    resetColor();
                } else if (jump >= 8 && row == 3) {
                    setColor(COLOR_GREEN);
                    std::cout << "$";
                    resetColor();
                } else {
                    std::cout << " ";
                }
            }
            std::cout << "|\n";
        }

        std::cout << "+--------------------------------------------------+\n";

        int elapsed = std::chrono::duration_cast<std::chrono::seconds>
                     (std::chrono::steady_clock::now() - start).count();
        int remaining = duration_seconds - elapsed;

        std::cout << "|           Converting... " << remaining << "s            |\n";
        std::cout << "+--------------------------------------------------+\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

struct Currency {
    std::string code;
    std::string name;
};

// 158 ВАЛЮТ - ПОЛНЫЙ СПИСОК
std::vector<Currency> currencies = {
    {"USD", "US Dollar"},
    {"EUR", "Euro"},
    {"RUB", "Russian Ruble"},
    {"GBP", "British Pound Sterling"},
    {"JPY", "Japanese Yen"},
    {"CNY", "Chinese Yuan"},
    {"AUD", "Australian Dollar"},
    {"CAD", "Canadian Dollar"},
    {"CHF", "Swiss Franc"},
    {"HKD", "Hong Kong Dollar"},
    {"SGD", "Singapore Dollar"},
    {"SEK", "Swedish Krona"},
    {"KRW", "South Korean Won"},
    {"NOK", "Norwegian Krone"},
    {"NZD", "New Zealand Dollar"},
    {"INR", "Indian Rupee"},
    {"MXN", "Mexican Peso"},
    {"TWD", "New Taiwan Dollar"},
    {"ZAR", "South African Rand"},
    {"BRL", "Brazilian Real"},
    {"DKK", "Danish Krone"},
    {"PLN", "Polish Zloty"},
    {"THB", "Thai Baht"},
    {"ILS", "Israeli New Shekel"},
    {"TRY", "Turkish Lira"},
    {"UAH", "Ukrainian Hryvnia"},
    {"KZT", "Kazakhstani Tenge"},
    {"BYN", "Belarusian Ruble"},
    {"AMD", "Armenian Dram"},
    {"AZN", "Azerbaijani Manat"},
    {"GEL", "Georgian Lari"},
    {"KGS", "Kyrgyzstani Som"},
    {"TJS", "Tajikistani Somoni"},
    {"MDL", "Moldovan Leu"},
    {"UZS", "Uzbekistani Som"},
    {"AED", "UAE Dirham"},
    {"AFN", "Afghan Afghani"},
    {"ALL", "Albanian Lek"},
    {"ANG", "Netherlands Antillean Guilder"},
    {"AOA", "Angolan Kwanza"},
    {"ARS", "Argentine Peso"},
    {"AWG", "Aruban Florin"},
    {"BAM", "Bosnia-Herzegovina Convertible Mark"},
    {"BBD", "Barbadian Dollar"},
    {"BDT", "Bangladeshi Taka"},
    {"BGN", "Bulgarian Lev"},
    {"BHD", "Bahraini Dinar"},
    {"BIF", "Burundian Franc"},
    {"BMD", "Bermudian Dollar"},
    {"BND", "Brunei Dollar"},
    {"BOB", "Bolivian Boliviano"},
    {"BSD", "Bahamian Dollar"},
    {"BTN", "Bhutanese Ngultrum"},
    {"BWP", "Botswana Pula"},
    {"BZD", "Belize Dollar"},
    {"CDF", "Congolese Franc"},
    {"CLP", "Chilean Peso"},
    {"COP", "Colombian Peso"},
    {"CRC", "Costa Rican Colon"},
    {"CUP", "Cuban Peso"},
    {"CVE", "Cape Verdean Escudo"},
    {"CZK", "Czech Koruna"},
    {"DJF", "Djiboutian Franc"},
    {"DOP", "Dominican Peso"},
    {"DZD", "Algerian Dinar"},
    {"EGP", "Egyptian Pound"},
    {"ERN", "Eritrean Nakfa"},
    {"ETB", "Ethiopian Birr"},
    {"FJD", "Fijian Dollar"},
    {"FKP", "Falkland Islands Pound"},
    {"FOK", "Faroese Krona"},
    {"GGP", "Guernsey Pound"},
    {"GHS", "Ghanaian Cedi"},
    {"GIP", "Gibraltar Pound"},
    {"GMD", "Gambian Dalasi"},
    {"GNF", "Guinean Franc"},
    {"GTQ", "Guatemalan Quetzal"},
    {"GYD", "Guyanese Dollar"},
    {"HNL", "Honduran Lempira"},
    {"HRK", "Croatian Kuna"},
    {"HTG", "Haitian Gourde"},
    {"HUF", "Hungarian Forint"},
    {"IDR", "Indonesian Rupiah"},
    {"IMP", "Isle of Man Pound"},
    {"IQD", "Iraqi Dinar"},
    {"IRR", "Iranian Rial"},
    {"ISK", "Icelandic Krona"},
    {"JEP", "Jersey Pound"},
    {"JMD", "Jamaican Dollar"},
    {"JOD", "Jordanian Dinar"},
    {"KES", "Kenyan Shilling"},
    {"KHR", "Cambodian Riel"},
    {"KID", "Kiribati Dollar"},
    {"KMF", "Comorian Franc"},
    {"KYD", "Cayman Islands Dollar"},
    {"LAK", "Lao Kip"},
    {"LBP", "Lebanese Pound"},
    {"LKR", "Sri Lankan Rupee"},
    {"LRD", "Liberian Dollar"},
    {"LSL", "Lesotho Loti"},
    {"LYD", "Libyan Dinar"},
    {"MAD", "Moroccan Dirham"},
    {"MGA", "Malagasy Ariary"},
    {"MKD", "Macedonian Denar"},
    {"MMK", "Myanmar Kyat"},
    {"MNT", "Mongolian Tugrik"},
    {"MOP", "Macanese Pataca"},
    {"MRU", "Mauritanian Ouguiya"},
    {"MUR", "Mauritian Rupee"},
    {"MVR", "Maldivian Rufiyaa"},
    {"MWK", "Malawian Kwacha"},
    {"MYR", "Malaysian Ringgit"},
    {"MZN", "Mozambican Metical"},
    {"NAD", "Namibian Dollar"},
    {"NGN", "Nigerian Naira"},
    {"NIO", "Nicaraguan Cordoba"},
    {"NPR", "Nepalese Rupee"},
    {"OMR", "Omani Rial"},
    {"PAB", "Panamanian Balboa"},
    {"PEN", "Peruvian Sol"},
    {"PGK", "Papua New Guinean Kina"},
    {"PHP", "Philippine Peso"},
    {"PKR", "Pakistani Rupee"},
    {"PYG", "Paraguayan Guarani"},
    {"QAR", "Qatari Riyal"},
    {"RON", "Romanian Leu"},
    {"RSD", "Serbian Dinar"},
    {"RWF", "Rwandan Franc"},
    {"SAR", "Saudi Riyal"},
    {"SBD", "Solomon Islands Dollar"},
    {"SCR", "Seychellois Rupee"},
    {"SDG", "Sudanese Pound"},
    {"SHP", "Saint Helena Pound"},
    {"SLE", "Sierra Leonean Leone"},
    {"SOS", "Somali Shilling"},
    {"SRD", "Surinamese Dollar"},
    {"SSP", "South Sudanese Pound"},
    {"STN", "Sao Tome and Principe Dobra"},
    {"SYP", "Syrian Pound"},
    {"SZL", "Eswatini Lilangeni"},
    {"TND", "Tunisian Dinar"},
    {"TOP", "Tongan Paanga"},
    {"TTD", "Trinidad and Tobago Dollar"},
    {"TVD", "Tuvaluan Dollar"},
    {"TZS", "Tanzanian Shilling"},
    {"UGX", "Ugandan Shilling"},
    {"UYU", "Uruguayan Peso"},
    {"VES", "Venezuelan Bolivar"},
    {"VND", "Vietnamese Dong"},
    {"VUV", "Vanuatu Vatu"},
    {"WST", "Samoan Tala"},
    {"XAF", "Central African CFA Franc"},
    {"XCD", "East Caribbean Dollar"},
    {"XOF", "West African CFA Franc"},
    {"XPF", "CFP Franc"},
    {"YER", "Yemeni Rial"},
    {"ZMW", "Zambian Kwacha"},
    {"ZWL", "Zimbabwean Dollar"}
};

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool isValidCurrencyCode(const std::string& code) {
    for (const auto& currency : currencies) {
        if (currency.code == code) {
            return true;
        }
    }
    return false;
}

void showAllCurrencies() {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "         ALL AVAILABLE CURRENCIES         \n";
    std::cout << std::string(80, '=') << "\n\n";

    for (size_t i = 0; i < currencies.size(); i++) {
        std::cout << std::setw(3) << (i + 1) << ". ";
        std::cout << std::setw(5) << currencies[i].code << " - ";
        std::cout << std::setw(35) << std::left << currencies[i].name << std::right;

        if ((i + 1) % 2 == 0) {
            std::cout << "\n";
        } else {
            std::cout << "  ";
        }
    }

    std::cout << "\n\n" << std::string(80, '=') << "\n\n";
}

Currency selectCurrency(const std::string& prompt) {
    std::string input;
    int choice;

    while (true) {
        std::cout << prompt << " (1-" << currencies.size() << "): ";
        std::cin >> input;

        bool isNumber = true;
        for (char c : input) {
            if (!std::isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (isNumber) {
            choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(currencies.size())) {
                std::cout << "  Selected: " << currencies[choice - 1].code
                         << " - " << currencies[choice - 1].name << "\n\n";
                return currencies[choice - 1];
            } else {
                std::cout << "  Error: enter 1-" << currencies.size() << "!\n\n";
            }
        } else {
            std::cout << "  Error: Please enter a number (1-" << currencies.size() << ")!\n\n";
        }
    }
}

int main() {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    #endif

    Converter converter;
    double amount;

    setColor(COLOR_YELLOW);
    std::cout << "+--------------------------------------------------+\n";
    std::cout << "|           CURRENCY CONVERTER v1.4               |\n";
    std::cout << "+--------------------------------------------------+\n";
    resetColor();

    setColor(COLOR_CYAN);
    std::cout << "|       158 CURRENCIES - REAL TIME RATES          |\n";
    std::cout << "+--------------------------------------------------+\n\n";
    resetColor();

    // АВТОМАТИЧЕСКИЙ ПОКАЗ ВСЕХ ВАЛЮТ ПРИ ЗАПУСКЕ
    showAllCurrencies();

    while (true) {
        std::cout << "\n" << std::string(50, '-') << "\n";
        std::cout << "           NEW CONVERSION           \n";
        std::cout << std::string(50, '-') << "\n\n";

        std::cout << "FROM CURRENCY\n";
        Currency fromCurrency = selectCurrency("From");

        std::cout << "TO CURRENCY\n";
        Currency toCurrency = selectCurrency("To");

        while (true) {
            std::cout << "Amount: ";
            std::cin >> amount;

            if (std::cin.fail() || amount <= 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Error: Enter a positive number!\n\n";
            } else {
                std::cout << "Amount set: " << amount << "\n\n";
                break;
            }
        }

        // АНИМАЦИЯ КОНВЕРТАЦИИ
        convertAnimation(2);

        double result = converter.convert(amount, fromCurrency.code, toCurrency.code);

        if (result > 0) {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            // Показываем список валют снова после конвертации
            showAllCurrencies();

            setColor(COLOR_GREEN);
            std::cout << "+--------------------------------------------------+\n";
            std::cout << "|           CONVERSION SUCCESS                    |\n";
            std::cout << "+--------------------------------------------------+\n";
            std::cout << "|                                                  |\n";
            std::cout << "|    " << amount << " " << fromCurrency.code;
            std::cout << " = " << result << " " << toCurrency.code;
            std::cout << "    |\n";
            std::cout << "|                                                  |\n";
            std::cout << "|    " << fromCurrency.name << " -> " << toCurrency.name << "\n";
            std::cout << "|                                                  |\n";
            std::cout << "|    Rate: 1 " << fromCurrency.code << " = "
                     << std::fixed << std::setprecision(2)
                     << (result / amount) << " " << toCurrency.code << "\n";
            std::cout << "|                                                  |\n";
            std::cout << "+--------------------------------------------------+\n\n";
            resetColor();
        } else {
            setColor(COLOR_RED);
            std::cout << "+--------------------------------------------------+\n";
            std::cout << "|           CONVERSION FAILED                     |\n";
            std::cout << "+--------------------------------------------------+\n";
            std::cout << "|                                                  |\n";
            std::cout << "|  Please check:                                   |\n";
            std::cout << "|  * Internet connection                           |\n";
            std::cout << "|  * Currency codes                                |\n";
            std::cout << "|  * API availability                              |\n";
            std::cout << "|                                                  |\n";
            std::cout << "+--------------------------------------------------+\n\n";
            resetColor();
        }

        std::cout << "Convert another currency? (y/n): ";
        char again;
        std::cin >> again;

        if (again != 'y' && again != 'Y') {
            setColor(COLOR_YELLOW);
            std::cout << "\n+--------------------------------------------------+\n";
            std::cout << "|     Thank you for using Currency Converter!     |\n";
            std::cout << "|           Have a great day!                    |\n";
            std::cout << "+--------------------------------------------------+\n\n";
            resetColor();
            break;
        }
    }

    return 0;
}
