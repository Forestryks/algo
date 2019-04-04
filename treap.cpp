////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odintsov
// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

// #define FAST_ALLOCATOR_MEMORY 250000000
 
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
string mtos(int mask, int bits = 5, bool inv = false) 
{ string s; rep(i, bits) { s += '0' + ((mask >> i) & 1); } if (!inv) reverse(all(s)); return s; }
mt19937 mmtw(MOD);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(mmtw) % (y - x + 1) + x; }
ld PI = 3.141592653589793238462643383279;
///////////////////////////////////////////////////////////////////////////////////////////////

struct node {
    node *left, *right;
    int key, prior;
    node(int key) : key(key) {
        prior = rand();
        left = right = nullptr;
    }
};

node *merge(node *left, node *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->prior < right->prior) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

pair<node *, node *> split(node *root, int key) {
    if (root == nullptr) return {nullptr, nullptr};

    if (root->key < key) {
        auto sp = split(root->right, key);
        root->right = sp.f;
        return {root, sp.s};
    } else {
        auto sp = split(root->left, key);
        root->left = sp.s;
        return {sp.f, root};
    }
}



int main() {    
}