#include <iostream>
#include <vector>
#include <string>
#include <bitset>

// Function: converts each character in the string to its ASCII binary
std::vector<std::string> stringToBinary(const std::string& input) {
    std::vector<std::string> result;

    for (char c : input) {
        std::bitset<8> binary(c);   // 8-bit ASCII representation
        result.push_back(binary.to_string());
    }

    return result;
}

//std::vector<std::string> encrypt(const std::string& input) {}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./program <message> [0 or 1]\n";
        return 1;
    }

    std::string message = argv[1];

    bool isBinary = false;

    if (argc >= 3) {
        isBinary = std::stoi(argv[2]) != 0;
    }

    std::vector<std::string> binaries;

    if (!isBinary)
        binaries = stringToBinary(message);
    else
        binaries = {message};

    for (const auto& b : binaries)
        std::cout << b << "\n";

    return 0;
}