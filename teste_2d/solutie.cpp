#include <bits/stdc++.h>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

const int N = 1024, D = 256;
int Q, mat[N][N + 1], cnt, w[D], f[D];

std::ifstream fin("7.in");
std::ofstream fout("7.ok");

void ADD() {
    int n;
    fin >> n;

    for (int i = 0; i < n; ++i) {
        int descriptor, sz;
        fin >> descriptor >> sz;

        sz = (sz + 7) / 8;

        for (int j = 0; j < N; ++j) {
            int combo = 0;
            for (int k = 0; k < N; ++k) {
                if (!mat[j][k]) {
                    ++combo;

                    if (combo == sz) {
                        k = k - sz + 1;
                        fout << descriptor << ": ";
                        fout << "((" << j << ", " << k << "), " << "(" << j << ", " << k + sz - 1 << "))\n";

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

        fout << descriptor << ": " << "((0, 0), (0, 0))\n";
        continue;

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
            fout << "((" << i << ", " << x << "), " << "(" << i << ", " << y << "))\n";
            return;
        }
    }

    fout << "((0, 0), (0, 0))\n";
    return;
}

void DELETE() {
    int descriptor;
    fin >> descriptor;
    f[descriptor] = false;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mat[i][j] == descriptor) {
                mat[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        int x = N, y = 0;

        for (int j = 0; j < N; ++j) {
            if (mat[i][j] && mat[i][j + 1] == mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);
            } else if (mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);

                fout << mat[i][j] << ": " << "((" << i << ", " << x << "), " << "(" << i << ", " << y << "))\n";

                x = N, y = 0;
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
            if (ind == cnt) {
                goto doneDefrag;
            }

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
                ++py;
            }
        }
    }

    doneDefrag: {}

    for (int i = 0; i < N; ++i) {
        int x = N, y = 0;

        for (int j = 0; j < N; ++j) {
            if (mat[i][j] && mat[i][j + 1] == mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);
            } else if (mat[i][j]) {
                x = std::min(x, j);
                y = std::max(y, j);

                fout << mat[i][j] << ": " << "((" << i << ", " << x << "), " << "(" << i << ", " << y << "))\n";

                x = N, y = 0;
            }
        }
    }

    return;
}

namespace fs = std::filesystem;

void CONCRETE() {
    std::string pathFolder;
    
    fin >> pathFolder;

    for (const auto& entry : fs::directory_iterator(pathFolder.c_str())) {
        if (fs::is_regular_file(entry.status())) {
            struct stat fileStat;

            stat(entry.path().c_str(), &fileStat);

            int descriptor = fileStat.st_ino % 255 + 1, sz = fileStat.st_size;
            sz = (sz + 1023) / 1024;

            if (f[descriptor] == true) {
                fout << descriptor << ": " << "((0, 0), (0, 0))\n";
            } else {
                sz = (sz + 7) / 8;

                for (int j = 0; j < N; ++j) {
                    int combo = 0;
                    for (int k = 0; k < N; ++k) {
                        if (!mat[j][k]) {
                            ++combo;

                            if (combo == sz) {
                                k = k - sz + 1;
                                fout << descriptor << ": ";
                                fout << "((" << j << ", " << k << "), " << "(" << j << ", " << k + sz - 1 << "))\n";

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

                fout << descriptor << ": " << "((0, 0), (0, 0))\n";
                continue;

                foundInterval: {} 
            }
        }
    }
    
    return;
}

int main() {
    fin >> Q;

    while (Q --) {
        int type;

        fin >> type;

        if (type == 1) {
            ADD();
        }

        if (type == 2) {
            int descriptor;
            fin >> descriptor;
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
