#pragma once
#include "core.h"
#include <cmath>

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

PublicKey keygen(const LWEParams& p, SecretKey& sk);

Ciphertext encrypt(const PublicKey& pk, const LWEParams& p, int m);

int decrypt(const Ciphertext& ct, const SecretKey& sk, const LWEParams& p);

std::vector<Ciphertext> encryptBits(const PublicKey& pk, const LWEParams& p, const std::vector<int>& message);

std::vector<int> decryptBits(const std::vector<Ciphertext>& ct, const SecretKey& sk, const LWEParams& p);