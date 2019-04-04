////////////////////////////////////////////////////////////////////////////////////////////////
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
ll MOD = 1000000007;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
mt19937 mmtw_(MOD);
uniform_int_distribution<ll> rd_;
ll randomll() { return rd_(mmtw_);}
ll rnd(ll x, ll y) { return rd_(mmtw_) % (y - x + 1) + x; }
template <class T> T fact(T n) { if (n == 1) return 1; return n * fact(n - 1); }
////////////////////////////////////////////////////////////////////////////////////////////////

using base = long double;
base EPS = 1e-12;

struct Vector {
    base x, y, z;
    Vector() : x(0), y(0), z(0) {}
    Vector(base x, base y, base z) : x(x), y(y), z(z) {}
    Vector(const Vector &a) : x(a.x), y(a.y), z(a.z) {}
    Vector(const Vector &a, const Vector &b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}

    base dot(const Vector &a) const {
        return x * a.x + y * a.y + z * a.z;
    }

    Vector cross(const Vector &a) const {
        return Vector(y * a.z - z * a.y,
                      z * a.x - x * a.z,
                      x * a.y - y * a.x);
    }

    base sqr(const Vector &a) const {
        base q = x - a.x;
        base w = y - a.y;
        base e = z - a.z;
        return q * q + w * w + e * e;
    }

    base dist(const Vector &a) const {
        return sqrt(sqr(a));
    }

    base len() const {
        return dist({0, 0, 0});
    }

    Vector operator+=(const Vector &a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return (*this);
    }

    Vector operator-=(const Vector &a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return (*this);
    }

    Vector operator/=(const base &a) {
        x /= a;
        y /= a;
        z /= a;
        return (*this);
    }

    Vector operator*=(const base &a) {
        x *= a;
        y *= a;
        z *= a;
        return (*this);
    }

    Vector normalize() const {
        Vector res = (*this);
        res /= res.len();
        return res;
    }

    void read(istream &in) {
        in >> x >> y >> z;
    }

    void print(ostream &out) const {
        out << x << ' ' << y << ' ' << z << endl;
    }
};

base dot(const Vector &a, const Vector &b) {
    return a.dot(b);
}

Vector cross(const Vector &a, const Vector &b) {
    return a.cross(b);
}

base sqr(const Vector &a, const Vector &b) {
    return a.sqr(b);
}

base dist(const Vector &a, const Vector &b) {
    return a.dist(b);
}

Vector operator+(Vector a, const Vector &b) {
    a += b;
    return a;
}

Vector operator-(Vector a, const Vector &b) {
    a -= b;
    return a;
}

Vector operator/(Vector a, const base b) {
    a /= b;
    return a;
}

Vector operator*(Vector a, const base b) {
    a *= b;
    return a;
}

base len(const Vector &a) {
    return a.len();
}

Vector normalize(const Vector &a) {
    return a.normalize();
}

struct Line {
    Vector a, b;
    Line() {}
    Line(Vector a, Vector b) : a(a), b(b) {}
};

struct Plane {
    base a, b, c, d;
    Vector norm;
    Plane(const Vector &pt, const Vector &norm) : norm(norm) {
        a = norm.x;
        b = norm.y;
        c = norm.z;
        d = dot(norm, pt);
    }
    Plane() {}
};

struct Segment {
    Vector a, b;
};

struct Circle {
    Vector a;
    base r;
    Circle() {}
    Circle(Vector a, base r) : a(a), r(r) {}
};

base dist(const Line &a, const Line &b) {
    Vector v1 = a.b - a.a;
    Vector v2 = b.b - b.a;

    Vector n = cross(v1, v2);
    if (n.x == n.y && n.y == n.z && n.z == 0) {
        n = cross(v1, Vector(a.a, b.a));
        if (n.x == n.y && n.y == n.z && n.z == 0) {
            // cout << "WAT???" << endl;
            return 0;
        }
        n = cross(n, v1);
    }

    n = n.normalize();

    return abs(dot(Vector(a.a, b.a), n));
}

base dist(const Vector &a, const Line &b) {
    base dh = dot(Vector(b.a, b.b), Vector(b.a, a)) / dist(b.a, b.b);
    base dx = dist(b.a, a);
    return sqrt(dx * dx - dh * dh);
}

