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

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const double DINF = numeric_limits<double>::infinity();
const ll MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

#define int long long

const int MAXN = 1e5 + 5;
ll c[MAXN];
ll t[MAXN];
int n, m;

void push(int v, int tl, int tr) {
    t[v] += c[v] * max((tr - tl), 0LL);
    c[v * 2 + 1] += c[v];
    c[v * 2 + 2] += c[v];
    c[v] = 0;
}

ll update(int v, int tl, int tr, int l, int r, ll val) {
    push(v, tl, tr);
    if (r <= tl || tr <= l) return t[v];
    if (l <= tl && tr <= r) {
        c[v] += val;
        push(v, tl, tr);
        return t[v];
    }
    int tm = tl + (tr - tl) / 2;

    ll a = update(v * 2 + 1, tl, tm, l, r, val);
    ll b = update(v * 2 + 2, tm, tr, l, r, val);
    t[v] = a + b;
    return t[v];
}

ll query(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (r <= tl || tr <= l) return 0;
    if (l <= tl && tr <= r) {
        return t[v];
    }
    int tm = tl + (tr - tl) / 2;

    ll a = query(v * 2 + 1, tl, tm, l, r);
    ll b = query(v * 2 + 2, tm, tr, l, r);
    return a + b;
}

signed main() {
    FAST_IO;
    cin >> n >> m;
    rep(i, m) {
        int q;
        cin >> q;
        if (q == 1) {
            int l, r, s;
            cin >> l >> r >> s;
            update(0, 0, n, l, r, s);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n, l, r) << '\n';
        }
    }
}
