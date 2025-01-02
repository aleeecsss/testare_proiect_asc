#include <bits/stdc++.h>

const int N = 1024, D = 256;
int Q = 512, Free, v[N], cnt, f[D];
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int getDthElement(int d, int c) {
    for (int w = 1; w < D; ++w) {
        if (f[w] > 0 && c == 0) {
            --d;
        }

        if (f[w] == 0 && c == 1) {
            --d;
        }

        if (d == 0) {
            return w;
        }
    }

    return rng() % (D - 1) + 1;
}

void ADD() {
    int n;
    /// fin >> n;

    n = rng() % Free + 1;
    std::cout << n << "\n";

    for (int i = 0; i < n; ++i) {
        int d, descriptor, sz;

        d = rng() % Free + 1;
        descriptor = getDthElement(d, 1);
        sz = rng() % (8 * (N / n) - 8) + 9;

        std::cout << descriptor << " " << sz << "\n";

        sz = (sz + 7) / 8;

        int combo = 0;

        for (int k = 0; k < N; ++k) {
            if (!v[k]) {
                ++combo;

                if (combo == sz) {
                    k = k - sz + 1;

                    for (int l = k; l < k + sz; ++l) {
                        v[l] = descriptor;
                    }

                    ++f[descriptor];
                    --Free;

                    goto foundInterval;
                }
            } else {
                combo = 0;
            }
        }

        foundInterval: {}
    }

    return;
}

void GET(int descriptor) {
    int x = N, y = 0;
    for (int i = 0; i < N; ++i) {
        if (v[i] == descriptor) {
            x = std::min(x, i);
            y = std::max(y, i);
        }
    }

    return;
}

void DELETE() {
    int descriptor, d;
    if (Free == D - 1) {
        descriptor = rng() % (D - 1) + 1;
    } else {
        d = rng() % (D - 1 - Free) + 1;
        descriptor = getDthElement(d, 0);
    }

    std::cout << descriptor << "\n";

    for (int i = 0; i < N; ++i) {
        if (v[i] == descriptor) {
            v[i] = 0;
        }
    }

    return;
}

void DEFRAGMENTATION() {
    int p = 0, q = 0;
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
    return;
}

int main() {
    std::cout << Q << "\n";

    while (Q --) {
        int type;

        for (int w = 1; w < D; ++w) {
            f[w] = 0;
        }

        for (int i = 0; i < N; ++i) {
            f[v[i]]++;
        }

        Free = 0;

        for (int w = 1; w < D; ++w) {
            if (f[w] == 0) {
                ++Free;
            }
        }

        if (Free) {
            type = rng() % 4 + 1;
        } else {
            type = rng() % 3 + 2;
        }

        std::cout << type << "\n";

        if (type == 1) {
            ADD();
        }

        if (type == 2) {
            int descriptor, d;
            if (Free == D - 1) {
                descriptor = rng() % (D - 1) + 1;
            } else {
                d = rng() % (D - 1 - Free) + 1;
                descriptor = getDthElement(d, 0);
            }

            std::cout << descriptor << "\n";

            GET(descriptor);
        }

        if (type == 3) {
            DELETE();
        }

        if (type == 4) {
            DEFRAGMENTATION();
        }
    }

    return 0;
}
