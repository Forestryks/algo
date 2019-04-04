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

namespace mincost {
    struct edge {
        int p, q;
        ll f, c, w;
    };

    const int inf = 2e9;
    const int MAXN = 1e5 + 5;

    int n;
    int s, t;
    vector<int> g[MAXN];
    vector<edge> e;
    int pr[MAXN];
    bool used[MAXN];
    int d[MAXN];

    void spfa() {
        fill(pr, pr + n, inf);
        fill(used, used + n, false);

        queue<int> q;
        q.push(s);
        used[s] = true;
        pr[s] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            used[v] = false;
            if (pr[v] == inf) continue;

            for (auto x : g[v]) {
                int to = e[x].q;
                ll w = e[x].w;

                if (e[x].c - e[x].f < 1) continue;

                if (pr[v] + w < pr[to]) {
                    pr[to] = pr[v] + w;
                    if (!used[to]) {
                        q.push(to);
                    }
                }
            }
        }
    }

    bool dijkstra() {
        fill(used, used + n, false);
        fill(d, d + n, inf);

        d[s] = 0;

        for (int qq = 0; qq < n; ++qq) {
            int v = -1;
            for (int i = 0; i < n; ++i) {
                if (used[i]) continue;
                if (v == -1 || d[i] < d[v]) {
                    v = i;
                }
            }

            if (d[v] == inf) break;

            used[v] = true;

            for (auto x : g[v]) {
                if (e[x].c - e[x].f < 1) continue;

                int to = e[x].q;
                ll w = e[x].w + pr[v] - pr[to];

                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            pr[i] += d[i];
        }

        return d[t] != inf;
    }

    int dfs(int v, int mn) {
        used[v] = true;
        if (v == t) return mn;

        for (auto x : g[v]) {
            int to = e[x].q;
            ll w = e[x].w + pr[v] - pr[to];
            if (e[x].c - e[x].f < 1) continue;
            if (w != 0) continue;
            if (used[to]) continue;

            int res = dfs(to, min<ll>(mn, e[x].c - e[x].f));
            if (res > 0) {
                e[x].f += res;
                e[x ^ 1].f -= res;
                return res;
            }
        }
        return 0;
    }

    void maxflow() {
        spfa();
        while (dijkstra()) {
            fill(used, used + n, false);
            dfs(s, inf);
        }
    }

    void link(int p, int q, ll c, ll w) {
        g[p].push_back(e.size());
        g[q].push_back(e.size() + 1);
        e.push_back({p, q, 0, c, w});
        e.push_back({q, p, 0, 0, -w});
    }
};

int n, m;

int main() {
    FAST_IO;
    cin >> n >> m;
    rep(i, m) {
        int p, q, c, w;
        cin >> p >> q >> c >> w;
        mincost::link(p - 1, q - 1, c, w);
    }

    mincost::s = 0;
    mincost::t = n - 1;
    mincost::n = n;

    mincost::maxflow();

    ll res = 0;
    for (int i = 0; i < mincost::e.size(); i += 2) {
        res += mincost::e[i].f * mincost::e[i].w;
    }

    cout << res << endl;
}
