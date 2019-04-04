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

struct Complex {
    ld real, imag;
    Complex() {
        real = imag = 0;
    }
    Complex(ld real) : real(real), imag(0) {};
    Complex(ld real, ld imag) : real(real), imag(imag) {};
};

Complex operator+(const Complex &a, const Complex &b) {
    return {a.real + b.real, a.imag + b.imag};
}

Complex operator+=(Complex &a, const Complex &b) {
    a.real += b.real;
    a.imag += b.imag;
    return a;
}

Complex operator-(const Complex &a, const Complex &b) {
    return {a.real - b.real, a.imag - b.imag};
}

Complex& operator-=(Complex &a, const Complex &b) {
    a.real -= b.real;
    a.imag -= b.imag;
    return a;
}

Complex operator*(const Complex &a, const Complex &b) {
    return {a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
}

Complex& operator*=(Complex &a, const Complex &b) {
    a = a * b;
    return a;
}

Complex operator/(const Complex &a, ld b) {
    return {a.real / b, a.imag / b};
}

Complex& operator/=(Complex &a, ld b) {
    a.real /= b;
    a.imag /= b;
    return a;
}

///////////////////////////////////////////////////////////////////////

const int MAXN = 6e5 + 5;

Complex w_len[MAXN];

int inv[MAXN];
void gen_inv(int sz) {
    inv[0] = 0;
    for (unsigned i = 1; i < (1 << sz); ++i) {
        inv[i] = (inv[i >> 1] >> 1) | ((i & 1) << (sz - 1));
    }
}

vector<Complex> fft(const vector<Complex> &a, bool rev) {
    int n = a.size();
    gen_inv(31 - __builtin_clz(n));

    vector<Complex> f(n);
    for (int i = 0; i < n; ++i) {
        f[i] = a[inv[i]];
    }

    for (int len = 1; 2 * len <= n; len *= 2) {
        ld ang = 2 * M_PI / (2 * len);
        if (rev) ang *= -1;

        Complex base(cos(ang), sin(ang));
        w_len[0] = {1, 0};
        for (int i = 1; i <= len; ++i) {
            w_len[i] = w_len[i - 1] * base;
        }

        for (int i = 0; i < n; i += len * 2) {
            for (int j = 0; j < len; ++j) {
                Complex t = f[i + j + len] * w_len[j];
                f[i + j + len] = f[i + j] - t;
                f[i + j] = f[i + j] + t;
            }
        }
    }

    if (rev) {
        for (int i = 0; i < n; ++i) {
            f[i] /= n;
        }
    }

    return f;
}

vector<ll> multiply(const vector<ll> &a_, const vector<ll> &b_) {
    vector<Complex> a(all(a_)), b(all(b_));
    int n = 1;
    while (n < max(a.size(), b.size())) n *= 2;
    n *= 2;

    a.resize(n);
    b.resize(n);

    a = fft(a, false);
    b = fft(b, false);
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] * b[i];
    }

    a = fft(a, true);

    vector<ll> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = round(a[i].real);
    }

    return res;
}

void bigint_read(vector<ll> &a) {
    string s;
    cin >> s;
    reverse(all(s));
    int n = s.size();
    for (int i = 0; i < n; i += 4) {
        string t = s.substr(i, 4);
        reverse(all(t));
        a.push_back(stoi(t));
    }
}

signed main() {
    FAST_IO;

    vector<ll> a;
    vector<ll> b;

    bigint_read(a);
    bigint_read(b);

    if (a.size() == 1 && a[0] == 0 || b.size() == 1 && b[0] == 0) {
        cout << 0 << endl;
        return 0;
    }

    // reverse(all(a));
    // reverse(all(b));

    // cout << "A: ";
    // for (auto it : a) {
    //     cout << it << ' ';
    // }
    // cout << endl;

    // cout << "B: ";
    // for (auto it : b) {
    //     cout << it << ' ';
    // }
    // cout << endl;

    a = multiply(a, b);
    // for (auto it : a) {
    //     cout << it << ' ';
    // }
    // cout << endl;

    int last = a.size() - 1;
    while (last >= 0 and a[last] == 0) {
        last--;
    }
    last++;

    a.erase(a.begin() + last, a.end());

    const ll base = 10000;

    ll carry = 0;
    for (int i = 0; (i < a.size()) || carry; ++i) {
        if (i >= a.size()) {
            a.push_back(carry % base);
            carry /= base;
        } else {
            a[i] += carry;
            carry = a[i] / base;
            a[i] %= base;
        }
    }
    reverse(all(a));


    for (int i = 0; i < a.size(); ++i) {
        string t = to_string(a[i]);
        if (i != 0) {
            reverse(all(t));
            while (t.size() < 4) t.push_back('0');
            reverse(all(t));
        }

        cout << t;
    }
    cout << endl;
}
