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

struct pt {
    ll x, y;
    pt operator+(pt a) {
        return {x + a.x, y + a.y};
    }
    pt operator-(pt a) {
        return {x - a.x, y - a.y};
    }
    pt operator*(ll k) {
        return {x * k, y * k};
    }
    pt operator-() {
        return {-x, -y};
    }
    bool operator==(pt a) {
        return (x == a.x && y == a.y);
    }
    bool operator!=(pt a) {
        return (x != a.x || y != a.y);
    }
};

ostream &operator<<(ostream &of, pt a) {
    of << "(" << a.x << "," << a.y << ")";
    return of;
}

pt get(pt a, pt b) {
    return b - a;
}

ll cross(pt a, pt b) {
    return a.x * b.y - a.y * b.x;
}

ll dot(pt a, pt b) {
    return a.x * b.x + a.y * b.y;
}

ll half(pt a) {
    return (a.y < 0 || (a.y == 0 && a.x < 0));
}

ll sq(pt a) {
    return dot(a, a);
}

ll orient(pt a, pt b, pt c) {
    return cross(get(a, b), get(a, c));
}

ld abs(pt a) {
    return sqrt(sq(a));
}

ld dist(pt a, pt b) {
    return abs(get(a, b));
}

ll sign(ll x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void cs_print(const vector<pt> &a) {
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i].x << ' ' << a[i].y << ' ' << i << '\n';
    }
    cout << "Polygon\n";
    for (auto &it : a) {
        cout << it.x << ' ' << it.y << '\n';
    }
    cout << "...\n";
}

struct line {
    pt v;
    ll c;

    line(pt v, ll c) : v(v), c(c) {}
    line(ll a, ll b, ll c) : v({b, -a}), c(c) {}
    line(pt a, pt b) : v(get(a, b)), c(cross(v, a)) {}

    ll side(pt a) {
        return cross(v, a) - c;
    }

    ld dist(pt a) {
        return abs(side(a)) / abs(v);
    }

    bool cmp_proj(pt a, pt b) {
        return dot(v, a) < dot(v, b);
    }
};

struct seg {
    pt a, b;

    ld dist(pt p) {
        if (a != b) {
            line l(a, b);
            if (l.cmp_proj(a, p) && l.cmp_proj(p, b)) {
                return l.dist(p);
            }
        }

        return min(abs(get(p, a)), abs(get(p, b)));
    }
};

vector<pt> build_convex(vector<pt> a) {
    int n = a.size();
    rep(i, n) {
        if (make_tuple(a[i].y, a[i].x) < make_tuple(a[0].y, a[0].x)) {
            swap(a[i], a[0]);
        }
    }

    pt o = a[0];
    sort(a.begin() + 1, a.end(), [&](pt a, pt b){
        return make_tuple(orient(o, a, b), sq(a)) < make_tuple(0, sq(b));
    });

    vector<pt> res;
    for (int i = 0; i < a.size(); ++i) {
        while (res.size() >= 2 && orient(res[res.size() - 2], res.back(), a[i]) >= 0) {
            res.pop_back();
        }
        res.push_back(a[i]);
    }
    
    return res;
}

vector<pt> minkowsky(vector<pt> a, vector<pt> b) {
    auto mf = [](vector<pt> &a) {
        int mn = 0;
        rep(i, a.size()) {
            if (a[i].y < a[mn].y || (a[i].y == a[mn].y && a[i].x < a[mn].x)) {
                mn = i;
            }
        }
        rotate(a.begin(), a.begin() + mn, a.end());
    };

    mf(a);
    mf(b);

    a.push_back(a[0]);
    b.push_back(b[0]);

    int n = a.size();
    int m = b.size();

    vector<pt> res;
    res.push_back(a[0] + b[0]);
    int i = 0, j = 0;
    while (i + 1 < n || j + 1 < m) {
        pt nw;
        if (j + 1 == m || cross(get(a[i], a[i + 1]), get(b[j], b[j + 1])) > 0) {
            nw = res.back() + get(a[i], a[i + 1]);
            i++;
        } else {
            nw = res.back() + get(b[j], b[j + 1]);
            j++;
        }
        while (res.size() >= 2 && orient(res[res.size() - 2], res.back(), nw) == 0) {
            res.pop_back();
        }
        res.push_back(nw);
    }

    res.pop_back();

    return res;
}

bool convex_inside(const vector<pt> &a, pt p) {
    int n = a.size();
    if (cross(get(a[0], a[n - 1]), get(a[0], p)) > 0 || cross(get(a[0], a[1]), get(a[0], p)) < 0) return false;
    if (cross(get(a[0], a[1]), get(a[0], p)) == 0) {
        return sq(get(a[0], p)) <= sq(get(a[0], a[1]));
    }

    int i = lower_bound(a.begin() + 1, a.end(), p, [&](pt p, pt q){
        return cross(get(a[0], p), get(a[0], q)) > 0;
    }) - a.begin();

    return orient(a[i - 1], a[i], p) >= 0;
}

pii find_tangents(const vector<pt> &a, pt p) {
    // assert(!convex_inside(a, p));
    int n = a.size();

    auto f = [](ll x) {
        return sign(x) <= 0;
    };

    pii ans;

    bool s = f(orient(p, a[0], a[1]));
    int l = 0, r = n - 1;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        bool t = f(orient(p, a[m], a[(m + 1) % n]));
        if (s != t) {
            r = m;
        } else {
            if (f(orient(p, a[0], a[m])) == s) {
                l = m;
            } else {
                r = m;
            }
        }
    }
    ans.f = r;

    l = r;
    r = n;
    s = f(orient(p, a[l], a[(l + 1) % n]));
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        bool t = f(orient(p, a[m], a[(m + 1) % n]));
        if (s != t) {
            r = m;
        } else {
            l = m;
        }
    }
    ans.s = r % n;

    if (orient(p, a[ans.f], a[ans.s]) > 0) swap(ans.f, ans.s);
    return ans;
}

int main() {

}
