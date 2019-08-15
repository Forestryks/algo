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

vector<pll> a;

ll prod(pll a, pll b) {
    return a.f * b.s - a.s * b.f;
}

bool cmp(pll p, pll q) {
    ll pr = prod({p.f - a[0].f, p.s - a[0].s}, {q.f - a[0].f, q.s - a[0].s});
    if (pr > 0) {
        return true;
    } else if (pr < 0) {
        return false;
    } else {
        ll d1 = (p.f - a[0].f) * (p.f - a[0].f) + (p.s - a[0].s) * (p.s - a[0].s);
        ll d2 = (q.f - a[0].f) * (q.f - a[0].f) + (q.s - a[0].s) * (q.s - a[0].s);
        return d1 < d2;
    }
}

inline pll get(pll a, pll b) {
    return {b.f - a.f, b.s - a.s};
}

vector<pll> ans;

int main() {
    int n;
    cin >> n;
    a.resize(n);
    
    vector<bool> use(n, true);
    rep(i, n) {
        cin >> a[i].f >> a[i].s;
    }

    int st = 0;
    rep(i, n) {
        if (a[i].s < a[st].s || (a[i].s == a[st].s && a[i].f > a[st].f)) st = i;
    }
    swap(a[0], a[st]);

    sort(a.begin() + 1, a.end(), cmp);

    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1]) use[i] = false;
    }

    int k = -1;
    for (int i = 0; i < n; ++i) {
        if (!use[i]) continue;
        while (k > 0 && prod(get(ans[k - 1], ans[k]), get(ans[k], a[i])) <= 0) {
            ans.pop_back();
            k--;
        }
        ans.push_back(a[i]);
        k++;
    }

    cout << ans.size() << '\n';
    for (auto t : ans) {
        cout << t.f << ' ' << t.s << '\n';
    }
}