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

const int MAXN = 1e6 + 5;
int n;
vector<int> g[MAXN];
int c[MAXN];
int last[MAXN];
int dsuParent[MAXN];
int dsuTop[MAXN];
int sz[MAXN];
int val[MAXN];
int ans[MAXN];

int getDsu(int v) {
    if (v == dsuParent[v]) return v;
    return dsuParent[v] = getDsu(dsuParent[v]);
}

void mergeDsu(int a, int b, int top) {
    a = getDsu(a);
    b = getDsu(b);
    if (sz[a] > sz[b]) {
        dsuParent[b] = a;
        dsuTop[a] = top;
        sz[a] += sz[b];
    } else {
        dsuParent[a] = b;
        dsuTop[b] = top;
        sz[b] += sz[a];
    }
}

void dfs1(int v) {
    dsuParent[v] = v;
    sz[v] = 1;
    for (auto to : g[v]) {
        dfs1(to);
        mergeDsu(v, to, v);
    }
    if (last[c[v]] != -1) {
        val[dsuTop[getDsu(last[c[v]])]]--;
    }
    val[v]++;
    last[c[v]] = v;
}

int dfs2(int v) {
    int sum = val[v];
    for (auto to : g[v]) {
        sum += dfs2(to);
    }
    ans[v] = sum;
    return sum;
}

int main() {
    FAST_IO;
    cin >> n;    
    rep(i, n) {
        int p, cc;
        cin >> p >> cc;
        g[p].push_back(i + 1);
        c[i + 1] = cc;
    }

    rep(i, MAXN) {
        last[i] = -1;
    }

    dfs1(g[0][0]);
    dfs2(g[0][0]);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    } cout << endl;
}
