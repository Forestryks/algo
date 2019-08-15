#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define rep(i, n) for (int (i) = 0; (i) < (n); ++(i))
#define all(x) (x).begin(), (x).end()
#define f first
#define s second
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define left left123
#define right right123

struct edge {
    int v, to;
    ll c, f;
};

const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
int n, m;
int s, f;
int last = 0;
edge e[MAXM];

vector<int> g[MAXN];
int d[MAXN];
int p[MAXN];
int B;

void link(int a, int b, int c) {
    e[last++] = {a, b, c, 0};
    e[last++] = {b, a, c, 0};
    g[a].push_back(last - 2);
    g[b].push_back(last - 1);
}

bool bfs() {
    queue<int> q;
    fill(d, d + n, -1);
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto i : g[v]) {
            int to = e[i].to;
            if (d[to] != -1 || e[i].c - e[i].f < B) continue;
            d[to] = d[v] + 1;
            q.push(to);
        }
    }

    return (d[f] != -1);
}

ll dfs(int v, ll mx) {
    if (v == f) return mx;
    ll cur = 0;
    for (; p[v] < g[v].size(); ++p[v]) {
        int i = g[v][p[v]];
        int to = e[i].to;
        if (d[to] != d[v] + 1 || e[i].c - e[i].f < B) continue;
        ll x = dfs(to, min(mx - cur, e[i].c - e[i].f));

        e[i].f += x;
        e[i ^ 1].f -= x;
        cur += x;
        if (cur == mx) break;
    }
    return cur;
}

int main() {
    FAST_IO;
    cin >> n >> m;
    s = 0;
    f = n - 1;
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        link(a, b, c);
    }

    ll res = 0;
    for (B = (1 << 30); B > 0; B >>= 1) {
        while (bfs()) {
            while (true) {
                fill(p, p + n, 0);
                ll x = dfs(s, 1e9);
                if (x == 0) break;
                res += x;
            }
        }
    }

    cout << res << endl;
    for (int i = 0; i < last; i += 2) {
        cout << e[i].f << '\n';
    }
}
