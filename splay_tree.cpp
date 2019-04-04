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
#define right right123
#define left left123
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

namespace splay {
    struct node {
        int size;
        ll val, sum;
        node *left, *right, *parent;

        node(int x) {
            left = right = parent = nullptr;
            val = sum = x;
            size = 1;
        }
    };

    ll get_sum(node *v) {
        if (v == nullptr) return 0;
        return v->sum;
    }

    int get_size(node *v) {
        if (v == nullptr) return 0;
        return v->size;
    }

    void update(node *v) {
        v->sum = get_sum(v->left) + get_sum(v->right) + v->val;
        v->size = get_size(v->left) + get_size(v->right) + 1;
    }

    bool is_parent_at_left(node *v) {
        assert(v != nullptr);
        return v->parent->right == v;
    }

    void move_parent(node *from, node *to) {
        if (from->parent == nullptr) {
            to->parent = nullptr;
            return;
        }

        bool left = is_parent_at_left(from);
        to->parent = from->parent;
        if (left) {
            to->parent->right = to;
        } else {
            to->parent->left = to;
        }
    }

    void zig(node *x, node *y, bool left) {
        if (left) {
            if (x->left != nullptr) {
                x->left->parent = y;
            }
            y->right = x->left;
            x->left = y;
        } else {
            if (x->right != nullptr) {
                x->right->parent = y;
            }
            y->left = x->right;
            x->right = y;
        }
        update(y);
        update(x);
        
        move_parent(y, x);
        y->parent = x;
    }

    void zigzig(node *x, node *y, node *z, bool left) {
        zig(y, z, left);
        zig(x, y, left);
    }

    void zigzag(node *x, node *y, node *z, bool left) {
        zig(x, y, left);
        zig(x, z, left ^ 1);
    }

    bool advance(node *v) {
        if (v->parent == nullptr) return false;

        bool left = is_parent_at_left(v);
        if (v->parent->parent == nullptr) {
            zig(v, v->parent, left);
            return true;
        }

        bool pleft = is_parent_at_left(v->parent);
        if (pleft == left) {
            zigzig(v, v->parent, v->parent->parent, left);
        } else {
            zigzag(v, v->parent, v->parent->parent, left);
        }
        return true;
    }
    
    node *splay(node *v) {
        while (advance(v));
        return v;
    }

    ll query_sum(node *v) {
        splay(v);
        return v->sum;
    }

    void change(node *v, int x) {
        splay(v);
        v->val = x;
        update(v);
    }

    void merge(node *a, node *b) {
        if (a == b) return;
        splay(a);
        splay(b);
        if (a->parent != nullptr || b->parent != nullptr) return;

        node *v = b;
        while (v->left != nullptr) v = v->left;

        splay(v);
        v->left = a;
        a->parent = v;
        update(v);
    }

    void split(node *v, int k) {
        splay(v);

        if (v->size <= k) return;

        while (true) {
            int lsz = get_size(v->left);
            if (lsz > k) v = v->left;
            else if (lsz < k) {
                k -= lsz + 1;
                v = v->right;
            } else {
                break;
            }
        }

        splay(v);
        v->left->parent = nullptr;
        v->left = nullptr;
        update(v);
    }

    void print(node *v) {
        if (v == nullptr) return;
        cout << v->val << " : left = ";
        if (v->left == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->left->val;
        }
        cout << "; right = ";
        if (v->right == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->right->val;
        }
        cout << "; parent = ";
        if (v->parent == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->parent->val;
        }
        cout << endl;
    }
};

using namespace splay;

const int MAXN = 1e5 + 5;

int n, m;
node *a[MAXN];

int main() {
    FAST_IO;
    cin >> n >> m;
    rep(i, n) {
        a[i] = new node(0);
    }
    
    rep(i, m) {
        string t;
        cin >> t;
        if (t[1] == 'i') {
            int p, q;
            cin >> p >> q;
            merge(a[p - 1], a[q - 1]);
        } else if (t[1] == 'p') {
            int p, k;
            cin >> p >> k;
            split(a[p - 1], k);
        } else if (t[1] == 'n') {
            int p, x;
            cin >> p >> x;
            change(a[p - 1], x);
        } else {
            int p;
            cin >> p;
            cout << query_sum(a[p - 1]) << '\n';
        }

        // cout << endl;
        // rep(j, n) {
        //     print(a[j]);
        // }
        // cout << endl;
        // cout << "ok" << endl;
    }
}
