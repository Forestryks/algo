////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define FILE_IO(x) freopen((string(x) + ".in").c_str(), "r", stdin); freopen((string(x) + ".out").c_str(), "w", stdout)
#define sz(x) ((int)((x).size()))
#define len(x) ((int)((x).length()))
#define f first
#define s second
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
const int MAXP = 20;

int n;
int last;
int a[MAXN * 2];
int height[MAXN];
int log_[MAXN * 2];
int first[MAXN * 2];
int st[MAXN * 2][19];
vector<int> g[MAXN];

void preCountLogs() {
    log_[1] = 0;
    for (int i = 2; i < MAXN * 2; ++i) {
        log_[i] = log_[i >> 1] + 1;
    }
}

void dfs(int v, int h, int p = -1) {
    height[v] = h;
    first[v] = last;
    a[last++] = v;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, h + 1, v);
        a[last++] = v;
    }
}

void buildSparseTable() {
    int pow = log_[last];
    for (int i = 0; i < last; ++i) {
        st[i][0] = a[i];
    }
    for (int j = 1; j <= pow; ++j) {
        for (int i = 0; i + (1 << j) < last; ++i) {
            if (height[st[i][j - 1]] < height[st[i + (1 << (j - 1))][j - 1]]) {
                st[i][j] = st[i][j - 1];
            } else {
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int querrySparseTable(int left, int right) {
    int pow = log_[right - left + 1];
    int leftPart = st[left][pow];
    int rightPart = st[right - (1 << pow) + 1][pow];
    if (height[leftPart] < height[rightPart]) {
        return leftPart;
    } else {
        return rightPart;
    }
}

int lca(int u, int v) {
    u = first[u];
    v = first[v];
    if (u > v) swap(u, v);
    return querrySparseTable(u, v);
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

    preCountLogs();
    dfs(0, 0);
    buildSparseTable();

    rep(i, n) {
        int p, q;
        cin >> p >> q;
        cout << lca(p - 1, q - 1) + 1 << endl;
    }
}
