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

const int inf = 2e9;

struct point {
    ll x, y;
};

bool operator==(const point &a, const point &b) {
    return a.x == b.x && a.y == b.y;
}

ll dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

ll cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ll sz_sq(point a) {
    return a.x * a.x + a.y * a.y;
}

point get(point a, point b) {
    return {b.x - a.x, b.y - a.y};
}

bool cmp(const point &a, const point &b) {
    ll pr = cross(a, b);
    if (pr > 0) return true;
    else if (pr < 0) return false;
    else {
        ll d1 = sz_sq(a);
        ll d2 = sz_sq(b);
        return d1 < d2;
    }
}

vector<point> build_convex(vector<point> a) {
    int n = a.size();

    sort(a.begin() + 1, a.end(), cmp);

    vector<point> res;
    int k = -1;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && cross(get(res[k - 1], res[k]), get(res[k], a[i])) <= 0) {
            res.pop_back();
            k--;
        }
        res.push_back(a[i]);
        k++;
    }

    return res;
}

struct line {
    ll a, b, c;
    ll get(point t) {
        return a * t.x + b * t.y + c;
    }
};

struct query {
    ll x, y;
    int id, type;
};

const int MAXN = 1e5 + 5;

int n, m;
vector<point> a;
vector<line> lines;
vector<query> q;
point ans[MAXN][2];

int main() {
    cin >> m >> n;
    lines.resize(m);
    rep(i, m) {
        cin >> lines[i].a >> lines[i].b >> lines[i].c;
    }

    a.resize(n);
    rep(i, n) {
        cin >> a[i].x >> a[i].y;
    }

    int mn = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i].y < a[mn].y || (a[i].y == a[mn].y && a[i].x < a[mn].x)) {
            mn = i;
        }
    }

    swap(a[0], a[mn]);

    point st = a[0];

    for (int i = n - 1; i >= 0; --i) {
        a[i].x -= a[0].x;
        a[i].y -= a[0].y;
    }

    a = build_convex(a);
    reverse(all(a));

    for (auto &it : a) {
        it.x += st.x;
        it.y += st.y;
    }

    n = a.size();

    // for (auto it : a) {
    //     cout << it.x << ' ' << it.y << endl;
    // }


    for (int i = 0; i < m; ++i) {
        q.push_back({lines[i].b, -lines[i].a, i, 0});
        q.push_back({-lines[i].b, lines[i].a, i, 1});
    }

    sort(all(q), [](const query &a, const query &b){
        if (a.x == 0 && b.x == 0) {
            return a.y > b.y;
        }
        if (a.x >= 0 && b.x < 0) return true;
        if (b.x >= 0 && a.x < 0) return false;

        return cross({a.x, a.y}, {b.x, b.y}) < 0;
    });

    // for (auto &it : q) {
    //     cout << it.x << ' ' << it.y << endl;
    // }

    mn = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i].x < a[mn].x || (a[i].x == a[mn].x && a[i].y < a[mn].y)) {
            mn = i;
        }
    }
    rotate(a.begin(), a.begin() + mn, a.end());

    int p = 0;
    for (auto &it : q) {
        if (n == 1) {
            ans[it.id][it.type] = a[0];
            continue;
        } else if (n == 2) {
            ans[it.id][it.type] = a[it.type];
            continue;
        }

        while (true) {
            point vec = get(a[p], a[p + 1 == n ? 0 : p + 1]);
            if (cross(vec, {it.x, it.y}) <= 0) {
                p++;
                if (p == n) p = 0;
            } else {
                break;
            }
        }

        ans[it.id][it.type] = a[p];
    }

    vector<int> res;

    rep(i, m) {
        point p1 = ans[i][0], p2 = ans[i][1];
        if (lines[i].get(p1) == 0 || lines[i].get(p2) == 0) res.push_back(i + 1);
        else if (((lines[i].get(p1) < 0) ^ (lines[i].get(p2) > 0)) == 0) res.push_back(i + 1);
    }

    cout << res.size() << '\n';
    for (auto it : res) {
        cout << it << ' ';
    }
    cout << '\n';
}