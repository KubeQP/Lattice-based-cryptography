#include <iostream>
#include <ctime>
#include "crypt.h"

int main() {
    srand(time(nullptr));

    LWEParams p;
    p.n = 1024;
    p.q = 3329;

    SecretKey sk;

    PublicKey pk = keygen(p, sk);

    std::vector<int> message = {1,0,1,1,0,0,1};

    auto ct = encryptBits(pk, p, message);
    auto dec = decryptBits(ct, sk, p);
    
    std::cout << "Original: ";
    for (int b : message) std::cout << b << " ";
    std::cout << "\nDecrypted: ";
    for (int b : dec) std::cout << b << " ";
    std::cout << "\n";
}