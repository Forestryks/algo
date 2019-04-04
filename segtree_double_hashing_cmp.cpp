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

const int MAXN = 4e5 + 5;

ll mod[2] = {928466111, 1001230517};
ll st[2] = {131, 111119};
ll pw_sum[MAXN][2];
ll pw[MAXN][2];

struct Hash {
    ll val[2];
    int sz;
    Hash() {
        val[0] = val[1] = 0;
        sz = 0;
    }
    Hash(int len, int a) {
        sz = len;
        val[0] = (pw_sum[len - 1][0] * a) % mod[0];
        val[1] = (pw_sum[len - 1][1] * a) % mod[1];
    }

    Hash operator()(int len, int a) {
        Hash res(len, a);
        return res;
    }
};

Hash operator+(const Hash &a, const Hash &b) {
    Hash res;
    res.sz = a.sz + b.sz;
    res.val[0] = (a.val[0] + (b.val[0] * pw[a.sz][0])) % mod[0];
    res.val[1] = (a.val[1] + (b.val[1] * pw[a.sz][1])) % mod[1];
    return res;
}

bool operator==(const Hash &a, const Hash &b) {
    return (a.sz == b.sz && a.val[0] == b.val[0] && a.val[1] == b.val[1]);
}

void prepareHash() {
    pw[0][0] = pw[0][1] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pw[i][0] = (pw[i - 1][0] * st[0]) % mod[0];
        pw[i][1] = (pw[i - 1][1] * st[1]) % mod[1];
    }

    pw_sum[0][0] = pw_sum[0][1] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pw_sum[i][0] = (pw_sum[i - 1][0] + pw[i][0]) % mod[0];
        pw_sum[i][1] = (pw_sum[i - 1][1] + pw[i][1]) % mod[1];
    }
}

int c[MAXN * 4];
Hash t[MAXN * 4];
int a[MAXN];
int n, m;

void push(int v, int tl, int tr) {
    if (tr <= tl) {
        return;
    }

    if (c[v]) {
        t[v] = Hash(tr - tl, c[v]);
        c[v * 2 + 1] = c[v];
        c[v * 2 + 2] = c[v];
        c[v] = 0;
    }
}

void build(int v, int tl, int tr) {
    if (tr <= tl) return;
    if (tr - tl == 1) {
        t[v] = Hash(1, a[tl]);
        // cout << a[tl] << endl;
        // cout << ":" << t[v].val[0] << ' ' << t[v].val[1] << endl;
        return;
    }
    int tm = tl + (tr - tl) / 2;
    build(v * 2 + 1, tl, tm);
    build(v * 2 + 2, tm, tr);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

void update(int v, int tl, int tr, int l, int r, ll val) {
    push(v, tl, tr);
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) {
        c[v] = val;
        push(v, tl, tr);
        return;
    }
    int tm = tl + (tr - tl) / 2;

    update(v * 2 + 1, tl, tm, l, r, val);
    update(v * 2 + 2, tm, tr, l, r, val);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    return;
}

Hash query(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (r <= tl || tr <= l) return Hash();
    if (l <= tl && tr <= r) {
        return t[v];
    }
    int tm = tl + (tr - tl) / 2;

    Hash a = query(v * 2 + 1, tl, tm, l, r);
    Hash b = query(v * 2 + 2, tm, tr, l, r);
    return a + b;
}

signed main() {
    prepareHash();
    FAST_IO;
    cin >> n;
    rep(i, n) {
        cin >> a[i];
    }
    build(0, 0, n);
    // rep(i, n * 4) {
    //     cout << t[i].val[0] << ' ' << t[i].val[1] << endl;
    // }

    cin >> m;
    rep(i, m) {
        int q, l, r, k;
        cin >> q >> l >> r >> k;
        if (q == 0) {
            update(0, 0, n, l - 1, r, k);
        } else {
            auto a = query(0, 0, n, l - 1, l - 1 + k);
            auto b = query(0, 0, n, r - 1, r - 1 + k);
            if (a == b) {
                cout << "+";
            } else {
                cout << "-";
            }
            // cout << ':' << a.val[0] << ' ' << b.val[0] << endl;
            // cout << ':' << a.val[1] << ' ' << b.val[1] << endl;
        }

        // rep(i, n * 4) {
        //     cout << t[i].val[0] << ' ' << t[i].val[1] << endl;
        // }
    }
    cout << endl;
}
