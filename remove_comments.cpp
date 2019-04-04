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

#define REGULAR_STATE 0
#define BLOCK_COMMENT 1
#define LINE_COMMENT 2
#define CSTYLE_COMMENT 3
#define AFTER_SLASH 4
#define AFTER_STAR 5

char ch;
int state = 0;

int main() {
    FAST_IO;
    FILE_IO("comments");
    // freopen("comments.in", "r", stdin);
    while ((ch = getchar()) != -1) {
        if (state == REGULAR_STATE) {
            if (ch == '/') state = AFTER_SLASH;
            else if (ch == '{') state = BLOCK_COMMENT;
            else {
                cout << ch;
            }
        } else if (state == BLOCK_COMMENT) {
            if (ch == '}') state = REGULAR_STATE;
        } else if (state == LINE_COMMENT) {
            if (ch == '\n') {
                state = REGULAR_STATE;
                cout << '\n';
            }
        } else if (state == CSTYLE_COMMENT) {
            if (ch == '*') {
                state = AFTER_STAR;
            }
        } else if (state == AFTER_SLASH) {
            if (ch == '/') {
                state = LINE_COMMENT;
            } else if (ch == '*') {
                state = CSTYLE_COMMENT;
            } else if (ch == '{') {
                cout << '/';
                state = BLOCK_COMMENT;
            } else {
                cout << '/' << ch;
                state = REGULAR_STATE;
            }
        } else if (state == AFTER_STAR) {
            if (ch == '/') {
                state = REGULAR_STATE;
            } else if (ch == '*') {
                state = AFTER_STAR;
            } else {
                state = CSTYLE_COMMENT;
            }
        } else {
            return 123;
        }
    }
}