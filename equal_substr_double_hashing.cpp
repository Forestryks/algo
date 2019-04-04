////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define FILE_IO(x) freopen((string(x) + ".in").c_str(), "r", stdin); freopen((string(x) + ".out").c_str(), "w", stdout)
#define sz(x) ((int)((x).size()))
#define len(x) ((int)((x).length()))
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
const int INF = (1 << 31) - 1;
const ll LINF = (1ll << 63) - 1;
const double DINF = numeric_limits<double>::infinity();
// const int MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
// mt19937 mmtw(MOD);
// ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T binpow(T n, T k) { if (k == 1) return n; if (k & 1) return binpow(n, k - 1) * n; T a = binpow(n, k / 2); return a * a; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 100005;

int n, q, l1, l2, r1, r2;
const ll B1 = 29;
const ll MD1 = 1073676287;
const ll B2 = 37;
const ll MD2 = 16769023;
char a[MAXN];
ll pows1[MAXN];
ll pows2[MAXN];
ll suf1[MAXN];
ll suf2[MAXN];

int main() {
    FAST_IO;
    // FILE_IO("eqsubstr");
    cin >> a;
    n = strlen(a);

    pows1[1] = B1;
    pows2[1] = B2;

    for (int i = 2; i <= n; ++i) {
        pows1[i] = (pows1[i - 1] * B1) % MD1;
        pows2[i] = (pows2[i - 1] * B2) % MD2;
    }

    for (int i = n - 1; i >= 0; --i) {
        suf1[i] = (a[i] - 'a' + 1 + suf1[i + 1] * B1) % MD1;
        suf2[i] = (a[i] - 'a' + 1 + suf2[i + 1] * B2) % MD2;
    }

    cin >> q;
    rep(i, q) {
        cin >> l1 >> r1 >> l2 >> r2;
        l1--, l2--;
        ll hash1 = (suf1[l1] - (suf1[r1] * pows1[r1 - l1]) % MD1 + MD1) % MD1;
        ll hash2 = (suf1[l2] - (suf1[r2] * pows1[r2 - l2]) % MD1 + MD1) % MD1;

        if (hash1 != hash2) {
            cout << '-';
            continue;
        }

        hash1 = (suf2[l1] - (suf2[r1] * pows2[r1 - l1]) % MD2 + MD2) % MD2;
        hash2 = (suf2[l2] - (suf2[r2] * pows2[r2 - l2]) % MD2 + MD2) % MD2;

        if (hash1 == hash2) {
            cout << '+';
        } else {
            cout << '-';
        }
    }
    cout << endl;
    return 0;
}