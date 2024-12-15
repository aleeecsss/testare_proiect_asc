#include <bits/stdc++.h>

const int N = 1024, D = 256;
int Q = 256, Free, mat[N][N + 1], cnt, w[D], f[D];
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int getDthElement(int d, int c) {
    for (int v = 1; v < D; ++v) {
        if (f[v] > 0 && c == 0) {
            --d;
        }

        if (f[v] == 0 && c == 1) {
            --d;
        }

        if (d == 0) {
            return v;
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
        sz = rng() % (8 * (N / 2)) + 1;

        std::cout << descriptor << " " << sz << "\n";

        if (sz < 9) {
            continue;
        }
    
        sz = (sz + 7) / 8;

        for (int j = 0; j < N; ++j) {
            int combo = 0;
            for (int k = 0; k < N; ++k) {
                if (!mat[j][k]) {
                    ++combo;

                    if (combo == sz) {
                        k = k - sz + 1;

                        for (int l = k; l < k + sz; ++l) {
                            mat[j][l] = descriptor;
                        }

                        ++f[descriptor];
                        --Free;

                        goto foundInterval;
                    }
                } else {
                    combo = 0;
                }
            }
        }

        foundInterval: {}
    }

    return;
}

void GET(int descriptor) {
    for (int i = 0; i < N; ++i) {
        int x = N, y = 0;

        for (int j = 0; j < N; ++j) {
            if (mat[i][j] == descriptor) {
                x = std::min(x, j);
                y = std::max(y, j);
            }
        }

        if (x != N) {
            /// std::cout << "((" << i << ", " << x << "), " << "(" << i << ", " << y << "))\n";
            return;
        }
    }

    /// std::cout << "((0, 0), (0, 0))\n";
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
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] == descriptor) {
                mat[i][j] = 0;
            }
        }
    }

    return;
}

void DEFRAGMENTATION() {
    int px = 0, py = 0, ind = 0, sum = 0;
    cnt = 0;

    for (int i = 0; i < N; ++i) {
        int x = N, y = 0;

        for (int j = 0; j < N; ++j) {
            if (mat[i][j] && mat[i][j + 1] == mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);
            } else if (mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);

                w[cnt++] = y - x + 1;

                x = N, y = 0;
            }
        }
    }

    for (int qx = 0; qx < N; ++qx) {
        for (int qy = 0; qy < N; ++ qy) {
            if (sum + w[ind] > N) {
                ++px;
                py = 0;
                sum = 0;
            }

            if (mat[qx][qy]) {
                if (mat[qx][qy] != mat[qx][qy + 1]) {
                    sum += w[ind];
                    ++ind;
                }

                int x = mat[qx][qy];
                mat[qx][qy] = 0;
                mat[px][py] = x;
                ++ py;
            }
        }
    }

    return;
}

int main(int argc, char* argv[]) {
    std::cout << Q << "\n";

    while (Q --) {
        int type;

        for (int v = 1; v < D; ++v) {
            f[v] = 0;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                f[mat[i][j]] ++;
            }
        }

        Free = 0;

        for (int v = 1; v < D; ++v) {
            if (f[v] == 0) {
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

    std::cout.flush();

    return 0;
}
