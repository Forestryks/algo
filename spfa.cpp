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

const int MAXN = 25005;
int n, m, k;
vector<pair<int, int>> g[MAXN];
int d[MAXN];
bool used[MAXN];

void spfa(int s) {
    fill(used, used + n, false);
    fill(d, d + n, INT_MAX);
    deque<int> q;

    d[s] = 0;
    q.push_back(s);
    used[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        used[v] = false;
        if (d[v] == INT_MAX) continue;

        for (auto it : g[v]) {
            int to = it.f;
            int w = it.s;
            if (d[v] + w < d[to]) {
                d[to] = d[v] + w;
                if (!used[to]) {
                    if (!q.empty() && d[q.front()] > d[to]) {
                        q.push_front(to);
                    } else {
                        q.push_back(to);
                    }
                    used[to] = true;
                }
            }
        }
    }
}

int main() {
    FAST_IO;
    cin >> n >> m;
    rep(i, m) {
        int p, q, w;
        cin >> p >> q >> w;
        g[p - 1].push_back({q - 1, w});
    }

    rep(i, n) {
        random_shuffle(all(g[i]));
    }

    cin >> k;
    rep(i, k) {
        int s, f;
        cin >> s >> f;
        s--; f--;
        spfa(s);
        if (d[f] == INT_MAX) {
            cout << -1 << '\n';
        } else {
            cout << d[f] << '\n';
        }
    }
}
