////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
// #pragma GCC optimize("Ofast")
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
const ll MOD = 1e9 + 7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
string mtos(int mask, int bits = 5, bool inv = false) 
{ string s; rep(i, bits) { s += '0' + ((mask >> i) & 1); } if (!inv) reverse(all(s)); return s; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
ld PI = 3.141592653589793238462643383279;
///////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 1e5 + 5;
const int MAXP = 20;
const int BLOCK = 300;

int n, m;
int last;
int a[MAXN * 2];
int height[MAXN];
int log_[MAXN * 2];
int first[MAXN * 2];
int st[MAXN * 2][19];
int d[MAXN];
vector<int> g[MAXN];
vector<int> tmp;
bool used[MAXN];

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

int dist(int u, int v) {
    int lc = lca(u, v);
    return height[u] + height[v] - 2 * height[lc];
}

void update(int v) {
    v--;
    tmp.push_back(v);
    if (tmp.size() >= BLOCK) {
        fill(used, used + n, false);
        queue<pii> q;
        while (tmp.size()) {
            q.push({0, tmp.back()});
            used[tmp.back()] = true;
            d[tmp.back()] = 0;
            tmp.pop_back();
        }

        while (!q.empty()) {
            int dst = q.front().f;
            int v = q.front().s;
            q.pop();
            for (auto to : g[v]) {
                if (used[to]) continue;
                used[to] = true;
                d[to] = min(dst + 1, d[to]);
                q.push({d[to], to});
            }
        }
    }
}

int query(int v) {
    v--;
    int dst = d[v];
    for (auto to : tmp) {
        dst = min(dst, dist(v, to));
    }
    return dst;
}

int main() {
    FAST_IO;
    cin >> n >> m;
    rep(i, n - 1) {
        int p, q;
        cin >> p >> q;
        g[p - 1].push_back(q - 1);
        g[q - 1].push_back(p - 1);
    }

    fill(d, d + n, 10000000);

    preCountLogs();
    dfs(0, 0);
    buildSparseTable();

    update(1);

    rep(qwe, m) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            update(v);
        } else {
            cout << query(v) << '\n';
        }
    }
}
