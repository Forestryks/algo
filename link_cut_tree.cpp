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

int CNT = 0;

namespace Splay {
    struct node {
        int size;
        bool reversed;
        node *left, *right, *parent;
        node *p;

        int id;

        node() {
            left = right = parent = p = nullptr;
            size = 1;
            reversed = false;
            id = CNT++;
        }
    };

    int get_size(node *v) {
        if (v == nullptr) return 0;
        return v->size;
    }

    void update(node *v) {
        assert(v != nullptr);
        v->size = get_size(v->left) + get_size(v->right) + 1;
    }

    void push(node *v) {
        assert(v != nullptr);
        if (!v->reversed) return;
        v->reversed = false;
        swap(v->left, v->right);
        if (v->left != nullptr) v->left->reversed ^= true;
        if (v->right != nullptr) v->right->reversed ^= true;
    }

    bool is_parent_at_left(node *v) {
        assert(v != nullptr);
        return v->parent->right == v;
    }

    void move_parent(node *from, node *to) {
        assert(from != nullptr);
        assert(to != nullptr);
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
        assert(x != nullptr);
        assert(y != nullptr);
        assert(x->parent == y);
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
        assert(v != nullptr);
        if (v->parent == nullptr) return false;

        
        if (v->parent->parent == nullptr) {
            push(v->parent);
            push(v);
            bool left = is_parent_at_left(v);
            zig(v, v->parent, left);
            return true;
        }
        push(v->parent->parent);
        push(v->parent);
        push(v);

        bool left = is_parent_at_left(v);
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

    node *go_up(node *v) {
        splay(v);
        push(v);
        while (v->right != nullptr) {
            v = v->right;
            push(v);
        }
        splay(v);
        return v;
    }

    void split(node *v) {
        assert(v != nullptr);
        splay(v);
        push(v);
        if (v->left == nullptr) return;
        v->left->parent = nullptr;
        node *child = go_up(v->left);
        child->p = v;
        v->left = nullptr;
        update(v);
    }

    void merge(node *a, node *b) {
        assert(a != nullptr);
        assert(b != nullptr);
        if (a == b) return;
        splay(a);
        splay(b);
        if (a->parent != nullptr || b->parent != nullptr) return;

        node *v = b;
        push(v);
        while (v->left != nullptr) {
            v = v->left;
            push(v);
        }

        splay(v);
        push(v);
        v->left = a;
        a->parent = v;
        a->p = nullptr;
        update(v);
    }

    void print(node *v) {
        if (v == nullptr) return;
        cout << v->id << " : left = ";
        if (v->left == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->left->id;
        }
        cout << "; right = ";
        if (v->right == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->right->id;
        }
        cout << "; parent = ";
        if (v->parent == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->parent->id;
        }
        cout << "; par = ";
        if (v->p == nullptr) {
            cout << "nullptr";
        } else {
            cout << v->p->id;
        }
        cout << "; reversed = ";
        cout << v->reversed;
        cout << endl;
    }
};

bool debug = false;

using namespace Splay;

const int MAXN = 2e5 + 5;
int n, m;

node *a[MAXN];

void print_all() {
    cout << endl;
    rep(j, n) {
        print(a[j]);
    }
    cout << endl;
}

void expose(node *v) {
    split(v);
    
    while (true) {
        v = go_up(v);
        if (v->p == nullptr) break;
        split(v->p);
        merge(v, v->p);
    }
}

void makeRoot(node *v) {
    expose(v);
    splay(v);
    v->reversed ^= 1;
}

int main() {
    FAST_IO;
    cin >> n >> m;
    // n = 3;
    rep(i, n) {
        a[i] = new node();
        // p[i] = nullptr;
    }
 
    // a[0]->p = a[1];
    // print_all();
    // makeRoot(a[0]);
    // makeRoot(a[1]);
    // a[0]->p = a[1];
    // print_all();

    // makeRoot(a[0]);
    // expose(a[1]);
    // print_all();


    rep(i, m) {
        string t;
        cin >> t;
        if (t[0] == 'l') {
            int p, q;
            cin >> p >> q;
            p--; q--;

            makeRoot(a[p]);
            makeRoot(a[q]);
            a[p]->p = a[q];
        } else if (t[0] == 'c') {
            int p, q;
            cin >> p >> q;
            p--; q--;
            makeRoot(a[p]);
            expose(a[q]);
            split(a[p]);
            a[q]->p = nullptr;
        } else {
            int p, q;
            cin >> p >> q;
            p--; q--;
            makeRoot(a[p]);

            expose(a[q]);
            
            auto t = go_up(a[q]);
            if (t != a[p]) cout << -1 << '\n';
            else {
                splay(a[q]);
                cout << get_size(a[q]) - 1 << '\n';
            }
        }

        // print_all();
    }
}
