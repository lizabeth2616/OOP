#include <iostream>
#include <string>
#include <cctype>


int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
    std::string number;

    for (char c : input) {
        if (isdigit(c)) {
            number += c;
        } else if (c == ' ') {
            number += ' ';
        }
    }

    if (!number.empty()) {
        std::cout << "Numbers string: " << number << std::endl;
    }
    else {
        std::cout << "No numbers found in the string." << std::endl;
    }
    
    return 0;
}