#include <iostream>
#include <vector>
#include <string>
#include <bitset>

// Function: converts each character in the string to its ASCII binary
std::vector<int> stringToBinary(const std::string& input) {
    std::vector<int> result;

    for (char c : input) {
        std::bitset<8> binary(c);   // 8-bit ASCII representation
        result.push_back(static_cast<unsigned char>(c));
    }

    return result;
}

//Simple vector mul with a int
std::vector<int> vectorMulWithInt(const std::vector<int>& input, int k) {
    std::vector<int> result;
    result.reserve(input.size()); // optional but efficient

    for (int value : input) {
        result.push_back(value * k);
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

    std::vector<int> binaries;

    if (!isBinary)
        binaries = stringToBinary(message);
    else
        binaries = {std::stoi(message)};
        
    for (const auto& b : binaries)
        std::cout << b << "\n";
        
    return 0;
}