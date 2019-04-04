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
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw(35446464654);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
template <class T> T binpow(T n, T k) { if (k == 1) return n; if (k & 1) return binpow(n, k - 1) * n; T a = binpow(n, k / 2); return a * a; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
long double PI = 3.14159265358979323846;
////////////////////////////////////////////////////////////////////////////////////////////////

struct Node {
    int val;
    Node *L, *R;
    Node(int v) : val(v), L(nullptr), R(nullptr) {}
};

int n;
vector<Node *> ver;

int get(Node *v) {
    if (v == nullptr) return 0;
    return v->val;
}

int get(Node *L, Node *R) {
    int a = get(L);
    int b = get(R);
    return b - a;
}

Node *update(int pos, Node *v, int l = 0, int r = n) {
    if (r - l == 1) {
        return new Node(v->val + 1);
    }
    int m = l + (r - l) / 2;
    Node *t = new Node(0);
    if (pos < m) {
        t->L = update(pos, v->L, l, m);
        t->R = v->R;
    } else {
        t->L = v->L;
        t->R = update(pos, v->R, m, r);
    }
    t->val = get(t->L) + get(t->R);
    return t;
}

int query(int k, Node *L, Node *R, int l = 0, int r = n) {
    if (r - l <= 1) return l;
    if (get(L, R) < k) {
        // cout << "g " << get(L, R) << endl;
        // cout << "k " << k << endl;
        // cout << l << ' ' << r << endl;
        // cout << "bye" << endl;
        exit(123);
    }
    int m = l + (r - l) / 2;
    if (get(L->L, R->L) >= k) {
        return query(k, L->L, R->L, l, m);
    } else {
        return query(k - get(L->L, R->L), L->R, R->R, m, r);
    }
}

Node *build(int l = 0, int r = n) {
    if (r - l < 1) return nullptr;
    if (r - l == 1) return new Node(0);
    Node *t = new Node(0);
    int m = l + (r - l) / 2;
    t->L = build(l, m);
    t->R = build(m, r);
    return t;
}

const int MAXN = 450005;
int a[MAXN];
int to_comp[MAXN];
vector<int> to_a;
Node *root;

void compress() {
    unordered_map<int, int> mp;
    vector<int> srt(a, a + n);
    sort(all(srt));
    srt.resize(unique(all(srt)) - srt.begin());

    for (int i = 0; i < srt.size(); ++i) {
        mp[srt[i]] = i;
        to_a.push_back(srt[i]);
    }

    rep(i, n) {
        to_comp[i] = mp[a[i]];
    }
}

void prepareTree() {
    root = build();
    ver.push_back(root);
    for (int i = 0; i < n; ++i) {
        root = update(to_comp[i], root);
        ver.push_back(root);
    }
}

int solve(int L, int R, int k) {
    return to_a[query(k, ver[L - 1], ver[R])];
}

int main() {
    FAST_IO;
    // freopen("input.txt", "r", stdin);
    cin >> n;

// generate a_i
    ll l, m;
    cin >> a[0] >> l >> m;
    for (int i = 1; i < n; ++i) {
        a[i] = (l * ((ll)(a[i - 1])) + m) % 1000000000LL;
    }
    compress();

    // rep(i, to_a.size()) {
    //     cout << a[i] << ' ';
    // } cout << endl;

    prepareTree();

    ll res = 0;
//tests
    int B;
    cin >> B;
    rep(qwe, B) {
        int q;
        cin >> q;
        ll x1, lx, mx, y1, ly, my, k1, lk, mk, ig, jg;
        cin >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        // cout << x1 << ' ' << y1 << ' ' << k1 << " : " << solve(x1, y1, k1) << endl;
        ig = x1, jg = y1;
        res += solve(x1, y1, k1);
        // cout << res << endl;

        for (int i = 1; i < q; ++i) {
            x1 = (((ig - 1) * lx + mx) % n) + 1;
            y1 = (((jg - 1) * ly + my) % n) + 1;
            ig = min(x1, y1);
            jg = max(x1, y1);
            k1 = (((k1 - 1) * lk + mk) % (jg - ig + 1)) + 1;

            // cout << ig << ' ' << jg << ' ' << k1 << " : " << solve(ig, jg, k1) << endl;
            res += solve(ig, jg, k1);
        }
    }
    cout << res << endl;
}