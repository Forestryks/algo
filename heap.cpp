///////////////////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;

// #define int long long

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
typedef double ld;
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

void siftUp(vector<ll> &a, int v) {
    int n = a.size();
    while (v > 1 && a[v] < a[v >> 1]) {
        swap(a[v], a[v >> 1]);
        v >>= 1;
    }
}

void siftDown(vector<ll> &a, int v) {
    int n = a.size();

    while ((v << 1) < n) {
        int l = (v << 1);
        int r = l + 1;
        if (r < n && a[r] < a[l] && a[r] < a[v]) {
            swap(a[v], a[r]);
            v = r;
        } else if (a[l] < a[v]) {
            swap(a[l], a[v]);
            v = l;
        } else {
            break;
        }
    }
}

void heapPush(vector<ll> &a, ll x) {
    a.push_back(x);
    siftUp(a, a.size() - 1);
}

ll heapMin(vector<ll> &a) {
    return a[1];
}

ll heapPop(vector<ll> &a) {
    swap(a[1], a.back());
    ll res = a.back();
    a.pop_back();
    siftDown(a, 1);
    return res;
}

vector<ll> a;

int main() {
    // FILE_IO("heap");
    FAST_IO;
    string s;
    a = {0};
    while (cin >> s) {
        if (s == "MIN") {
            cout << "MIN: " << heapMin(a) << '\n';
        } else if (s == "ADD") {
            ll x;
            cin >> x;
            heapPush(a, x);
            cout << "SIZE: " << a.size() - 1 << '\n';
        } else {
            cout << "POP: " << heapPop(a);
            cout << " SIZE: " << a.size() - 1 << '\n';
        }
    }
}