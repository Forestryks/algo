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
const ll MOD = 1000000;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

int n, m, k;
int ndfa[11][27];
int dfa[1050][27];
bool used[1050];

int dp[105][1050];

void makeDFA() {
    int start = (1 << n) - 1;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int mask = q.front(); q.pop();
        if (used[mask]) continue;
        used[mask] = true;
        int to = 0;

        rep(ch, 26) {
            int to = 0;
            for (int i = 0, bit = 1; bit <= mask; ++i, bit <<= 1) {
                if (!(bit & mask)) continue;
                to |= ndfa[i][ch];
            }
            if (to) {
                dfa[mask][ch] = to;
                q.push(to);
            }
        }
    }
}

int main() {
    FAST_IO;
    // FILE_IO("path-string");
    cin >> n >> m >> k;
    rep(i, m) {
        int u, v;
        char a;
        cin >> u >> v >> a;
        ndfa[u - 1][a - 'a'] |= (1 << (v - 1));
    }

    makeDFA();

    dp[0][(1 << n) - 1] = 1;
    for (int stage = 1; stage <= k; ++stage) {
        for (int v = 1; v < (1 << n); ++v) {
            for (int ch = 0; ch < 26; ++ch) {
                if (dfa[v][ch]) {
                    dp[stage][dfa[v][ch]] = (dp[stage][dfa[v][ch]] + dp[stage - 1][v]) % MOD;
                }
            }
        }
    }

    int res = 0;
    for (int i = 1; i < (1 << n); ++i) {
        res = (res + dp[k][i]) % MOD;
    }
    cout << res << endl;
}