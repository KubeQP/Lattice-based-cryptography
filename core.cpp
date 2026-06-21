#include "core.h"
#include <cstdlib>

int mod(long long x, int q) {
    x %= q;
    if (x < 0) x += q;
    return (int)x;
}

Vector randomVector(const LWEParams& p) {
    Vector v(p.n);
    for (int i = 0; i < p.n; i++)
        v[i] = rand() % p.q;
    return v;
}

Vector noiseVector(const LWEParams& p) {
    Vector e(p.n);
    for (int i = 0; i < p.n; i++)
        e[i] = 0; (rand() % 3 -1); // -1, 0, or 1
    return e;
}

Matrix randomMatrix(const LWEParams& p) {
    Matrix A(p.n, Vector(p.n));
    for (int i = 0; i < p.n; i++)
        for (int j = 0; j < p.n; j++)
            A[i][j] = rand() % p.q;
    return A;
}

Vector matrixVectorMul(const Matrix& A, const Vector& x, const LWEParams& p) {
    Vector r(p.n, 0);

    for (int i = 0; i < p.n; i++) {
        long long sum = 0;

        for (int j = 0; j < p.n; j++) {
            sum += (long long)A[i][j] * x[j];
        }

        r[i] = mod(sum, p.q);
    }

    return r;
}

Vector addVectors(const Vector& a, const Vector& b, const LWEParams& p) {
    Vector r(p.n);

    for (int i = 0; i < p.n; i++)
        r[i] = mod((long long)a[i] + b[i], p.q);

    return r;
}

Matrix transpose(const Matrix& A) {
    Matrix T(A[0].size(), Vector(A.size()));

    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < A[0].size(); j++)
            T[j][i] = A[i][j];

    return T;
}