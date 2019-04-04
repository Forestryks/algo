////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0)
#define FILE_IO(x) freopen((string(x) + ".in").c_str(), "r", stdin); freopen((string(x) + ".out").c_str(), "w", stdout)
#define sz(x) ((int)((x).size()))
#define len(x) ((int)((x).length()))
#define x first
#define y second
#define foreach(it, v) for (auto it : v)
#define rep(it, n) for (int it = 0; it < n; ++it)
#define forin(it, l, r) for (int it = l; it < r; ++it)
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = (1 << 31) - 1;
const ll LINF = (1ll << 63) - 1;
const double DINF = numeric_limits<double>::infinity();
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T binpow(T n, T k) { if (k == 1) return n; if (k & 1) return binpow(n, k - 1) * n; T a = binpow(n, k / 2); return a * a; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 1e5 + 5;

int p[MAXN];
int tin[MAXN];
int tout[MAXN];
int n, m, u, v, t, r;
queue <int> g[MAXN];

void dfs(int v) {
    tin[v] = t++;
    while (!g[v].empty()) {
        dfs(g[v].front());
        g[v].pop();
    }
    tout[v] = t++;
}

bool is_anc(int u, int v) {
    return (tin[u] < tin[v] && tout[u] > tout[v]);
}

int main() {
    FILE_IO("ancestor");
    FAST_IO;
    cin >> n;
    rep(i, n) {
        cin >> v;
        if (v == 0) {
            p[i] = i;
            r = i;
        } else {
            p[i] = v - 1;
            g[v - 1].push(i);
        }
    }

    dfs(r);

    cin >> m;
    rep(i, m) {
        cin >> v >> u;
        cout << int(is_anc(v - 1, u - 1)) << "\n";
    }
    return 0;
}