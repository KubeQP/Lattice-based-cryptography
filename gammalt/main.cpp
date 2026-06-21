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

template <typename T>
void printData(const std::vector<T>& v,
               typename std::enable_if<!std::is_same<T, std::vector<T>>::value &&
                                       !std::is_same<T, std::bitset<8>>::value>::type* = 0) {
    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

// Overload for nested vectors
template <typename T>
void printData(const std::vector<std::vector<T>>& v) {
    for (const auto& row : v) {
        printData(row);
    }
}

// Overload for vector of bitsets
template <size_t N>
void printData(const std::vector<std::bitset<N>>& v) {
    for (const auto& elem : v) {
        std::cout << elem.to_string() << " ";
    }
    std::cout << "\n";
}

//factorial number system. length! > n 
std::vector<int> intToPermVector(int n, int length) {
    std::vector<int> elems(length);
    for (int i = 0; i < length; ++i) elems[i] = i;

    std::vector<int> result;

    for (int i = length; i >= 1; --i) {
        int factorial = 1;
        for (int j = 1; j < i; ++j) factorial *= j;

        int index = n / factorial;
        n %= factorial;

        result.push_back(elems[index]);
        elems.erase(elems.begin() + index);
    }

    return result;
}

int permVectorToInt(const std::vector<int>& v) {
    int n = 0;
    int length = v.size();
    std::vector<int> elems(length);
    for (int i = 0; i < length; ++i) elems[i] = i;

    for (int i = 0; i < length; ++i) {
        auto it = std::find(elems.begin(), elems.end(), v[i]);
        int index = it - elems.begin();
        int factorial = 1;
        for (int j = 1; j < length - i; ++j) factorial *= j;

        n += index * factorial;
        elems.erase(it);
    }

    return n;
}

bool isBinary(const std::string& s) {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(),
                       [](char c){ return c=='0' || c=='1'; });
}

std::vector<int> toVectorInt(const std::string& temp) {
    std::vector<int> result;

    for (size_t i = 0; i < temp.size(); i += 8) {
        std::string chunk = temp.substr(i, 8); // get 8-character chunk
        int value = 0;

        for (char c : chunk) {
            value = (value << 1) | (c == '1' ? 1 : 0);
        }

        result.push_back(value);
    }

    return result;
}

std::vector<int> stringToInt(const std::string& input) {
    std::vector<int> result;

    for (char c : input) {
        result.push_back(static_cast<int>(c));
    }

    return result;
}

std::vector<std::vector<int>> mulMatrix(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B
) {
    int n = A.size();
    int m = A[0].size();
    int p = B[0].size();

    std::vector<std::vector<int>> C(n, std::vector<int>(p, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
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

std::vector<std::vector<int>> solvableMatrix(int n, int m, int minVal = 0, int maxVal = 9) {
    std::vector<std::vector<int>> A = randomMatrix(n, m,minVal, maxVal);
    std::vector<std::vector<int>> B = randomMatrix(n, m,minVal, maxVal);
    return mulMatrix(A, B);
    
}

int decode(std::vector<int> input) {
    printData(input);
    return 0;
} 


int encode(std::vector<int> input) {
    printData(input);
    return 0;
}


int main(int argc, char* argv[]) {
    std::string temp;
    std::string key;
    std::vector<int> data;
    std::srand(std::time(nullptr)); // seed för slump


    if (argc > 2) {
        temp = argv[argc-1];
        if (argc > 3) {
            key = argv[argc-2];
        }
    }
    if (!isBinary(temp)) {
        data = stringToInt(temp);
    } else {
        data = toVectorInt(temp);
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
        if (argc > 3) {
            encode(data);
        } else {
            invalidArgument();
        }
        return 0;
    }

    if (arg == "matrix") {
        std::vector<std::vector<int>> matrix = solvableMatrix(3,3);
        printData(matrix);

        return 0;
    }
    if (arg == "test") {
        std::vector<int> test = intToPermVector(data[0], 5);
        printData(test);

        return 0;
    }
    
    }      
    return 0;
invalidArgument();

}


