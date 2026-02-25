#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <cstdlib>  
#include <ctime>    


int invalidArgument() {
    std::cout << "Invalid argument.\n Usage: ./main OPTION (KEY) (DATA)\n";
    return 0;
}

bool isBinary(const std::string& s) {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(),
                       [](char c){ return c=='0' || c=='1'; });
}

std::vector<std::string> toVector(const std::string& temp) {
    std::vector<std::string> result;

    for (size_t i = 0; i < temp.size(); i += 8) {
        result.push_back(temp.substr(i, 8));
    }

    return result;
}

// Function: converts each character in the string to its ASCII binary
std::vector<std::string> stringToBinary(const std::string& input) {
    std::vector<std::string> result;

    for (char c : input) {
        std::bitset<8> binary(c);   // 8-bit ASCII representation
        result.push_back(binary.to_string());
    }

    return result;
}

std::vector<std::vector<int>> randomMatrix(int n, int m, int minVal = 0, int maxVal = 9) {
    std::vector<std::vector<int>> result;
    result.reserve(n); 

    for (int i = 0; i < n; i++) {
        std::vector<int> row;
        row.reserve(m); 

        for (int j = 0; j < m; j++) {
            int val = minVal + std::rand() % (maxVal - minVal + 1);
            row.push_back(val);
        }

        result.push_back(row);
    }

    return result;
}

int decode(std::vector<std::string> input) {
    return 0;
} 


std::vector<std::string> encode(std::vector<std::string> input) {
    return {};
}


int main(int argc, char* argv[]) {
    std::string temp;
    std::string key;
    std::vector<std::string> data;

    if (argc > 2) {
        temp = argv[argc-1];
        if (argc > 3) {
            key = argv[argc-2];
        }
    }
    if (!isBinary(temp)) {
        data = stringToBinary(temp);
    } else {
        data = toVector(temp);
    }

    for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];  

    if (arg == "decode") {

        if (argc > 3){
            decode(data);
        } else {
            invalidArgument();
        }
        return 0;
    }

    if (arg == "encode") {
        if (argc > 2) {
            encode(data);
        } else {
            invalidArgument();
        }
        return 0;
        }
    }
    std::cout << "Data:\n";
    for (const auto& byte : data) {
        std::cout << byte << "\n";
    }        

    std::srand(std::time(nullptr)); // seed för slump

    auto mat = randomMatrix(3, 4); // 3x4 matris

    for (auto& row : mat) {
        for (auto val : row)
            std::cout << val << " ";
        std::cout << "\n";
    }

    std::cout << "\n";

    return 0;
}