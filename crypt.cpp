#include "crypt.h"
#include <cmath>

#include <sstream>

// =====================
// MISSING HELPERS ONLY
// =====================

Vector parseVector(const std::string& str) {
    Vector v;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, ',')) {
        if (!item.empty())
            v.push_back(std::stoi(item));
    }
    return v;
}

Matrix parseMatrix(const std::string& str) {
    Matrix A;
    std::stringstream ss(str);
    std::string row;

    while (std::getline(ss, row, ';')) {
        A.push_back(parseVector(row));
    }
    return A;
}

std::string vecToStr(const Vector& v) {
    std::string s;
    for (size_t i = 0; i < v.size(); i++) {
        s += std::to_string(v[i]);
        if (i + 1 < v.size()) s += ",";
    }
    return s;
}

std::string matToStr(const Matrix& A) {
    std::string s;
    for (size_t i = 0; i < A.size(); i++) {
        s += vecToStr(A[i]);
        if (i + 1 < A.size()) s += ";";
    }
    return s;
}

Vector textToBits(const std::string& text) {
    Vector bits;

    for (char c : text) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((c >> i) & 1);
        }
    }

    return bits;
}

PublicKey keygen(const LWEParams& p, SecretKey& sk) {
    sk.s = randomVector(p);

    Matrix A = randomMatrix(p);
    Vector e = noiseVector(p);

    Vector As = matrixVectorMul(A, sk.s, p);
    Vector b = addVectors(As, e, p);

    return {A, b};
}

Ciphertext encrypt(const PublicKey& pk, const LWEParams& p, int m) {
    Vector r = randomVector(p);

    Matrix AT = transpose(pk.A);

    Vector u = matrixVectorMul(AT, r, p);

    long long v = 0;

    for (int i = 0; i < p.n; i++) {
        v += (long long)pk.b[i] * r[i];
    }

    v = mod(v, p.q);

    if (m == 1)
        v = mod(v + p.q / 2, p.q);

    return {u, (int)v};
}

std::vector<Ciphertext> encryptBits(
    const PublicKey& pk,
    const LWEParams& p,
    const std::vector<int>& message)
{
    std::vector<Ciphertext> out;

    Matrix AT = transpose(pk.A);

    for (int m : message) {
        Vector r = randomVector(p);

        Vector u = matrixVectorMul(AT, r, p);

        long long v = 0;
        for (int i = 0; i < p.n; i++)
            v += (long long)pk.b[i] * r[i];

        v = mod(v, p.q);

        if (m == 1)
            v = mod(v + p.q / 2, p.q);

        out.push_back({u, (int)v});
    }

    return out;
}

int decrypt(const Ciphertext& ct, const SecretKey& sk, const LWEParams& p) {

    long long us = 0;

    for (int i = 0; i < p.n; i++)
        us += (long long)sk.s[i] * ct.u[i];

    us = mod(us, p.q);

    int diff = mod((long long)ct.v - us, p.q);

    int dist0 = diff;
    int dist1 = std::abs(diff - p.q / 2);

    return (dist1 < dist0) ? 1 : 0;
}

std::vector<int> decryptBits(
    const std::vector<Ciphertext>& ct,
    const SecretKey& sk,
    const LWEParams& p)
{
    std::vector<int> out;

    for (const auto& c : ct) {

        long long us = 0;

        for (int i = 0; i < p.n; i++)
            us += (long long)sk.s[i] * c.u[i];

        us = mod(us, p.q);

        int diff = mod((long long)c.v - us, p.q);

        int dist0 = diff;
        int dist1 = std::abs(diff - p.q / 2);

        out.push_back(dist1 < dist0 ? 1 : 0);
    }

    return out;
}