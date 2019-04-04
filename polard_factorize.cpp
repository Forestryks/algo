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

ll binmul(ll a, ll b, ll mod) {
    if (b == 0 || a == 0) {
        return 0;
    }
    ll res = a;
    b--;
    while (b) {
        if (b & 1) {
            res = (res + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll binpow(ll n, ll k, ll mod) {
    ll res = 1;
    while (k) {
        if (k & 1) {
            res = binmul(res, n, mod);
        }
        n = binmul(n, n, mod);
        k >>= 1;
    }
    return res;
}

bool millerRabin(ll n) {
    if (n % 2 == 0 || n <= 3) {
        return (n == 2) || (n == 3);
    }

    ll d = n - 1, s = 0;
    while (!(d & 1)) {
        d = d >> 1;
        s++;
    }

    for (int test = 0; test < 100; ++test) {
        ll a = rnd(2LL, n - 2);
        ll x = binpow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool flag = false;
        for (int i = 0; i < s - 1; ++i) {
            x = binmul(x, x, n);
            if (x == 1) {
                return false;
            }
            else if (x == n - 1) {
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        return false;
    }
    return true;
}

void upd(ll &a, ll n) {
    a = binmul(a, a, n) - 1;
    if (a == -1) a = n - 1;
}

ll polard(ll n) {
    if (n % 2 == 0) return 2;
    ll a = rnd(1, n - 2), q = 1;
    ll b = a;

    for (int i = 1; q == 1; ++i) {
        if (!(i & 1)) {
            upd(b, n);
        }
        upd(a, n);

        q = gcd(n, abs(a - b));
    }
    if (millerRabin(q)) {
        return q;
    } else {
        return polard(q);
    }
}

int main() {
    // FILE_IO("factor");
    ll n;
    cin >> n;
    if (n == 1) {
        cout << "1 1" << endl;
        return 0;
    }
    ll a = polard(n);
    ll b = n / a;
    cout << min(a, b) << " " << max(a, b) << endl; 
}
