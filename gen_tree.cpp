#include "testlib.h"
#include <cassert>

namespace tree_gen {

enum TreeType {
    RANDOM,
    BINARY,
    ACACIA,
    HAIRBRUSH,
    STAR,
    ANTI_HLD
};

std::vector<int> __generate_parents(int n, int tree_type, int distr) {
    assert(distr >= -n && distr <= n - 1);
    std::vector<int> p(n);
    p[0] = -1;
    if (tree_type == TreeType::RANDOM) {
        if (distr >= 0) {
            distr = n - distr;
            assert(distr >= 1 && distr <= n);
            for (int i = 1; i < n; ++i) {
                p[i] = rnd.next(std::max(0, i - distr), i - 1);
            }
        } else {
            distr = -distr;
            distr = n - distr;
            assert(distr >= 0 && distr <= n - 1);
            for (int i = 1; i < n; ++i) {
                p[i] = rnd.next(0, std::min(i - 1, distr));
            }
        }
    } else if (tree_type == TreeType::BINARY) {
        for (int i = 1; i < n; ++i) {
            p[i] = (i - 1) / 2;
        }
    } else if (tree_type == TreeType::ACACIA) {
        for (int i = 1; i <= n / 2; ++i) {
            p[i] = i - 1;
        }
        for (int i = n / 2 + 1; i < n; ++i) {
            p[i] = n / 2;
        }
    } else if (tree_type == TreeType::HAIRBRUSH) {
        for (int i = 1; i <= n / 2; ++i) {
            p[i] = i - 1;
        }
        for (int i = n / 2 + 1; i < n; ++i) {
            p[i] = i - (n / 2 + 1);
        }
    } else if (tree_type == TreeType::STAR) {
        for (int i = 1; i < n; ++i) {
            p[i] = 0;
        }
    } else if (tree_type == TreeType::ANTI_HLD) {
        int ptr = 1;
        std::function<void(int, int)> build = [&] (int v, int cnt) {
            if (cnt <= 2) {
                for (int i = 0; i < cnt; i++) {
                    p[ptr++] = v;
                }
                return;
            }
            int x = cnt / 3;
            if (x >= 2) {
                x--;
            }
            int y = cnt - 2 * x;
            for (int i = 0; i < x; i++) {
                p[ptr] = v;
                v = ptr++;
            }
            build(v, x);
            for (int i = 0; i < y; i++) {
                p[ptr] = v;
                v = ptr++;
            }
        };
        build(0, n - 1);
    } else {
        assert(false);
    }
    return p;
}

std::vector<int> __shuffle_graph(std::vector<int> p) {
    int n = p.size();
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin(), perm.end());
    for (int i = 0; i < n; ++i) {
        if (p[i] == -1) continue;
        p[i] = perm[p[i]];
    }
    std::vector<int> np(n);
    for (int i = 0; i < n; ++i) {
        np[perm[i]] = p[i];
    }
    return np;
}

/*
 * n         - number of verticies
 * tree_type - type of tree
 * distr     - [-n .. n-1] (only for tree_type=RANDOM)
                 distr < 0 is likely to generate star
                 distr == 0 will generate random tree
                 distr > 0 is likely to generate bamboo
 * Returns array of verticies parents. Verticies are numbered from zero, root having parent equal -1
 */
std::vector<int> generate(int n, TreeType tree_type, int distr) {
    std::vector<int> p = __generate_parents(n, tree_type, distr);
    p = __shuffle_graph(p);
    return p;
}

} // namespace tree_gen

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    // parse_params(argc, argv);
    // gen();
    auto p = tree_gen::generate(10, tree_gen::TreeType::BINARY, 0);
    for (auto it : p) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
}
