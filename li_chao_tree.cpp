////////////////////////////////////////////////////////////////////////////////////////////////
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
mt19937 mmtw_(MOD);
uniform_int_distribution<ll> rd_;
ll randomll() { return rd_(mmtw_);}
ll rnd(ll x, ll y) { return rd_(mmtw_) % (y - x + 1) + x; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

const ll INF = 3e18;

struct line {
    ll k, b;
    ll get(ll x) {
        return k * x + b;
    }
    line() {
        k = 0;
        b = INF;
    }
    line(ll k, ll b) {
        this->k = k;
        this->b = b;
    }
};

struct node : public line {
    node *l, *r;
    node() {
        l = r = nullptr;
    }
};

node *update(node *v, ll tl, ll tr, line nw) {
    if (v == nullptr) v = new node();

    ll tm = tl + (tr - tl) / 2;
    bool lef = nw.get(tl) < v->get(tl);
    bool mid = nw.get(tm) < v->get(tm);

    if (mid) {
        swap(v->k, nw.k);
        swap(v->b, nw.b);
    }

    if (tr - tl == 1) {
        return v;
    } else if (lef != mid) {
        v->l = update(v->l, tl, tm, nw);
    } else {
        v->r = update(v->r, tm, tr, nw);
    }
    return v;
}

ll query(node *v, ll tl, ll tr, ll x) {
    if (v == nullptr) return INF;

    ll tm = tl + (tr - tl) / 2;

    if (tr - tl == 1) {
        return v->get(x);
    } else if (x < tm) {
        return min(v->get(x), query(v->l, tl, tm, x));
    } else {
        return min(v->get(x), query(v->r, tm, tr, x));
    }
}

const int MAXN = 1e5 + 5;
const int MAXV = 1e9 + 5;
int n;
ll a[MAXN];
ll b[MAXN];
ll dp[MAXN];
node *root;

int main() {
    FAST_IO;
    cin >> n;
    rep(i, n) {
        cin >> a[i];
    }
    rep(i, n) {
        cin >> b[i];
    }

    dp[0] = 0;
    root = update(root, 0, MAXV, {b[0], 0});

    for (int i = 1; i < n; ++i) {
        dp[i] = query(root, 0, MAXV, a[i]);
        root = update(root, 0, MAXV, {b[i], dp[i]});
    }

    cout << dp[n - 1] << endl;
}