base dist_log(const Segment &a, const Vector &b, int iter = 1000) {
    ll sz = 1e18;
    Vector p((a.a.x - a.b.x) / sz, (a.a.y - a.b.y) / sz, (a.a.z - a.b.z) / sz);
    base l = 0, r = sz;
    rep(i, iter) {
        base m1 = l + (r - l) / 3;
        base m2 = l + (r - l) / 3 * 2;
        if (dist(b, a.b + p * m1) < dist(b, a.b + p * m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return dist(b, a.b + p * l);
}

base dist_log(const Segment &a, const Segment &b, int iter = 1000) {
    ll sz = 1e18;
    Vector p((a.a.x - a.b.x) / sz, (a.a.y - a.b.y) / sz, (a.a.z - a.b.z) / sz);
    base l = 0, r = sz;
    rep(i, iter) {
        base m1 = l + (r - l) / 3;
        base m2 = l + (r - l) / 3 * 2;
        if (dist_log(b, a.b + p * m1) < dist_log(b, a.b + p * m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return dist_log(b, a.b + p * l);
}

Vector intersect(const Plane &a, const Line &b) {
    if (dot(a.norm, Vector(b.a, b.b)) == 0) {
        // cout << "WAT???" << endl;
        exit(123);
    }

    Vector v(b.a, b.b);
    // U = {b.a + v * t}
    // (n, U) = a.d
    // (n, b.a) + t * (n, v) = a.d
    // t = (a.d - (n, b.a)) / (n, v);
    base t = (a.d - dot(a.norm, b.a)) / dot(a.norm, v);
    return Vector(b.a + v * t);
}

Line intersect(const Plane &a, const Plane &b) {
    if (cross(a.norm, b.norm).len() == 0) { // == 0
        cout << "NO" << endl;
        exit(0);
    }

    Vector dir = cross(a.norm, b.norm);

    Line t({0, 0, 0}, cross(dir, a.norm));
    Vector inter = intersect(b, t);
    Line res(inter, inter + dir);
    return res;
}

pair<base, base> intersect_log(const Line &a, const Circle &b, int iter = 1000) {
    ll sz = 3000000000000LL;
    Vector p = normalize(Vector(a.a, a.b)) / 1000000.0;
    Vector bg = a.a - p * 1000000000000.0;

    base l = 0, r = sz;
    rep(i, iter) {
        base m1 = l + (r - l) / 3;
        base m2 = l + (r - l) / 3 * 2;
        if (dist(bg + p * m1, b.a) < dist(bg + p * m2, b.a)) {
            r = m2;
        } else {
            l = m1;
        }
    }

    base md = l;
    if (dist(bg + p * md, b.a) > b.r) {
        cout << "NO" << endl;
        exit(0);
    }

    // (bg + p * md).print(cout);

    l = md, r = sz;
    rep(i, iter) {
        base m = l + (r - l) / 2;
        if (dist(bg + p * m, b.a) < b.r) {
            l = m;
        } else {
            r = m;
        }
    }

    // cout << "DEB" << endl;
    // Vector p1 = bg + p * (md - (l - md));
    // Vector p2 = bg + p * l;
    // p1.print(cout);
    // p2.print(cout);

    return {md - (l - md), l};
}

Vector c1, c2;
Vector n1, n2;
ld r1, r2;

int main() {
    cout.setf(ios::fixed);
    cout.precision(5);

    c1.read(cin); n1.read(cin); cin >> r1;
    c2.read(cin); n2.read(cin); cin >> r2;

    Plane a(c1, n1);
    Plane b(c2, n2);
    Line line = intersect(a, b);

    // line.a.print(cout); line.b.print(cout);

    Circle ac(c1, r1);
    Circle bc(c2, r2);

    auto ans1 = intersect_log(line, ac);
    auto ans2 = intersect_log(line, bc);

    // cout << ans1.f << ' ' << ans1.s << endl;
    // cout << ans2.f << ' ' << ans2.s << endl;

    if ((ans1.f < ans2.f && ans2.s < ans1.s) ||
        (ans2.f < ans1.f && ans1.s < ans2.s)) {
        cout << "NO" << endl;
        return 0;
    }

    if (min(ans1.f, ans1.s) > max(ans2.f, ans2.s) ||
        min(ans2.f, ans2.s) > max(ans1.f, ans1.s)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}
