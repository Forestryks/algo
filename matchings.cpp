#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define rep(i, n) for (int (i) = 0; (i) < (n); ++(i))
#define all(x) (x).begin(), (x).end()
#define f first
#define s second
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define left left123
#define right right123
#define timed(x) clock_t c_start = clock(); while (1000.0 * (clock() - c_start) / CLOCKS_PER_SEC < x)

#define FAST_ALLOCATOR_MEMORY 10000000
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
    long long t = (long long)x;
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

namespace rnd {
    random_device rd;
    mt19937 mt(rd());
};

const int MAXN = 250;
int n, m;
vector<int> g[MAXN];
int tt = 1;
int last[MAXN];
int mt[MAXN];

unsigned int g_seed;
int fastrand() { 
    g_seed = (214013 * g_seed + 2531011); 
    return (g_seed >> 16) & 0x7FFF;
}

int notsofast() {
    return (fastrand() << 15) + fastrand();
}

int rndi() {
    return fastrand();
    // return mmtw_();
    // return notsofast();
}

int r2(int n) {
    return rndi() & (n - 1);
}

template <class T>
void shfl(vector<T> &a, int c) {
    // rep(i, a.size()) {
    //  swap(a[i], a[r(i + 1)]);
    // }

    if (r2(c) == 0) {
        int n = a.size();
        rep(i, n) {
            swap(a[i], a[r2(n)]);
        }
    } else {
        int n = a.size();
        rep(i, n - 1) {
            swap(a[i], a[i + 1]);
        }
    }
}

bool dfs(int v) {
    last[v] = tt;
    for (auto to : g[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            mt[v] = to;
            return true;
        }
        if (last[mt[to]] == tt) continue;
        int sv = mt[to];
        mt[v] = to;
        mt[to] = v;
        mt[sv] = -1;
        if (dfs(sv)) return true;
        mt[sv] = to;
        mt[to] = sv;
        mt[v] = -1;
    }
    return false;
}

void build_matching() {
    fill(mt, mt + n, -1);

    vector<int> p(n);
    rep(i, n) {
        p[i] = i;
    }

    int cnt = 0;
    timed(8) {
        cnt++;
        // shuffle(all(p), rnd::mt);
        // rep(i, n) {
        //     shuffle(all(g[i]), rnd::mt);
        // }
        shfl(p, 1);
        rep(i, n) {
            shfl(g[i], 4);
        }
        rep(i, n) {
            int v = p[i];
            if (mt[v] != -1) continue;
            tt++;
            dfs(v);
        }
    }
    // cout << "iters " << cnt << endl;
}

int main() {
    FAST_IO;
    n = readInt();
    m = readInt();
    rep(i, m) {
        int u = readInt();
        int v = readInt();
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_matching();
    
    vector<pii> res;
    rep(i, n) {
        if (mt[i] > i) {
            res.push_back({i, mt[i]});
        }
    }

    if (res.size() * 2 == n) {
        writeWord("YES\n");
    } else {
        writeWord("NO\n");
    }

    // writeInt(res.size() * 2, '\n');
    // for (auto it : res) {
    //     writeInt(it.f + 1, ' ');
    //     writeInt(it.s + 1, '\n');
    // }
}
