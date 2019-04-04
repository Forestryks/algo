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

namespace dinic {
    const int inf = 2e9;
    const int MAXN = 100000;

    struct edge {
        int p, q, c, f;
    };

    int n, m;
    int s, t;
    vector<edge> e;
    vector<int> g[MAXN];
    int d[MAXN];
    int pos[MAXN];
    int B = 1;

    bool bfs() {
        fill(d, d + n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (auto x : g[v]) {
                int to = e[x].q;
                if (d[to] != -1) continue;
                if (e[x].c - e[x].f < B) continue;

                d[to] = d[v] + 1;
                q.push(to);
            }
        }

        return d[t] != -1;
    }

    int dfs(int v, int mn) {
        if (v == t) return mn;

        for (; pos[v] < g[v].size(); pos[v]++) {
            int x = g[v][pos[v]];
            int to = e[x].q;
            if (e[x].c - e[x].f < B) continue;
            if (d[to] != d[v] + 1) continue;
            int res = dfs(to, min(mn, e[x].c - e[x].f));
            if (res > 0) {
                e[x].f += res;
                e[x ^ 1].f -= res;
                return res;
            }
        }

        return 0;
    }

    void link(int i, int j, int k) {
        g[i].push_back(e.size());
        g[j].push_back(e.size() + 1);
        e.push_back({i, j, k, 0});
        e.push_back({j, i, 0, 0});
    }

    int maxflow() {
        for (B = (1 << 30); B > 0; B = (B >> 1)) {
            while (bfs()) {
                fill(pos, pos + n, false);
                while (dfs(s, inf));
            }
        }

        int res = 0;
        for (auto x : g[s]) {
            res += e[x].f;
        }
        return res;
    }
}

const int MAXN = 505;
int n, m;

int main() {
    FAST_IO;
    // cin >> n >> m;
    n = readInt();
    m = readInt();

    dinic::s = 0;
    dinic::t = n - 1;
    dinic::n = n;

    rep(i, m) {
        int p, q, c;
        // cin >> p >> q >> c;
        p = readInt();
        q = readInt();
        c = readInt();
        dinic::link(p - 1, q - 1, c);
    }

    dinic::maxflow();

    ll res = 0;
    for (auto x : dinic::g[0]) {
        res += dinic::e[x].f;
    }
    // cout << res << ".0\n";
    writeInt(res);
    writeWord(".0\n");

    for (int i = 0; i < dinic::e.size(); i += 2) {
        // cout << dinic::e[i].f << ".0\n";
        writeInt(dinic::e[i].f);
        writeWord(".0\n");
    }
}


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

namespace dinic {
    const int inf = 2e9;
    const int MAXN = 100000;

    struct edge {
        int p, q, c, f;
    };

    int n, m;
    int s, t;
    vector<edge> e;
    vector<int> g[MAXN];
    int d[MAXN];
    int pos[MAXN];
    int B = 1;

    bool bfs() {
        fill(d, d + n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (auto x : g[v]) {
                int to = e[x].q;
                if (d[to] != -1) continue;
                if (e[x].c - e[x].f < B) continue;

                d[to] = d[v] + 1;
                q.push(to);
            }
        }

        return d[t] != -1;
    }

    int dfs(int v, int mn) {
        if (v == t) return mn;

        for (; pos[v] < g[v].size(); pos[v]++) {
            int x = g[v][pos[v]];
            int to = e[x].q;
            if (e[x].c - e[x].f < B) continue;
            if (d[to] != d[v] + 1) continue;
            int res = dfs(to, min(mn, e[x].c - e[x].f));
            if (res > 0) {
                e[x].f += res;
                e[x ^ 1].f -= res;
                return res;
            }
        }

        return 0;
    }

    void link(int i, int j, int k) {
        g[i].push_back(e.size());
        g[j].push_back(e.size() + 1);
        e.push_back({i, j, k, 0});
        e.push_back({j, i, 0, 0});
    }

    int maxflow() {
        for (B = (1 << 30); B > 0; B = (B >> 1)) {
            while (bfs()) {
                fill(pos, pos + n, false);
                while (dfs(s, inf));
            }
        }

        int res = 0;
        for (auto x : g[s]) {
            res += e[x].f;
        }
        return res;
    }
}

const int MAXN = 505;
int n, m;

int main() {
    FAST_IO;
    cin >> n >> m;

    dinic::s = 0;
    dinic::t = n - 1;
    dinic::n = n;

    rep(i, m) {
        int p, q, c;
        cin >> p >> q >> c;
        dinic::link(p - 1, q - 1, c);
    }

    dinic::maxflow();

    ll res = 0;
    for (auto x : dinic::g[0]) {
        res += dinic::e[x].f;
    }
    cout << res << ".0\n";

    for (int i = 0; i < dinic::e.size(); i += 2) {
        cout << dinic::e[i].f << ".0\n";
    }
}