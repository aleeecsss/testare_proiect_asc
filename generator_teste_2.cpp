#include <bits/stdc++.h>

const int N = 1024;
int Q = 512;
std::mt19937 rng(6203);

int n, descriptor, Free, sz, x, y, p, q, v[N], f[256];
int cnt, Max = 0;

std::ofstream fout("test.out");

void ADD() {
    fout << n << "\n";
    while (n --) {
        int d = rng() % Free + 1;

        for (int i = 1; i < 256; ++i) {
            if (f[i] == 0) {
                -- d;

                if (d == 0) {
                    descriptor = i;
                    break;
                }
            }
        }

        sz = rng() % 8184 + 9;

        fout << descriptor << " " << sz << "\n";

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
                Max -= sz;
                --Free;
                f[descriptor] = 1;
                for (int j = i; j < i + sz; ++j) {
                    v[j] = descriptor;
                }
                break;
            }
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
    return;
}

void DELETE() {
    for (int i = 0; i < N; ++i) {
        if (v[i] == descriptor) {
            v[i] = 0;
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
    return;
}

int main() {
    fout << Q << "\n";

    while (Q --) {
        for (int i = 0; i < 256; ++i) {
            f[i] = 0;
        }

        cnt = 0;

        for (int i = 0; i < N; ++i) {
            if (v[i] == 0) {
                ++cnt;
                Max = std::max(Max, cnt);
            } else {
                cnt = 0;
            }
            f[v[i]] ++;
        }

        Free = 0;

        for (int i = 1; i < 256; ++i) {
            if (f[i] == 0) {
                ++Free;
            }
        }

        int type;
        type = rng() % 4 + 1;

        if (Free == 0) {
            type = rng() % 3 + 2;
        }

        fout << type << "\n";

        switch (type) {
            case 1:
                n = rng() % Free + 1;
                ADD();
                break;
            case 2:
                if (Free == 255) {
                    descriptor = rng() % 255 + 1;
                }
                else {
                    int d = rng() % (255 - Free) + 1;
                    for (int i = 1; i < 256; ++i) {
                        if (f[i] != 0) {
                            -- d;

                            if (d == 0) {
                                descriptor = i;
                                break;
                            }
                        }
                    }
                }

                fout << descriptor << "\n";

                GET(descriptor);
                break;
            case 3:
                if (Free == 255) {
                    descriptor = rng() % 255 + 1;
                }
                else {
                    int d = rng() % (255 - Free) + 1;
                    for (int i = 1; i < 256; ++i) {
                        if (f[i] != 0) {
                            -- d;

                            if (d == 0) {
                                descriptor = i;
                                f[descriptor] = 0;
                                break;
                            }
                        }
                    }
                }

                fout << descriptor << "\n";

                DELETE();
                break;
            case 4:
                DEFRAGMENTATION();
                break;
        }
    }
    return 0;
}
