////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define FILE_IO(x) freopen((string(x) + ".in").c_str(), "r", stdin); freopen((string(x) + ".out").c_str(), "w", stdout)
#define f first
#define s second
#define x1 x1qwer
#define y1 y1qwer
#define foreach(it, v) for (auto it : v)
#define rep(it, n) for (int it = 0; it < n; ++it)
#define forin(it, l, r) for (int it = l; it < r; ++it)
#define all(x) x.begin(), x.end()

// #define FAST_ALLOCATOR_MEMORY 200000000

#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void * operator new ( size_t n ) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
    return (void *)res;
}
inline void operator delete ( void * ) noexcept { }
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const double DINF = numeric_limits<double>::infinity();
const ll MOD = 1e9 + 7;
const double EpS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll rnd(ll x, ll y) {
    static mt19937 mmtw(time(0));
    static uniform_int_distribution<ll> rd;
    return rd(mmtw) % (y - x + 1) + x;
}

typedef long long ll;

// template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
///////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 3e5 + 5;
const int MAXP = 20;
int n;
vector<int> g[MAXN];

namespace segtree {
    void update(ll *t, int v, int tl, int tr, int l, int r, ll x) {
        if (r <= tl || tr <= l) return;
        if (l <= tl && tr <= r) {
            t[v] += x;
            return;
        }

        int tm = tl + (tr - tl) / 2;
        update(t, v * 2 + 1, tl, tm, l, r, x);
        update(t, v * 2 + 2, tm, tr, l, r, x);
    }

    ll query(ll *t, int v, int tl, int tr, int pos) {
        if (tr - tl == 1) return t[v];

        int tm = tl + (tr - tl) / 2;
        if (pos < tm) {
            return t[v] + query(t, v * 2 + 1, tl, tm, pos);
        } else {
            return t[v] + query(t, v * 2 + 2, tm, tr, pos);
        }
    }
};

namespace lca {
    int up[MAXN][MAXP];
    int tin[MAXN];
    int tout[MAXN];
    int t;

    void buildLca(int v, int p) {
        tin[v] = t++;
        if (p != -1) {
            up[v][0] = p;
        } else {
            up[v][0] = v;
        }
        for (int i = 1; i < MAXP; ++i) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto to : g[v]) {
            if (to == p) continue;
            buildLca(to, v);
        }
        tout[v] = t;
    }

    void prepareLca(int v = 0) {
        t = 0;
        buildLca(v, -1);
    }

    bool isAncestor(int a, int b) {
        return tin[a] <= tin[b] && tin[b] < tout[a];
    }

    int query(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = MAXP - 1; i >= 0; --i) {
            if (!isAncestor(up[a][i], b)) a = up[a][i];
        }
        return up[a][0];
    }
};

namespace hld {
    int sz[MAXN];
    int time;
    int tin[MAXN];
    int tout[MAXN];
    int pathBegin[MAXN];
    ll t[MAXN * 4];

    void rebuildGraph(int v, int p) {
        sz[v] = 1;

        int mx = -1;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (to == p) continue;

            rebuildGraph(to, v);

            sz[v] += sz[to];
            if (mx == -1 || sz[g[v][i]] > sz[g[v][mx]]) {
                mx = i;
            }
        }

        if (mx == -1) return;
        swap(g[v][0], g[v][mx]);
    }

    void buildPaths(int v, int p, int up) {
        tin[v] = time++;
        if (up == -1) up = v;
        pathBegin[v] = up;

        if (!g[v].empty() && g[v][0] != p) buildPaths(g[v][0], v, up);

        for (int i = 1; i < g[v].size(); ++i) {
            if (g[v][i] == p) continue;
            buildPaths(g[v][i], v, -1);
        }
        tout[v] = time;
    }

    void prepareHld(int v = 0) {
        time = 0;
        fill(t, t + MAXN * 4, 0); // bad comlexity !!!
        rebuildGraph(0, -1);
        buildPaths(0, -1, -1);
    }

    void update1(int v, int a, ll val) {
        bool f = false;
        do {
            if (f) {
                a = lca::up[a][0];
            }

            int l = max(tin[pathBegin[a]], tin[v]);
            int r = tin[a];
            if (r < l) continue;
            segtree::update(t, 0, 0, n, l, r + 1, val);
            a = pathBegin[a];

            f = true;
        } while (tin[v] < tin[a]);
    }

    void update(int a, int b, ll val) {
        int v = lca::query(a, b);
        
        segtree::update(t, 0, 0, n, tin[v], tin[v] + 1, -val);
        update1(v, a, val);
        update1(v, b, val);
    }
};

void dfs(int v, int p) {
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p) continue;
        cout << v + 1 << ' ' << to + 1 << ' ' << i + 1 << endl;
        dfs(to, v);
    }
}

int main() {
    FAST_IO;
    cin >> n;
    rep(i, n - 1) {
        int p, q;
        cin >> p >> q;
        g[p - 1].push_back(q - 1);
        g[q - 1].push_back(p - 1);
    }

    hld::prepareHld();
    lca::prepareLca();

    int m;
    cin >> m;
    rep(i, m) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int p, q, val;
            cin >> p >> q >> val;
            hld::update(p - 1, q - 1, val);
        } else {
            int v;
            cin >> v;
            cout << segtree::query(hld::t, 0, 0, n, hld::tin[v - 1]) << '\n';
        }
    }
}
