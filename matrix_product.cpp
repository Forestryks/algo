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

using matrix = vector<vector<ll>>;

matrix matrixProduct(const matrix &, const matrix &);
matrix operator*(const matrix &, const matrix &);
matrix binpow(matrix, ll);
void printMatrix(const matrix &);
ostream& operator<<(ostream &, const matrix &);
istream& operator>>(istream &, matrix &);
void assignMatrix(matrix &, int, int);


matrix operator*(const matrix &a, const matrix &b) {
    return matrixProduct(a, b);
}

matrix matrixProduct(const matrix &m1, const matrix &m2) {
    if (m1.size() == 0 || m2.size() == 0) return {};
    if (m2.size() != m1[0].size()) return {};
    ll n = m1.size();
    ll m = m2[0].size();

    vector<ll> tmp(m, 0);
    matrix res(n, tmp);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m2.size(); ++k) {
                res[i][j] = (res[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
        }
    }

    return res;
}

matrix binpow(matrix a, ll k) {
    if (k == 0) {
        int n = a.size();
        matrix res;
        assignMatrix(res, n, n);
        rep(i, n) {
            res[i][i] = 1;
        }
        return res;
    }
    matrix res = a;
    k--;
    while (k) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

ostream& operator<<(ostream &f, const matrix &a) {
    rep(i, a.size()) {
        if (i != 0) f << "\n";
        rep(j, a[i].size()) {
            f << a[i][j] << " ";
        }
    }
    return f;
}

istream& operator>>(istream &f, matrix &a) {
    rep(i, a.size()) {
        rep(j, a[i].size()) {
            f >> a[i][j];
        }
    }
    return f;
}

void assignMatrix(matrix &a, int n, int m) {
    vector<ll> t(m, 0);
    a.assign(n, t);
}

int p, q, r;

int main() {
    // FILE_IO("mmul");
    matrix a, b;
    cin >> p >> q >> r;
    assignMatrix(a, p, q);
    assignMatrix(b, q, r);
    cin >> a >> b;
    cout << (a * b) << endl;
}
