#include "Proverka.h"

std::string InputString()
{
    std::string str;
    getline(std::cin >> std::ws, str);
    std::cerr << str;
    return str;
}
