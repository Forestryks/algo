///////////////////////////////////////////////////////////////////////////////////////////////
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
#define right right123
#define left left123
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
uniform_int_distribution<int> rdi_;
ll randomll() { return rd_(mmtw_);}
int randto(int x) {return rdi_(mmtw_) % x;}
ll rnd(ll x, ll y) { return rd_(mmtw_) % (y - x + 1) + x; }
////////////////////////////////////////////////////////////////////////////////////////////////

const ll mod = 1e9 + 7;

ll mpow(ll a, ll p) {
    ll r = 1;
    while (p) {
        if (p & 1) {
            r *= a;
            r %= mod;
        }

        a *= a;
        a %= mod;
        p >>= 1;
    }
    return r;
}

ll minv(ll a) {
    return mpow(a, mod - 2);
}

ll mdiv(ll a, ll b) {
    return (a * minv(b)) % mod;
}

vector<ll> modgauss(vector<vector<ll>> a, vector<ll> b) {
    if (a.size() != b.size() || a.size() == 0) return {};
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (a[i].size() != n) return {};
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (a[j][i] != 0) {
                swap(a[i], a[j]);
                break;
            }
        }

        if (a[i][i] == 0) continue;

        ll ai = minv(a[i][i]);
        // cout << i << ' ' << ai << endl;
        for (int j = i; j < n; ++j) {
            a[i][j] = (a[i][j] * ai) % mod;
        }
        b[i] = (b[i] * ai) % mod;

        for (int j = i + 1; j < n; ++j) {
            b[j] = ((b[j] - (b[i] * a[j][i])) % mod + mod) % mod;
            for (int k = n - 1; k >= i; --k) {
                a[j][k] = ((a[j][k] - (a[i][k] * a[j][i])) % mod + mod) % mod;
            }
        }
    }

    vector<ll> res(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            b[i] = ((b[i] - a[i][j] * res[j]) % mod + mod) % mod;
        }
        if (a[i][i] == 0 && b[i] != 0) return {INT_MIN};
        if (a[i][i] == 0 && b[i] == 0) return {INT_MAX};
        if (b[i] == 0) res[i] = 0;
        else {
            res[i] = mdiv(b[i], a[i][i]);
        }
    }

    return res;
}

int main() {
    int n;
    cin >> n;
    vector<vector<ll>> a(n);
    vector<ll> b(n);

    rep(i, n) {
        a[i].resize(n);
        rep(j, n) {
            cin >> a[i][j];
        }
        cin >> b[i];
    }

    auto res = modgauss(a, b); 
    for (auto it : res) {
        cout << it << ' ' ;
    }
    cout << endl;
}