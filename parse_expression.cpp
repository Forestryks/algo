////////////////////////////////////////////////////////////////////////////////////////////////
// Andrey Odllsov
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define FILE_IO(x) freopen((string(x) + ".in").c_str(), "r", stdin); freopen((string(x) + ".out").c_str(), "w", stdout)
#define sz(x) ((ll)((x).size()))
#define len(x) ((ll)((x).length()))
#define f first
#define s second
#define x1 x1qwer
#define y1 y1qwer
#define foreach(it, v) for (auto it : v)
#define rep(it, n) for (ll it = 0; it < n; ++it)
#define forin(it, l, r) for (ll it = l; it < r; ++it)
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
const ll INF = (1 << 31) - 1;
const ll LINF = (1ll << 63) - 1;
const double DINF = numeric_limits<double>::infinity();
const ll MOD = 1e9 + 7;
const double EPS = 1e-7;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
////////////////////////////////////////////////////////////////////////////////////////////////

char a[1005];
int n;
int pos;
map<string, ll> var;

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

void check(ll pos) {
    if (pos >= n) {
        cout << "WRONG" << endl;
        exit(0);
    }
}

ll sum(int &);
ll mul(int &);

ll number(int &pos) {
    check(pos);
    ll res = 0;
    if (!is_digit(a[pos]) || (a[pos] == '0' && pos < n - 1 && is_digit(a[pos + 1]))) {
        cout << "WRONG" << endl;
        exit(0);
    }
    while (pos < n && is_digit(a[pos])) {
        res *= 10;
        res += a[pos] - '0';
        pos++;
    }
    return res;
}

ll word(int &pos) {
    check(pos);
    string str = "";
    while (pos < n && (a[pos] >= 'a' && a[pos] <= 'z' || a[pos] >= 'A' && a[pos] <= 'Z' || a[pos] == ' ')) {
        str += a[pos];
        pos++;
    }
    if (str == "Podarok") {
        if (pos >= n || a[pos] != '(') {
            cout << "WRONG" << endl;
            exit(0);
        }
        pos++;
        ll res = sum(pos);
        if (pos >= n || a[pos] != ')') {
            cout << "WRONG" << endl;
            exit(0);
        }
        pos++;
        if (res > 0) {
            return res + 5;
        } else {
            return -res;
        }
    } else {
        if (var.count(str) == 0) {
            cout << "WRONG" << endl;
            exit(0);
        } else {
            return var[str];
        }
    }
}

ll sum(int &pos) {
    check(pos);
    ll res = mul(pos);
    while (pos < n) {
        if (a[pos] == '+') {
            pos++;
            res += mul(pos);
        } else if (a[pos] == '-') {
            pos++;
            res -= mul(pos);
        } else {
            return res;
        }
    }
    return res;
}

ll mul(int &pos) {
    check(pos);
    if (a[pos] == '(') {
        pos++;
        ll res = sum(pos);
        if (pos >= n || a[pos] != ')') {
            cout << "WRONG" << endl;
            exit(0);
        }
        pos++;
        if (pos < n && a[pos] == '*') {
            pos++;
            res *= mul(pos);
        }
        return res;
    } else if (a[pos] >= 'a' && a[pos] <= 'z' || a[pos] >= 'A' && a[pos] <= 'Z') {
        ll res = word(pos);
        if (pos < n && a[pos] == '*') {
            pos++;
            res *= mul(pos);
        }
        return res;
    } else {
        ll res = number(pos);
        if (pos < n && a[pos] == '*') {
            pos++;
            res *= mul(pos);
        }
        return res;
    }
}

int main() {
    FAST_IO;
    // FILE_IO("expr");
    var["Ded Moroz"] = 2018;
    var["Moroz"] = -30;
    var["Snegurochka"] = 10;
    while (a[n] = getchar()) {
        if (a[n] == '.') break;
        n++;
    }
    ll res = sum(pos);
    if (pos < n) {
        cout << "WRONG" << endl;
    } else {
        cout << res << endl;
    }
}