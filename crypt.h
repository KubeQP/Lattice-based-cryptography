#pragma once

#include "core.h"
#include <vector>
#include <string>

using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;

struct PublicKey {
    Matrix A;
    Vector b;
};

struct SecretKey {
    Vector s;
};

struct Ciphertext {
    Vector u;
    int v;
};

// crypto
PublicKey keygen(const LWEParams&, SecretKey&);

Ciphertext encrypt(const PublicKey&, const LWEParams&, int);

std::vector<Ciphertext> encryptBits(const PublicKey&, const LWEParams&, const Vector&);

int decrypt(const Ciphertext&, const SecretKey&, const LWEParams&);

std::vector<int> decryptBits(const std::vector<Ciphertext>&, const SecretKey&, const LWEParams&);

Vector parseVector(const std::string&);
Matrix parseMatrix(const std::string&);

std::string vecToStr(const Vector&);
std::string matToStr(const Matrix&);

Vector textToBits(const std::string&);