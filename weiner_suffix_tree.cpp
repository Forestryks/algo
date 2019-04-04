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
 
#define FAST_ALLOCATOR_MEMORY 250000000
  
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

namespace weiner {
    const int MAXN = 2e5 + 5;

    int sz;
    string s;
    int pos[MAXN], len[MAXN], par[MAXN];
    map<char, int> to[MAXN], link[MAXN];
    int path[MAXN];
    int ptr;

    void init() {
        sz = 2;
        pos[1] = 0; len[1] = 1; par[1] = 0;
        for (int i = 0; i < 256; ++i) {
            link[0][i] = 1;
        }
    }

    void attach(int child, int parent, char ch, int length) {
        par[child] = parent;
        to[parent][ch] = child;
        len[child] = length;
    }

    int extend(int i) {
        int vlen = s.size() - i, old = sz - 1, ptr = 0, v;
        for (v = old; !link[v].count(s[i]); v = par[v]) {
            vlen -= len[v];
            path[ptr++] = v;
        }
        int w = link[v][s[i]];

        if (to[w].count(s[i + vlen])) {
            int u = to[w][s[i + vlen]];
            for (pos[sz] = pos[u] - len[u]; s[pos[sz]] == s[i + vlen]; pos[sz] += len[v]) {
                v = path[--ptr];
                vlen += len[v];
            }

            attach(sz, w, s[pos[u] - len[u]], len[u] - (pos[u] - pos[sz]));
            attach(u, sz, s[pos[sz]], pos[u] - pos[sz]);
            w = link[v][s[i]] = sz++;
        }

        link[old][s[i]] = sz;
        attach(sz, w, s[i + vlen], s.size() - (i + vlen));
        pos[sz++] = s.size();
        return len[sz - 1];
    }
};

int main() {
    FAST_IO;
    cin >> weiner::s;
    int n = weiner::s.size();
    reverse(all(weiner::s));

    weiner::init();
    ll res = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += weiner::extend(i);
        cout << res << '\n';
    }
}