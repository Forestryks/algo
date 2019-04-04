////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
#include <bits/stdc++.h>
using namespace std;
 
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
  
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const double DINF = numeric_limits<double>::infinity();
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw(35446464654);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T binpow(T n, T k) { if (k == 1) return n; if (k & 1) return binpow(n, k - 1) * n; T a = binpow(n, k / 2); return a * a; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
long double PI = 3.14159265358979323846;
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 5005;
int dp[MAXN][MAXN];
int f[MAXN][MAXN];
int par[MAXN][MAXN];
int fpar[MAXN][MAXN];
int n, k;
int sz[MAXN];
vector<int> g0[MAXN];
vector<int> g[MAXN];
vector<pii> del;
map<pii, int> id;
int de;

void dfs0(int v, int p) {
    sz[v] = 1;
    for (auto to : g0[v]) {
        if (to == p) continue;
        g[v].push_back(to);
        dfs0(to, v);
        sz[v] += sz[to];
    }
}

void dfs(int v) {
    for (auto to : g[v]) {
        dfs(to);
    }

    int sumsz = 0;
    // for (auto to : g[v]) {
    if (g[v].size()) {
        int to = g[v][0];
        for (int i = 0; i < MAXN; ++i) {
            f[to][i] = dp[to][i];
            fpar[to][i] = i;
        }
        sumsz = sz[to] + 1;
    }
    // }

    for (int t = 1; t < g[v].size(); ++t) {
        int to = g[v][t];
        int prev = g[v][t - 1];
        for (int i = 0; i < sumsz; ++i) {
            for (int j = 0; j < sz[to] + 2; ++j) {
                // f[to][i + j] = min(f[to][i + j], f[prev][i] + dp[to][j]);
                if (f[prev][i] + dp[to][j] < f[to][i + j]) {
                    f[to][i + j] = f[prev][i] + dp[to][j];
                    fpar[to][i + j] = j;
                }
            }
        }
        sumsz += sz[to];
    }

    if (g[v].size()) {
        int last = g[v][g[v].size() - 1];
        for (int i = 1; i + 1 < MAXN; ++i) {
            dp[v][i] = f[last][i - 1];
            par[v][i] = i - 1;
        }
    }
    dp[v][1] = g[v].size();
    par[v][1] = 1000000000;
    dp[v][0] = 1;
}

void dfs1(int v, int k) {
    // cout << ": " << v << ' ' << k << endl;
    if (par[v][k] == 1000000000) {
        for (auto to : g[v]) del.push_back({v, to});
        return;
    }

    k--;
    for (int i = g[v].size() - 1; i >= 0; --i) {
        int to = g[v][i];
        if (fpar[to][k] == 0) del.push_back({v, to});
        else dfs1(to, fpar[to][k]);
        k -=  fpar[to][k];
    }
}

int main() {
    cin >> n >> k;
    rep(i, n - 1) {
        int p, q;
        cin >> p >> q;
        g0[p - 1].push_back(q - 1);
        g0[q - 1].push_back(p - 1);
        id[{p - 1, q - 1}] = i + 1;
        id[{q - 1, p - 1}] = i + 1;
    }

    dfs0(0, -1);

    rep(i, MAXN) {
        rep(j, MAXN) {
            dp[i][j] = 1000000000;
            f[i][j] = 1000000000;
        }
    }

    dfs(0);

    // rep(i, n) {
    //     cout << "dp[" << i << "] = [";
    //     rep(j, k + 1) {
    //         if (j != 0) cout << ", ";
    //         cout << dp[i][j];
    //     }
    //     cout << "]" << endl;
    // }

    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (best == 0) {
            if (dp[i][k] + 1 < dp[best][k]) best = i;
        } else {
            if (dp[i][k] + 1 < dp[best][k] + 1) best = i;
        }
    }

    dfs1(best, k);
    if (best != 0) {
        rep(v, n) {
            for (auto to : g[v]) {
                if (to == best) del.push_back({v, to});
            }
        }
    }

    // if (del.size() != dp[best][k] + (best != 0)) while(true) {};
    // cout << dp[best][k] + (best != 0) << endl;
    cout << del.size() << endl;
    for (auto it : del) {
        cout << id[it] << ' ';
    } cout << endl;
}
