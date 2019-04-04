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

#define int long long
#define PW2 8
#define SIZE 250

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

struct node {
    ll val;
    map<int, bool> sign;
    node(ll a, int pos) {
        val = a;
        sign[pos] = true;
    }
    ~node() {
        sign.clear();
    }
};

bool cmp(const node *a, const node *b) {
    return a->val < b->val;
}

ll p, q;
node *a[SIZE + 5];

void printAnswer() {
    string s1(SIZE, 'a');
    string s2 = s1;
    for (auto it : a[0]->sign) {
        if (it.s) {
            s1[it.f]++;
        } else {
            s2[it.f]++;
        }
    }
    reverse(all(s1));
    reverse(all(s2));
    cout << s1 << endl << s2 << endl;

    ll h1 = 0, h2 = 0;
    for (int i = 0; i < SIZE; ++i) {
        h1 += s1[i];
        h1 = binmul(h1, p, q);
    }

    for (int i = 0; i < SIZE; ++i) {
        h2 += s2[i];
        h2 = binmul(h2, p, q);
    }

    cout << h1 << endl << h2 << endl;
    return;
}

void solve() {
    while(true) {
        int size = SIZE;
        sort(a, a + size, cmp);

        // for (int i = 0; i < size; ++i) {
        //     cout << a[i]->val << " ";
        // } cout << endl;

        if (a[0]->val == 0) {
            printAnswer();
            return;
        }
        if (size == 1) {
            cout << "No answer" << endl;
            exit(1);
        }

        for (int i = 0; i < size - 1; i += 2) {
            for (auto it : a[i]->sign) {
                a[i + 1]->sign[it.f] = it.s ^ 1;
            }
            a[i / 2]->sign.clear();
            for (auto it : a[i + 1]->sign) {
                a[i / 2]->sign[it.f] = it.s;
            }
            a[i / 2]->val = a[i + 1]->val - a[i]->val;
        }

        if (size & 1) {
            a[size / 2]->sign.clear();
            for (auto it : a[size - 1]->sign) {
                a[size / 2]->sign[it.f] = it.s;
            }
            a[size / 2]->val = a[size - 1]->val;
            size = size / 2 + 1;
        } else {
            size = size / 2;
        }
    }
}

signed main() {
    FAST_IO;
    // FILE_IO("breaking-hashing");
    cin >> p >> q;
    ll hash = 1;

    // for (int i = 0; i < 65536; ++i) {
    for (int i = 0; i < SIZE; ++i) {
        // cout << hash << endl;
        a[i] = new node(hash, i);
        hash = binmul(hash, p, q);
    }
    solve();

    return 0;
}
