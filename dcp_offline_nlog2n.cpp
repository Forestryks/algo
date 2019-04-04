/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */
 
#define VERSION "0.1.5"

#include <cassert>
#include <cstdio>
#include <algorithm>

/** Fast allocation */

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

/** Fast input-output */

template <class T = int> inline T readInt();                        
inline double readDouble();
inline int readUInt();                   
inline int readChar(); // first non-blank character
inline void readWord( char *s ); 
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int getChar(); 
inline int peekChar();
inline bool seekEof();
inline void skipBlanks();

template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

static struct buffer_flusher_t {
    ~buffer_flusher_t() {
        flush();
    }
} buffer_flusher;

/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len)
            return 1;
    }
    return 0;
}

inline int getChar() { 
    return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() { 
    return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() { 
    int c;
    while ((c = peekChar()) != -1 && c <= 32)
        buf_pos++;
    return c == -1;
}

inline void skipBlanks() {
    while (!isEof() && buf[buf_pos] <= 32U)
        buf_pos++;
}

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32)
        c = getChar();
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    else if (c == '+')
        c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    if (c == '.') {
        c = getChar();
        double coef = 1;
        while ('0' <= c && c <= '9')
            x += (c - '0') * (coef *= 1e-1), c = getChar();
    }
    return s == 1 ? x : -x;
}

inline void readWord( char *s ) { 
    int c = readChar();
    while (c > 32)
        *s++ = c, c = getChar();
    *s = 0;
}

inline bool readLine( char *s ) { 
    int c = getChar();
    while (c != '\n' && c != -1)
        *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
    if (write_buf_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
    write_buf[write_buf_pos++] = x;
}

inline void flush() {
    if (write_buf_pos) {
        fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
        fflush(stdout);
    }
}

template <class T> 
inline void writeInt( T x, char end, int output_len ) {
    if (x < 0)
        writeChar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
        s[n++] = '0';
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord( const char *s ) {
    while (*s)
        writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
    if (x < 0)
        writeChar('-'), x = -x;
    int t = (int)x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int)x);
        writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
    writeChar('0' + t);
}

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

const int inf = 2e9;

struct Array {
    int n;
    vector<int> a;
    vector<pii> old;
    vector<int> cnt;

    void init(int sz) {
        n = sz;
        a.assign(sz, 0);
        old.clear();
        cnt.clear();
        cnt.push_back(0);
    }

    void backup() {
        cnt.push_back(0);
    }

    void rollback() {
        if (cnt.empty()) return;
        rep(i, cnt.back()) {
            pii q = old.back();
            a[q.f] = q.s;
            old.pop_back();
        }
        cnt.pop_back();
    }

    inline void set(int i, int x) {
        old.push_back({i, a[i]});
        cnt.back()++;
        a[i] = x;
    }

    inline int get(int i) {
        return a[i];
    }
};

const int MAXN = 3e5 + 5;
int n, m;

Array p;
Array sz;
vector<int> cnt;

void prepareDsu() {
    p.init(n);
    sz.init(n);
    cnt.push_back(n);

    rep(i, n) {
        p.set(i, i);
        sz.set(i, 1);
    }

    p.backup();
    sz.backup();
}

int getDsu(int a) {
    if (a == p.get(a)) return a;
    return getDsu(p.get(a));
}

void mergeDsu(int a, int b) {
    // cout << "mrg " << a << ' ' << b << endl;
    a = getDsu(a);
    b = getDsu(b);
    if (a == b) return;

    cnt.back()--;

    int as = sz.get(a);
    int bs = sz.get(b);

    if (as < bs) {
        p.set(a, b);
    } else if (as > bs) {
        p.set(b, a);
    } else {
        p.set(a, b);
        sz.set(b, as + 1);
    }
}

void backupDsu() {
    // cout << "bkp" << endl;
    p.backup();
    sz.backup();
    cnt.push_back(cnt.back());
}

void rollbackDsu() {
    // cout << "rlb" << endl;
    p.rollback();
    sz.rollback();
    cnt.pop_back();
}

vector<pii> e;
pii q[MAXN];
int right[MAXN];
int left[MAXN];
int pre[MAXN];
int ans[MAXN];

void solve(int l, int r) {
    if (r <= l) return;
    // cout << ": " << l << ' ' << r << endl;
    if (r - l == 1) {
        if (q[l].f != -1) return;
        // for (int i = 0; i < n; ++i) {
        //     cout << p.get(i) << ' ';
        // }
        // cout << endl;

        ans[l] = cnt.back();
        return;
    }

    int m = l + (r - l) / 2;

    backupDsu();

    for (int i = m; i < r; ++i) {
        if (q[i].f == -1 || q[i].f == 0) continue;
        if (left[i] < l) {
            int a = e[q[i].s].f, b = e[q[i].s].s;
            mergeDsu(a, b);
        }
    }

    solve(l, m);
    rollbackDsu();
    backupDsu();

    for (int i = l; i < m; ++i) {
        if (q[i].f == -1 || q[i].f == 1) continue;
        if (right[i] >= r) {
            int a = e[q[i].s].f, b = e[q[i].s].s;
            mergeDsu(a, b);
        }
    }

    solve(m, r);
    rollbackDsu();
}

int main() {
    FAST_IO;
    // cin >> n >> m;
    n = readInt();
    m = readInt();

    if (m == 0) return 0;

    map<pii, int> id;
    int last = 0;
    rep(i, m) {
        char ch = readChar();
        // cin >> ch;
        if (ch == '+' || ch == '-') {
            int a, b;
            // cin >> a >> b;
            a = readInt();
            b = readInt();
            a--; b--;
            if (a > b) swap(a, b);
            if (id.count({a, b})) {
                q[i] = {ch == '-', id[{a, b}]};
            } else {
                id[{a, b}] = last;
                q[i] = {ch == '-', last};
                e.push_back({a, b});
                last++;
            }
        } else {
            q[i] = {-1, 0};
        }
    }

    fill(pre, pre + m, inf);
    fill(right, right + m, inf);

    for (int i = m - 1; i >= 0; --i) {
        if (q[i].f == 1) pre[q[i].s] = i;
        else if (q[i].f == 0) right[i] = pre[q[i].s];
    }

    fill(left, left + m, -inf);

    for (int i = 0; i < m; ++i) {
        if (q[i].f == 0) {
            if (right[i] == inf) continue;
            left[right[i]] = i;
        }
    }

    prepareDsu();

    solve(0, m);


    // for (auto it : e) {
    //     cout << it.f << ' ' << it.s << endl;
    // }
    // cout << endl;

    // rep(i, m) {
    //     cout << q[i].f << ' ' << q[i].s << endl;
    // }

    // cout << endl;

    // rep(i, m) {
    //     cout << right[i] << ' ';
    // }
    // cout << endl;
    // rep(i, m) {
    //     cout << left[i] << ' ';
    // }
    // cout << endl;

    // while (true) {
    //     string s;
    //     cin >> s;
    //     if (s[0] == 'b') {
    //         backupDsu();
    //     } else if (s[0] == 'r') {
    //         rollbackDsu();
    //     } else if (s[0] == 'm') {
    //         int a, b;
    //         cin >> a >> b;
    //         mergeDsu(a, b);
    //     } else {
    //         // int a;
    //         // cin >> a;
    //         // cout << getDsu(a) << endl;
    //         cout << cnt.back() << endl;
    //     }
    // }

    rep(i, m) {
        if (q[i].f == -1) {
            // cout << ans[i] << '\n';
            writeInt(ans[i], '\n');
        }
    }
}
