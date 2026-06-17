#pragma once
#include <vector>

struct LWEParams {
    int n;
    int q;
};

using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;

Vector randomVector(const LWEParams& p);
Vector noiseVector(const LWEParams& p);
Matrix randomMatrix(const LWEParams& p);

Vector matrixVectorMul(const Matrix& A, const Vector& x, const LWEParams& p);
Vector addVectors(const Vector& a, const Vector& b, const LWEParams& p);

Matrix transpose(const Matrix& A);

int mod(long long x, int q);