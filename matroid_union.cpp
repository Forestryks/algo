////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
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

// #define FAST_ALLOCATOR_MEMORY 250000000
 
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
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll rnd(ll x, ll y) {
    static mt19937 mmtw(time(0));
    static uniform_int_distribution<ll> rd;
    return rd(mmtw) % (y - x + 1) + x;
}

typedef long long ll;

template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

struct edge {
    int p, q, c;
};

const int MAXN = 105;
const int MAXM = 5005;
int n, m;
vector<edge> e;
vector<int> ans;

vector<int> v1, v2;
vector<int> g[MAXN];
vector<int> g1[MAXM];
vector<int> g2[MAXM];
int gc[MAXN];
bool col[105];
bool S[MAXM];
bool T[MAXM];
int d1[MAXM];
int d2[MAXM];
int p1[MAXM];
int p2[MAXM];
bool del[MAXM];

void dfs(int v, int c) {
    gc[v] = c;
    for (auto to : g[v]) {
        if (gc[to] == -1) {
            dfs(to, c);
        }
    }
}

void buildEdges1(int v) {
    rep(i, n) {
        g[i].clear();
        gc[i] = -1;
    }

    for (int i = 0; i < v1.size(); ++i) {
        if (i == v) continue;
        int p = e[v1[i]].p;
        int q = e[v1[i]].q;
        g[p].push_back(q);
        g[q].push_back(p);
    }

    for (int i = 0; i < n; ++i) {
        if (gc[i] == -1) {
            dfs(i, i);
        }
    }

    for (int to = 0; to < v2.size(); ++to) {
        int p = e[v2[to]].p;
        int q = e[v2[to]].q;
        if (gc[p] != gc[q]) {
            g1[v].push_back(to);
        }
    }
}

void buildEdges2(int v) {
    fill(col, col + 105, 0);
    for (int i = 0; i < v1.size(); ++i) {
        if (i == v) continue;
        col[e[v1[i]].c] = true;
    }

    for (int to = 0; to < v2.size(); ++to) {
        int c = e[v2[to]].c;
        if (col[c] == false) {
            g2[to].push_back(v);
        }
    }
}

void buildS() {
    fill(S, S + v2.size(), false);
    rep(i, n) {
        g[i].clear();
        gc[i] = -1;
    }

    for (int i = 0; i < v1.size(); ++i) {
        int p = e[v1[i]].p;
        int q = e[v1[i]].q;
        g[p].push_back(q);
        g[q].push_back(p);
    }

    for (int i = 0; i < n; ++i) {
        if (gc[i] == -1) {
            dfs(i, i);
        }
    }

    for (int to = 0; to < v2.size(); ++to) {
        int p = e[v2[to]].p;
        int q = e[v2[to]].q;
        if (gc[p] != gc[q]) {
            S[to] = true;
        }
    }
}

void buildT() {
    fill(col, col + 105, 0);
    fill(T, T + v2.size(), false);

    for (int i = 0; i < v1.size(); ++i) {
        col[e[v1[i]].c] = true;
    }

    for (int to = 0; to < v2.size(); ++to) {
        int c = e[v2[to]].c;
        if (col[c] == false) {
            T[to] = true;
        }
    }
}

void buildGraph() {
    v1.clear();
    v2.clear();

    for (auto it : ans) {
        v1.push_back(it);
    }
    for (int i = 0; i < m; ++i) {
        auto it = lower_bound(all(v1), i);
        if (it == v1.end() || (*it) != i) {
            v2.push_back(i);
        }
    }

    rep(i, v1.size()) {
        g1[i].clear();
    }
    rep(i, v2.size()) {
        g2[i].clear();
    }

    for (int i = 0; i < v1.size(); ++i) {
        buildEdges1(i);
    }

    for (int i = 0; i < v1.size(); ++i) {
        buildEdges2(i);
    }

    buildS();
    buildT();

    // cout << endl;
    // for (int i = 0; i < v2.size(); ++i) {
    //     if (S[i]) cout << i << ' ';
    // }
    // cout << endl << endl;

    // for (int i = 0; i < v2.size(); ++i) {
    //     if (T[i]) cout << i << ' ';
    // }
    // cout << endl << endl;

    // for (int i = 0; i < v1.size(); ++i) {
    //     cout << i << " : ";
    //     for (auto to : g1[i]) {
    //         cout << to << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for (int i = 0; i < v2.size(); ++i) {
    //     cout << i << " : ";
    //     for (auto to : g2[i]) {
    //         cout << to << ' ';
    //     }
    //     cout << endl;
    // }
}

bool nextIter() {
    if (ans.size() == m) return false;
    buildGraph();

    fill(d1, d1 + v1.size(), -1);
    fill(d2, d2 + v2.size(), -1);

    queue<int> q;
    rep(i, v2.size()) {
        if (S[i]) {
            q.push(-(i + 1));
            d2[i] = 0;
            p2[i] = -1;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v < 0) {
            v = -v;
            v--;
            for (auto to : g2[v]) {
                if (d1[to] == -1) {
                    q.push(to + 1);
                    d1[to] = d2[v] + 1;
                    p1[to] = v;
                }
            }
        } else {
            v--;
            for (auto to : g1[v]) {
                if (d2[to] == -1) {
                    q.push(-(to + 1));
                    d2[to] = d1[v] + 1;
                    p2[to] = v;
                }
            }
        }
    }

    int v = 0;
    for (int i = 0; i < v2.size(); ++i) {
        if (T[i]) {
            if (!T[v] || d2[v] == -1 || d2[i] < d2[v]) {
                v = i;
            }
        }
    }

    if (!T[v] || d2[v] == -1) {
        return false;
    }

    // rep(i, n) {
    //     cout << d2[i] << ' ';
    // }
    // cout << endl;
    // rep(i, n) {
    //     cout << p2[i] << ' '; 
    // }
    // cout << endl;

    vector<int> nasn;
    fill(del, del + v1.size(), false);
    nasn.push_back(v2[v]);
    while (p2[v] != -1) {
        del[p2[v]] = true;
        v = p1[p2[v]];
        nasn.push_back(v2[v]);
    }
    rep(i, v1.size()) {
        if (!del[i]) {
            nasn.push_back(v1[i]);
        }
    }

    sort(all(nasn));

    ans = nasn;

    return true;
}

int main() {
    FILE_IO("rainbow");
    cin >> n >> m;
    rep(i, m) {
        int p, q, c;
        cin >> p >> q >> c;
        e.push_back({p - 1, q - 1, c});
    }

    while (nextIter()) {}
    // ans = {0, 3, 4};
    // nextIter();
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it + 1 << ' ';
    }
    cout << endl;
}
