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

const int MAXN = 400005;

struct suffix {
    int id;
    int rank[2];
};

void countingSort(vector<suffix> &a, int ind) {
    int n = a.size();
    vector<suffix> res(n);
    vector<int> count(MAXN);

    for (int i = 0; i < n; ++i) {
        count[a[i].rank[ind]]++;
    }

    for (int i = 1; i < MAXN; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        res[count[a[i].rank[ind]] - 1] = a[i];
        count[a[i].rank[ind]]--;
    }

    for (int i = 0; i < n; ++i) {
        a[i] = res[i];
    }
}

void radixSort(vector<suffix> &a) {
    countingSort(a, 1);
    countingSort(a, 0);
}

vector<int> buildSuffixArray(const string &a) {
    int n = a.size();

    vector<suffix> suf(n);

    for (int i = 0; i < n; ++i) {
        suf[i].id = i;
        suf[i].rank[0] = a[i];
        if (i + 1 >= n) suf[i].rank[1] = 0;
        else suf[i].rank[1] = a[i + 1];
    }

    radixSort(suf);

    vector<int> id(n);
    for (int k = 2; k < n; k *= 2) {
        int rank = 1;
        int prev = suf[0].rank[0];
        suf[0].rank[0] = 1;
        id[suf[0].id] = 0;

        for (int i = 1; i < n; ++i) {
            if (suf[i].rank[0] == prev && suf[i].rank[1] == suf[i - 1].rank[1]) {
                suf[i].rank[0] = rank;
            } else {
                prev = suf[i].rank[0];
                suf[i].rank[0] = ++rank;
            }
            id[suf[i].id] = i;
        }

        for (int i = 0; i < n; ++i) {
            int next = suf[i].id + k;
            if (next >= n) suf[i].rank[1] = 0;
            else suf[i].rank[1] = suf[id[next]].rank[0];
        }

        radixSort(suf);
    }

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = suf[i].id;
    }
    return ans;
}

vector<int> buildLCP(const vector<int> &suf, const string &a) {
    int n = a.size();
    vector<int> res(n);
    vector<int> p(n);

    for (int i = 0; i < n; ++i) {
        p[suf[i]] = i;
    }

    int k = 0;
    for (int i = 0; i < n; ++i) {
        k = max(0, k - 1);
        if (p[i] == n - 1) {
            res[n - 1] = 0;
            k = 0;
        } else {
            int j = suf[p[i] + 1];
            while (max(i + k, j + k) < n && a[i + k] == a[j + k]) {
                k++;
            }
            res[p[i]] = k;
        }
    }
    return res;
}

int main() {
    FILE_IO("array");
    string s;
    cin >> s;

    auto suf = buildSuffixArray(s);
    auto lcp = buildLCP(suf, s);

    rep(i, s.size()) {
        if (i != 0) cout << ' ';
        cout << suf[i] + 1;
    }
    cout << endl;
    rep(i, int(s.size()) - 1) {
        cout << lcp[i] << ' ';
    }
    cout << endl;
}
