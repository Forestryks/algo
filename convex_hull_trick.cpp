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

struct line {
    ll k, b;
};

vector<line> cht;
int ptr = 0;

/*
k1*x+b1 = k2*x+b2
x*(k1-k2) = b2-b1
x=(b2-b1)/(k1-k2)


(b2-b1)/(k1-k2)>(b3-b1)/(k1-k3)
(b2-b1)*(k1-k3)>(b3-b1)*(k1-k2)
*/

bool bad(ll k1, ll b1, ll k2, ll b2, ll k3, ll b3) {
    return 1.0 * (b2 - b1) * (k1 - k3) > 1.0 * (b3 - b1) * (k1 - k2);
}

void add(ll k, ll b) {
    int sz = cht.size();
    while (sz >= 2 && bad(cht[sz - 2].k, cht[sz - 2].b, cht[sz - 1].k, cht[sz - 1].b, k, b)) {
        sz--;
        cht.pop_back();
    }
    cht.push_back({k, b});
}

ll query(ll x) {
    ptr = min(ptr, ((int)cht.size() - 1));
    while (ptr + 1 < cht.size() && cht[ptr + 1].k * x + cht[ptr + 1].b <= cht[ptr].k * x + cht[ptr].b) {
        ptr++;
    }
    return cht[ptr].k * x + cht[ptr].b;
}

const int MAXN = 1e5 + 5;

int n;
ll a[MAXN];
ll b[MAXN];
ll dp[MAXN];

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
    add(b[0], 0);

    for (int i = 1; i < n; ++i) {
        dp[i] = query(a[i]);
        add(b[i], dp[i]);
    }

    cout << dp[n - 1] << endl;
}