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
    int d[MAXN];
    bool used[MAXN];

    bool spfa() {
        fill(d, d + n, inf);
        fill(used, used + n, false);

        queue<int> q;
        q.push(s);
        used[s] = true;
        d[s] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            used[v] = false;
            if (d[v] == inf) continue;

            for (auto x : g[v]) {
                int to = e[x].q;
                ll w = e[x].w;

                if (e[x].c - e[x].f < 1) continue;

                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    if (!used[to]) {
                        q.push(to);
                    }
                }
            }
        }

        return d[t] != inf;
    }

    int dfs(int v, int mn) {
        used[v] = true;
        if (v == t) return mn;

        for (auto x : g[v]) {
            int to = e[x].q;
            if (e[x].c - e[x].f < 1) continue;
            if (d[to] != d[v] + e[x].w) continue;
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
        while (spfa()) {
            // rep(i, n) {
            //     cerr << d[i] << ' ';
            // }
            // cerr << endl;
            fill(used, used + n, false);
            dfs(s, inf);
        }
    }

    void k_flow(int k) {
        for (int i = 0; i < k && spfa(); ++i) {
            // rep(i, n) {
            //     cerr << d[i] << ' ';
            // }
            // cerr << endl;
            fill(used, used + n, false);
            dfs(s, 1);
        }
    }

    void link(int p, int q, ll c, ll w) {
        g[p].push_back(e.size());
        g[q].push_back(e.size() + 1);
        e.push_back({p, q, 0, c, w});
        e.push_back({q, p, 0, 0, -w});
    }

    vector<int> path;

    void get_path(int v) {
        if (v == t) return;

        for (auto x : g[v]) {
            if (e[x].f > 0) {
                e[x].f--;
                e[x ^ 1].f++;
                path.push_back(x);
                get_path(e[x].q);
                return;
            }
        }
    }

    void get_path() {
        path.clear();
        get_path(s);
        // reverse(all(path));
    }
};

int n, m, k;

int main() {
    FAST_IO;
    cin >> n >> m >> k;

    rep(i, m) {
        int p, q, w;
        cin >> p >> q >> w;
        mincost::link(p - 1, q - 1, 1, w);
        mincost::link(q - 1, p - 1, 1, w);
    }

    mincost::n = n;
    mincost::s = 0;
    mincost::t = n - 1;

    mincost::k_flow(k);

    int cnt = 0;
    for (auto x : mincost::g[mincost::s]) {
        cnt += mincost::e[x].f;
    }

    if (cnt < k) {
        cout << -1 << endl;
        return 0;
    }

    ll price = 0;
    for (int i = 0; i < mincost::e.size(); i += 2) {
        price += mincost::e[i].f * mincost::e[i].w;
    }

    cout.setf(ios::fixed);
    cout.precision(20);
    cout << price * 1.0 / k << endl;
    rep(i, k) {
        mincost::get_path();
        cout << mincost::path.size() << ' ';
        for (auto it : mincost::path) {
            cout << (it / 4) + 1 << ' ';
        }
        cout << '\n';
    }
}