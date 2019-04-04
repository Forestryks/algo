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

ll n;
ll a, b, c, m;

ll get(ll i) {
    return (((a * i) % m) * i + b * i + c) % m;
}

ll dfs(ll d, ll pos, ll a, ll b, bool maximize) {
    if (d == n) {
        return get(pos);
    }

    if (maximize) {
        ll r1 = dfs(d + 1, pos, a, b, false);
        if (r1 >= b) return b;
        ll r2 = dfs(d + 1, pos + (1 << (n - d - 1)), max(a, r1), b, false);
        return max(r1, r2);
    } else {
        ll r1 = dfs(d + 1, pos, a, b, true);
        if (r1 <= a) return a;
        ll r2 = dfs(d + 1, pos + (1 << (n - d - 1)), a, min(r1, b), true);
        return min(r1, r2);
    }
}

int main() {
    FAST_IO;
    cin >> n >> a >> b >> c >> m;
    cout << dfs(0, 0, INT64_MIN, INT64_MAX, true) << endl;
}