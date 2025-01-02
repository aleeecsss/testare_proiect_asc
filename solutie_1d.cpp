#include <bits/stdc++.h>

const int N = 1024;
int n, Q, descriptor, sz, x, y, p, q, v[N];

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

void ADD() {
    fin >> n;
    while (n --) {
        fin >> descriptor >> sz;
        sz = (sz + 7) / 8;
        bool ok = true;
        for (int i = 0; i < N - sz + 1; ++i) {
            ok = true;
            for (int j = i; j < i + sz; ++j) {
                if (v[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok == true) {
                for (int j = i; j < i + sz; ++j) {
                    v[j] = descriptor;
                }
                fout << descriptor << ": " << "(" << i << ", " << i + sz - 1 << ")\n";
                break;
            }
        }
        if (ok == false) {
            fout << descriptor << ": " << "(0, 0)\n";
        }
    }
    return;
}

void GET(int descriptor) {
    x = N, y = 0;
    for (int i = 0; i < N; ++i) {
        if (v[i] == descriptor) {
            x = std::min(x, i);
            y = std::max(y, i);
        }
    }
    if (x == N) {
        x = 0;
    }
    fout << "(" << x << ", " << y << ")\n";
    return;
}

void DELETE() {
    fin >> descriptor;
    for (int i = 0; i < N; ++i) {
        if (v[i] == descriptor) {
            v[i] = 0;
        }
    }
    for (int i = 0; i < N; ++i) {
        if (v[i] != 0) {
            fout << v[i] << ": ";
            GET(v[i]);
            i = y;
        }
    }
    return;
}

void DEFRAGMENTATION() {
    p = 0, q = 0;
    int x;
    while (q < N) {
        if (v[q] != 0) {
            x = v[q];
            v[q] = 0;
            v[p] = x;
            ++p;
        }
        ++q;
    }
    for (int i = 0; i < N; ++i) {
        if (v[i] != 0) {
            fout << v[i] << ": ";
            GET(v[i]);
            i = y;
        }
    }
    return;
}

int main() {
    fin >> Q;
    while (Q --) {
        int type;
        fin >> type;
        switch (type) {
            case 1:
                ADD();
                break;
            case 2:
                fin >> descriptor;
                GET(descriptor);
                break;
            case 3:
                DELETE();
                break;
            case 4:
                DEFRAGMENTATION();
                break;
        }
    }
    return 0;
}
