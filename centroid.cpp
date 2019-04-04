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
const ll MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
string mtos(int mask, int bits = 5, bool inv = false) 
{ string s; rep(i, bits) { s += '0' + ((mask >> i) & 1); } if (!inv) reverse(all(s)); return s; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
ld PI = 3.141592653589793238462643383279;
///////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 2e5 + 5;

int n;
vector<int> g[MAXN];
int p[MAXN];
bool used[MAXN];
int sz[MAXN];

int dfs1(int v, int par = -1) {
    sz[v] = 1;
    for (auto to : g[v]) {
        if (!used[to] && to != par) {
            sz[v] += dfs1(to, v);
        }
    }
    return sz[v];
}

int getCentroid(int v, int size, int par = -1) {
    int mx = -1;
    for (auto to : g[v]) {
        if (to == par || used[to]) continue;
        if (sz[to] * 2 > size && to != par) {
            mx = to;
        }
    }
    if (mx == -1) {
        return v;
    } else {
        return getCentroid(mx, size, v);
    }
}

void build(int v, int par = -1) {
    int size = dfs1(v);
    int c = getCentroid(v, size);
    used[c] = true;
    p[c] = par;
    for (auto to : g[c]) {
        if (!used[to]) {
            build(to, c);
        }
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

    build(0);

    rep(i, n) {
        cout << p[i] + 1 << ' ';
    } cout << endl;
}
