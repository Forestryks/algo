////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
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
 
#define FAST_ALLOCATOR_MEMORY 250000000
  
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void * operator new ( size_t n ) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
    return (void *)res;
}
inline void operator delete ( void * ) noexcept { }
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }
#endif
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const double DINF = numeric_limits<double>::infinity();
const ll MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
ll rnd(ll x, ll y) {
    static mt19937 mmtw(time(0));
    static uniform_int_distribution<ll> rd;
    return rd(mmtw) % (y - x + 1) + x;
}
 
typedef long long ll;
 
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 1e5 + 5;

int n;

namespace ukkonen {
    const int inf = 1e9;
    const int maxn = 2e5 + 5;

    int n; // кол-во символов в строке
    char s[maxn]; // строка
    int len[maxn]; // длина ребра (в строке), входящего в вершину
    int fpos[maxn]; // позиция начала ребра (в строке), входящего в вершину
    int link[maxn]; // суффиксная ссылка из вершины
    map<int, int> to[maxn]; // ребра по символам из вершины
    int pos; // на сколько нужно спуститься по ребру
    int sz; // текущее кол-во вершин
    int node; // вершина в которой стоим (из которой будем спускаться)

    int createNode(int p, int l) { // создаем вершину [p, p + l)
        fpos[sz] = p;
        len[sz] = l;
        return sz++;
    }

    void go() {
        // стоим в вершине node, проходим необходимое кол-во ребер так, чтобы pos лежал в интервале 
        while (pos > len[to[node][s[n - pos]]]) {
            node = to[node][s[n - pos]];
            pos -= len[node];
        }
    }

    void tree_add(int ch) {
        s[n++] = ch;
        pos++;
        int last = 0;

        while (pos > 0) {
            go();
            int edge = s[n - pos];
            int &v = to[node][edge];
            int t = s[fpos[v] + pos - 1];

            if (v == 0) {
                v = createNode(n - pos, inf);
                link[last] = node;
                last = 0;
            } else if (t == ch) {
                link[last] = node;
                return;
            } else {
                int u = createNode(fpos[v], pos - 1);
                to[u][t] = v;
                to[u][ch] = createNode(n - 1, inf);
                fpos[v] += pos - 1;
                len[v] -= pos - 1;

                v = u;

                link[last] = u;
                last = u;
            }

            if (node == 0) {
                pos--;
            } else {
                node = link[node];
            }
        }
    }

    void init() {
        len[0] = inf;
        sz = 1;
        node = 0;
    }

    struct qwe {
        int a, b, c, d;
    };

    vector<qwe> ans;

    void dfs(int v) {
        for (auto it : to[v]) {
            if (it.s != 0) {
                ans.push_back({v + 1, it.s + 1, fpos[it.s] + 1, min(fpos[it.s] + len[it.s], ::n)});
                dfs(it.s);
            }
        }
    }
};

int main() {
    // FILE_IO("tree");
    ukkonen::init();

    string a;
    cin >> a;
    n = a.size();
    for (auto it : a) {
        ukkonen::tree_add(it);
    }

    cout << ukkonen::sz << ' ' << ukkonen::sz - 1 << '\n';
    ukkonen::dfs(0);

    sort(all(ukkonen::ans), [](const ukkonen::qwe &a, const ukkonen::qwe &b) {
        if (a.c == b.c) {
            return a.d < b.d;
        }
        return a.c < b.c;
    });

    for (auto it : ukkonen::ans) {
        cout << it.a << ' ' << it.b << ' ' << it.c << ' ' << it.d << '\n';
    }
}
