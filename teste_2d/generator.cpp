#include <bits/stdc++.h>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

const int N = 1024, D = 256;
int Q = 256, Free, mat[N][N + 1], cnt, w[D], f[D];
std::mt19937 rng(1435812);

std::ofstream fout("7.in");

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
    fout << n << "\n";

    for (int i = 0; i < n; ++i) {
        int d, descriptor, sz;

        d = rng() % Free + 1;
        descriptor = getDthElement(d, 1);
        sz = rng() % (8 * (N / 2) - 8) + 9;

        fout << descriptor << " " << sz << "\n";

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
            /// fout << "((" << i << ", " << x << "), " << "(" << i << ", " << y << "))\n";
            return;
        }
    }

    /// fout << "((0, 0), (0, 0))\n";
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

    fout << descriptor << "\n";

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

const int P = 10;

std::string paths[P];

namespace fs = std::filesystem;

void CONCRETE() {
    int r = rng() % P;
    std::string pathFolder = paths[r];

    fout << pathFolder << "\n";

    for (const auto& entry : fs::directory_iterator(pathFolder.c_str())) {
        if (fs::is_regular_file(entry.status())) {
            struct stat fileStat;

            stat(entry.path().c_str(), &fileStat);

            int descriptor = fileStat.st_ino % 255 + 1, sz = fileStat.st_size;
            sz = (sz + 1023) / 1024;

            if (f[descriptor] == false) {
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

                                f[descriptor] = true;

                                goto foundInterval;
                            }
                        } else {
                            combo = 0;
                        }
                    }
                }

                continue;

                foundInterval: {} 
            }
        }
    }
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        paths[i - 1] = argv[i];
    }

    fout << Q << "\n";

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
            type = rng() % 5 + 1;
        } else {
            type = rng() % 4 + 2;
        }

        fout << type << "\n";

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

            fout << descriptor << "\n";

            GET(descriptor);
        }

        if (type == 3) {
            DELETE();
        }

        if (type == 4) {
            DEFRAGMENTATION();
        }

        if (type == 5) {
            CONCRETE();
        }
    }

    return 0;
}
