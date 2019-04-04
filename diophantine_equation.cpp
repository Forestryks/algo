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
template <class T> T binpow(T n, T k) { if (k == 1) return n; if (k & 1) return binpow(n, k - 1) * n; T a = binpow(n, k / 2); return a * a; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

ll gcdex(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    ll x1, y1;
    ll g = gcdex(b % a, a, x1, y1);
    y = x1;
    x = y1 - b / a * x1;
    return g;
}

pair<ll, ll> solveDiofant(ll a, ll b, ll c) {
    ll x, y;
    ll g = gcdex(a, b, x, y);
    if (c % g != 0) {
        cout << "Impossible" << endl;
        exit(0);
    } else {
        x *= (c / g);
        y *= (c / g);

        if (x < 0) {
            ll q = (-x) / (b / g);
            x += q * (b / g);
            y -= q * (a / g);
            if (x < 0) {
                x += (b / g);
                y -= (a / g);
            }
        }

        ll q = x / (b / g);
        x -= q * (b / g);
        y += q * (a / g);

        return mp(x, y);
    }
}

ll a, b, c;

int main() {
    // FILE_IO("dioph");
    cin >> a >> b >> c;
    auto ans = solveDiofant(a, b, c);
    cout << ans.f << " " << ans.s << endl;
}