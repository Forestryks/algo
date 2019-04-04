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
uniform_int_distribution<int> rdi_;
ll randomll() { return rd_(mmtw_);}
int randto(int x) {return rdi_(mmtw_) % x;}
ll rnd(ll x, ll y) { return rd_(mmtw_) % (y - x + 1) + x; }
////////////////////////////////////////////////////////////////////////////////////////////////

const int MAXN = 505;
int n;
int a[MAXN][MAXN];
int u[MAXN], v[MAXN];
int minval[MAXN], minpos[MAXN];
bool r[MAXN], c[MAXN];
int rowp[MAXN], colp[MAXN];
int pr[MAXN];

int main() {
    FILE_IO("assignment");
    FAST_IO;
    cin >> n;
    rep(i, n) {
        rep(j, n) {
            cin >> a[i][j];
        }
    }


    /* Находим минимальный элемент и вычитаем его из каждой строки */
    int mn = INT_MAX;
    rep(i, n) {
        rep(j, n) {
            mn = min(a[i][j], mn);
        }
    }
    rep(i, n) {
        u[i] -= mn;
    }

    /* Помечаем, что каждый столбец ни с чем не связан */
    rep(j, n) {
        pr[j] = -1;
    }

    /* По очереди добавляем строки */
    for (int i = 0; i < n; ++i) {
        /* Помечаем, что все строки не красные */
        for (int j = 0; j <= i; ++j) {
            colp[j] = -1;
            rowp[j] = -1;
            r[j] = false;
        }
        /* Помечаем, что все столбцы не оранжевые */
        for (int j = 0; j < n; ++j) {
            c[j] = false;
        }

        /* i-я строка красная */
        r[i] = true;
        /* Инициализируем минимумы в столбцах */
        for (int j = 0; j < n; ++j) {
            minval[j] = a[i][j] + u[i] + v[j];
            minpos[j] = i;
        }

        /* Ищем цепочку */
        while (true) {
            /* Ищем минимальный элемент среди красных строк и не оранжевых столбцов */
            int mn = INT_MAX, ps;
            for (int j = 0; j < n; ++j) {
                if (c[j]) continue;
                if (minval[j] < mn) {
                    mn = minval[j];
                    ps = j;
                }
            }

            /* Вычитаем из красных строк */
            for (int j = 0; j <= i; ++j) {
                if (r[j]) u[j] -= mn;
            }
            /* Прибавляем к оранжевым столбцам и обновляем minval*/
            for (int j = 0; j < n; ++j) {
                if (c[j]) v[j] += mn;
                else minval[j] -= mn;
            }

            /* Если столбец уже занят, то идем дальше */
            if (pr[ps] != -1) {
                int row = pr[ps];
                /* Откуда пришли */
                rowp[pr[ps]] = minpos[ps];
                colp[pr[ps]] = ps;

                /* Помечаем строку и столбец */
                r[row] = true;
                c[ps] = true;

                /* Обновляем minpos, minval */
                for (int j = 0; j < n; ++j) {
                    if (!c[j] && a[row][j] + u[row] + v[j] < minval[j]) {
                        minval[j] = a[row][j] + u[row] + v[j];
                        minpos[j] = row;
                    }
                }
            } else {
                /* Profit! */
                int i = minpos[ps];
                pr[ps] = i;

                while (rowp[i] != -1) {
                    pr[colp[i]] = rowp[i];
                    i = rowp[i];
                }
                break;
            }
        }

        // cout << "After " << i << endl;
        // rep(i, n) {
        //  cout << pr[i] << ' ';
        // }
        // cout << endl;
    }

    int sum = 0;
    rep(i, n) {
        sum += a[pr[i]][i];
    }

    cout << sum << '\n';
    rep(i, n) {
        cout << pr[i] + 1 << ' ' << i + 1 << '\n';
    }
}
