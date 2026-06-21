#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "crypt.h"

using namespace std;

static void loadKeys(const string& file, Matrix& A, Vector& b, Vector& s) {
    ifstream in(file);
    string line;

    while (getline(in, line)) {
        if (line.rfind("A=", 0) == 0)
            A = parseMatrix(line.substr(2));
        else if (line.rfind("b=", 0) == 0)
            b = parseVector(line.substr(2));
        else if (line.rfind("s=", 0) == 0)
            s = parseVector(line.substr(2));
    }
}

static string bitsToText(const vector<int>& bits) {
    string out;

    for (size_t i = 0; i + 7 < bits.size(); i += 8) {
        int val = 0;

        for (int j = 0; j < 8; j++) {
            val = (val << 1) | bits[i + j];
        }

        out.push_back((char)val);
    }

    return out;
}

int main(int argc, char* argv[]) {

    LWEParams p;
    p.n = 1024;
    p.q = 3329;

    if (argc < 2) {
        cout << "Usage:\n";
        cout << "./main gen\n";
        cout << "./main enc keys.txt input.txt > cipher.txt\n";
        cout << "./main dec keys.txt cipher.txt\n";
        return 0;
    }

    string mode = argv[1];

    if (mode == "gen") {

        SecretKey sk;
        PublicKey pk = keygen(p, sk);

        cout << "A=" << matToStr(pk.A) << "\n";
        cout << "b=" << vecToStr(pk.b) << "\n";
        cout << "s=" << vecToStr(sk.s) << "\n";

        return 0;
    }

    if (mode == "enc" && argc == 4) {

        Matrix A;
        Vector b, s;
        loadKeys(argv[2], A, b, s);

        PublicKey pk{A, b};

        ifstream in(argv[3]);
        string msg;

        while (getline(in, msg)) {

            if (msg.empty()) continue;

            Vector bits = textToBits(msg);
            auto ct = encryptBits(pk, p, bits);

            for (auto &c : ct) {
                for (int i = 0; i < (int)c.u.size(); i++) {
                    cout << c.u[i];
                    if (i + 1 < (int)c.u.size()) cout << ",";
                }
                cout << "|" << c.v << "\n";
            }
        }

        return 0;
    }

    if (mode == "dec" && argc == 4) {

        Matrix A;
        Vector b, s;
        loadKeys(argv[2], A, b, s);

        PublicKey pk{A, b};
        SecretKey sk{s};

        ifstream in(argv[3]);
        string line;

        vector<int> bits;

        while (getline(in, line)) {

            if (line.empty()) continue;

            size_t sep = line.find('|');
            if (sep == string::npos) continue;

            string uStr = line.substr(0, sep);
            string vStr = line.substr(sep + 1);

            int v = stoi(vStr);

            Vector u;
            string num;

            for (char c : uStr) {
                if (c == ',') {
                    u.push_back(stoi(num));
                    num.clear();
                } else {
                    num.push_back(c);
                }
            }
            if (!num.empty())
                u.push_back(stoi(num));

            Ciphertext ct{u, v};

            bits.push_back(decrypt(ct, sk, p));
        }

        cout << bitsToText(bits) << "\n";

        return 0;
    }

    cout << "Invalid mode\n";
    return 0;
}