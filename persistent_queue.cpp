
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
mt19937 mmtw_(MOD);
uniform_int_distribution<ll> rd_;
ll randomll() { return rd_(mmtw_);}
ll rnd(ll x, ll y) { return rd_(mmtw_) % (y - x + 1) + x; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 2e5 + 5;

struct Node {
    int val;
    Node *l, *r;
    Node() {
        val = 0;
        l = r = nullptr;
    }
    Node(Node *a) {
        l = a->l;
        r = a->r;
        val = a->val;
    }
};

Node *build(int tl, int tr) {
    if (tr <= tl) return nullptr;
    if (tr - tl == 1) return new Node();

    Node *a = new Node();

    int tm = tl + (tr - tl) / 2;
    a->l = build(tl, tm);
    a->r = build(tm, tr);
    return a;
}

Node *update(Node *v, int tl, int tr, int pos, int x) {
    v = new Node(v);
    if (tr - tl == 1) {
        v->val = x;
    } else {
        int tm = tl + (tr - tl) / 2;
        if (pos < tm) {
            v->l = update(v->l, tl, tm, pos, x);
        } else {
            v->r = update(v->r, tm, tr, pos, x);
        }
    }
    return v;
}

int get(Node *v, int tl, int tr, int pos) {
    if (tr - tl == 1) {
        return v->val;
    }

    int tm = tl + (tr - tl) / 2;
    if (pos < tm) {
        return get(v->l, tl, tm, pos);
    } else {
        return get(v->r, tm, tr, pos);
    }
}

struct Array {
    vector<Node*> ver;
    Array() {
        Node *v = build(0, MAXN);
        ver.push_back(v);
    }
    
    int get(int v, int pos) {
        return ::get(ver[v], 0, MAXN, pos);
    }

    void set(int v, int pos, int x) {
        ver.push_back(update(ver[v], 0, MAXN, pos, x));
    }
};

struct Queue {
    vector<Node*> ver;
    vector<int> begin;
    vector<int> end;
    Queue() {
        Node *v = build(0, MAXN);
        ver.push_back(v);
        begin.push_back(0);
        end.push_back(0);
    }

    int pop(int v) {
        begin.push_back(begin[v] + 1);
        end.push_back(end[v]);
        ver.push_back(ver[v]);
        return ::get(ver[v], 0, MAXN, begin[v]);
    }

    void push(int v, int x) {
        begin.push_back(begin[v]);
        end.push_back(end[v] + 1);
        ver.push_back(update(ver[v], 0, MAXN, end[v], x));
    }
};

int main() {
    // Array a;
    // while (true) {
    //     char ch;
    //     cin >> ch;
    //     if (ch == 'U') {
    //         int ver, pos, x;
    //         cin >> ver >> pos >> x;
    //         a.set(ver, pos, x);
    //     } else {
    //         int ver, pos;
    //         cin >> ver;
    //         // cout << a.get(ver, pos) << endl;
    //         rep(i, 6) {
    //             cout << a.get(ver, i) << ' ';
    //         }
    //         cout << endl;
    //     }
    // }
    Queue a;
    int n = readInt();
    // cin >> n;
    rep(i, n) {
        int t = readInt();
        // cin >> t;
        // cerr << t << endl;
        if (t == 1) {
            int v, x;
            // cin >> v >> x;
            v = readInt();
            x = readInt();
            a.push(v, x);
        } else {
            int v = readInt();
            // cin >> v;
            // cout << a.pop(v) << '\n';
            writeInt(a.pop(v), '\n');
        }
    }
}