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
///////////////////////////////////////////////////////////////////////////////////////////////

struct Trie {
    map<char, Trie *> edges;
    char prev;
    bool is_term;
    int cnt;
    Trie *link;
    Trie *suplink;
    Trie *parent;

    Trie(Trie *p, char ch) {
        is_term = 0;
        parent = p;
        link = suplink = nullptr;
        prev = ch;
        cnt = 0;
    }
};
vector<Trie *> inv;

void make_link(Trie *v) {
    if (!v->parent) {
        v->link = v->suplink = v;
        return;
    }
    if (!v->parent->parent) {
        v->link = v->parent;
        if (v->is_term) v->suplink = v;
        else v->suplink = v->parent;
        return;
    }

    Trie *to = v->parent->link;
    char ch = v->prev;
    while (to->parent && to->edges.find(ch) == to->edges.end()) {
        to = to->link;
    }
    if (to->edges.find(ch) != to->edges.end()) {
        v->link = to->edges[ch];
    } else {
        v->link = to;
    }

    if (v->is_term) {
        v->suplink = v;
    } else {
        v->suplink = v->link->suplink;
    }
}

void bfs(Trie *root) {
    queue<Trie *> q;
    q.push(root);
    while (!q.empty()) {
        Trie *v = q.front();
        q.pop();
        inv.push_back(v);
        make_link(v);
        for (auto it : v->edges) {
            q.push(it.s);
        }
    }
}

Trie *trie_add(Trie *root, string s) {
    Trie *v = root;
    for (char ch : s) {
        if (v->edges.find(ch) == v->edges.end()) {
            v->edges[ch] = new Trie(v, ch);
        }
        v = v->edges[ch];
    }
    v->is_term = true;
    return v;
}

void count_all() {
    for (auto v : inv) {
        if (v->parent) {
            if (v->link->suplink->is_term) {
                v->link->suplink->cnt += v->cnt;
            }
        }
    }
}

const int MAXN = 1e6 + 5;
int n;
string s;
Trie *ptr[MAXN];

int main() {
    FILE_IO("search5");
    FAST_IO;
    cin >> n;
    Trie *root = new Trie(nullptr, 0);
    rep(i, n) {
        cin >> s;
        ptr[i] = trie_add(root, s);
    }
    cin >> s;

    bfs(root);

    Trie *v = root;
    for (auto ch : s) {
        while (v->parent && v->edges.find(ch) == v->edges.end()) {
            v = v->link;
        }
        if (v->edges.find(ch) != v->edges.end()) v = v->edges[ch];

        if (v->suplink->is_term) v->suplink->cnt += 1;
    }

    reverse(all(inv));
    count_all();

    rep(i, n) {
        cout << ptr[i]->cnt << endl;
    }
}
