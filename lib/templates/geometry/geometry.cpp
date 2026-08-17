namespace geo {
using ld = long double;
using i128 = __int128_t;

const ld EPS = 1e-12L;
const ld PI = acosl(-1.0L);

template<class T>
struct Point {
    T x, y;

    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    template<class U> explicit Point(const Point<U> &p) : x(p.x), y(p.y) {}

    Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator*(T k) const { return {x * k, y * k}; }
    Point operator/(T k) const { return {x / k, y / k}; }
    Point& operator+=(const Point &p) { x += p.x, y += p.y; return *this; }
    Point& operator-=(const Point &p) { x -= p.x, y -= p.y; return *this; }
    Point& operator*=(T k) { x *= k, y *= k; return *this; }
    Point& operator/=(T k) { x /= k, y /= k; return *this; }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point &p) const { return !(*this == p); }
    bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
};

template<class T> Point<T> operator*(T k, const Point<T> &p) { return p * k; }
template<class T> istream& operator>>(istream &in, Point<T> &p) { return in >> p.x >> p.y; }
template<class T> ostream& operator<<(ostream &out, const Point<T> &p) { return out << p.x << ' ' << p.y; }

using P = Point<int>;
using FP = Point<ld>;

template<class T> using Wide = conditional_t<is_integral_v<T>, i128, ld>;

template<class T> Wide<T> dot(const Point<T> &a, const Point<T> &b) {
    return (Wide<T>)a.x * b.x + (Wide<T>)a.y * b.y;
}
template<class T> Wide<T> cross(const Point<T> &a, const Point<T> &b) {
    return (Wide<T>)a.x * b.y - (Wide<T>)a.y * b.x;
}
template<class T> Wide<T> cross(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return ((Wide<T>)b.x - a.x) * ((Wide<T>)c.y - a.y)
         - ((Wide<T>)b.y - a.y) * ((Wide<T>)c.x - a.x);
}
template<class T> Wide<T> dot(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    return ((Wide<T>)b.x - a.x) * ((Wide<T>)c.x - a.x)
         + ((Wide<T>)b.y - a.y) * ((Wide<T>)c.y - a.y);
}
template<class T> Wide<T> dist2(const Point<T> &a, const Point<T> &b) {
    Wide<T> x = (Wide<T>)a.x - b.x, y = (Wide<T>)a.y - b.y;
    return x * x + y * y;
}
template<class T> int sgn(T x) {
    if constexpr(is_floating_point_v<T>) return (x > EPS) - (x < -EPS);
    else return (x > 0) - (x < 0);
}

ld norm(const FP &p) { return sqrtl(dot(p, p)); }
ld dist(const FP &a, const FP &b) { return norm(a - b); }
FP unit(const FP &p) { return p / norm(p); }
template<class T> Point<T> perp(const Point<T> &p) { return {-p.y, p.x}; }
FP rotate(const FP &p, ld a) { return {p.x * cosl(a) - p.y * sinl(a), p.x * sinl(a) + p.y * cosl(a)}; }
ld angle(const FP &p) { return atan2l(p.y, p.x); }
ld angle(const FP &a, const FP &b) { return atan2l(cross(a, b), dot(a, b)); }
FP to_fp(const P &p) { return {(ld)p.x, (ld)p.y}; }
bool equal(ld a, ld b) { return fabsl(a - b) <= EPS; }
bool equal(const FP &a, const FP &b) { return dist2(a, b) <= EPS * EPS; }
ld clamp_unit(ld x) { return max(-1.0L, min(1.0L, x)); }
template<class T> int polar_half(const Point<T> &p) {
    return p.y > 0 || (p.y == 0 && p.x >= 0) ? 0 : 1;
}
template<class T> bool polar_less(const Point<T> &a, const Point<T> &b) {
    if(polar_half(a) != polar_half(b)) return polar_half(a) < polar_half(b);
    auto c = cross(a, b);
    return c != 0 ? c > 0 : dot(a, a) < dot(b, b);
}

struct Line {
    FP p, v;
    Line() {}
    Line(FP _p, FP _v) : p(_p), v(_v) {}
    static Line through(FP a, FP b) { return {a, b - a}; }
};

int side(const Line &l, const FP &p) { return sgn(cross(l.v, p - l.p)); }
FP projection(const Line &l, const FP &p) { return l.p + l.v * (dot(p - l.p, l.v) / dot(l.v, l.v)); }
FP reflection(const Line &l, const FP &p) { return projection(l, p) * 2 - p; }
ld distance_line(const Line &l, const FP &p) { return fabsl(cross(l.v, p - l.p)) / norm(l.v); }

// nullopt means parallel or coincident.
optional<FP> line_intersection(const Line &a, const Line &b) {
    ld d = cross(a.v, b.v);
    if(sgn(d) == 0) return nullopt;
    return a.p + a.v * (cross(b.p - a.p, b.v) / d);
}

template<class T>
bool on_segment(const Point<T> &p, const Point<T> &a, const Point<T> &b) {
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p, a, b)) <= 0;
}
template<class T>
bool on_ray(const Point<T> &p, const Point<T> &a, const Point<T> &b) {
    return sgn(cross(a, b, p)) == 0 && sgn(dot(a, p, b)) >= 0;
}
template<class T>
bool segments_intersect(const Point<T> &a, const Point<T> &b, const Point<T> &c, const Point<T> &d) {
    int ab_c = sgn(cross(a, b, c)), ab_d = sgn(cross(a, b, d));
    int cd_a = sgn(cross(c, d, a)), cd_b = sgn(cross(c, d, b));
    if(ab_c == 0 && on_segment(c, a, b)) return true;
    if(ab_d == 0 && on_segment(d, a, b)) return true;
    if(cd_a == 0 && on_segment(a, c, d)) return true;
    if(cd_b == 0 && on_segment(b, c, d)) return true;
    return ab_c * ab_d < 0 && cd_a * cd_b < 0;
}

// Returns zero, one, or two endpoints of the intersection.
vector<FP> segment_intersection(FP a, FP b, FP c, FP d) {
    vector<FP> res;
    for(FP p : {a, b}) if(on_segment(p, c, d)) res.pb(p);
    for(FP p : {c, d}) if(on_segment(p, a, b)) res.pb(p);
    sort(all(res));
    res.erase(unique(all(res), [](const FP &p, const FP &q) { return equal(p, q); }), res.end());
    if(sz(res)) {
        if(sz(res) > 2) res = {res.front(), res.back()};
        return res;
    }
    auto p = line_intersection(Line::through(a, b), Line::through(c, d));
    if(p && on_segment(*p, a, b) && on_segment(*p, c, d)) res.pb(*p);
    return res;
}

ld distance_segment(const FP &p, const FP &a, const FP &b) {
    if(equal(a, b)) return dist(p, a);
    ld t = max(0.0L, min(1.0L, dot(p - a, b - a) / dot(b - a, b - a)));
    return dist(p, a + (b - a) * t);
}
ld distance_segments(const FP &a, const FP &b, const FP &c, const FP &d) {
    if(segments_intersect(a, b, c, d)) return 0;
    return min({distance_segment(a, c, d), distance_segment(b, c, d),
                distance_segment(c, a, b), distance_segment(d, a, b)});
}

// -1 outside, 0 boundary, 1 inside.
template<class T>
int point_in_triangle(const Point<T> &p, const Point<T> &a, const Point<T> &b, const Point<T> &c) {
    int x = sgn(cross(a, b, p)), y = sgn(cross(b, c, p)), z = sgn(cross(c, a, p));
    if((x < 0 || y < 0 || z < 0) && (x > 0 || y > 0 || z > 0)) return -1;
    return x == 0 || y == 0 || z == 0 ? 0 : 1;
}

ld triangle_area(FP a, FP b, FP c) { return fabsl(cross(a, b, c)) / 2; }
optional<FP> circumcenter(FP a, FP b, FP c) {
    FP u = b - a, v = c - a;
    ld d = 2 * cross(u, v);
    if(sgn(d) == 0) return nullopt;
    return a + FP{dot(u, u) * v.y - dot(v, v) * u.y,
                  dot(v, v) * u.x - dot(u, u) * v.x} / d;
}
FP incenter(FP a, FP b, FP c) {
    ld x = dist(b, c), y = dist(c, a), z = dist(a, b);
    return (a * x + b * y + c * z) / (x + y + z);
}
optional<FP> orthocenter(FP a, FP b, FP c) {
    auto o = circumcenter(a, b, c);
    if(!o) return nullopt;
    return a + b + c - *o * 2;
}

struct Circle {
    FP o;
    ld r;
};

bool contains(const Circle &c, const FP &p) { return dist2(c.o, p) <= c.r * c.r + EPS; }
Circle circumcircle(FP a, FP b, FP c) {
    auto o = circumcenter(a, b, c);
    assert(o);
    return {*o, dist(*o, a)};
}
Circle incircle(FP a, FP b, FP c) {
    FP o = incenter(a, b, c);
    return {o, distance_line(Line::through(a, b), o)};
}

vector<FP> line_circle_intersection(const Line &l, const Circle &c) {
    FP h = projection(l, c.o);
    ld d2 = dist2(h, c.o), r2 = c.r * c.r;
    if(d2 > r2 + EPS) return {};
    if(equal(d2, r2)) return {h};
    FP v = unit(l.v) * sqrtl(max(0.0L, r2 - d2));
    return {h - v, h + v};
}
vector<FP> segment_circle_intersection(FP a, FP b, const Circle &c) {
    vector<FP> res;
    for(FP p : line_circle_intersection(Line::through(a, b), c))
        if(on_segment(p, a, b)) res.pb(p);
    return res;
}
vector<FP> circle_intersection(const Circle &a, const Circle &b) {
    FP d = b.o - a.o;
    ld d2 = dot(d, d);
    if(d2 <= EPS * EPS) return {};
    ld x = (d2 + a.r * a.r - b.r * b.r) / (2 * sqrtl(d2));
    ld h2 = a.r * a.r - x * x;
    if(h2 < -EPS) return {};
    FP p = a.o + d * (x / sqrtl(d2));
    if(h2 <= EPS) return {p};
    FP q = perp(d) * (sqrtl(max(0.0L, h2)) / sqrtl(d2));
    return {p - q, p + q};
}

vector<FP> tangents_from_point(const Circle &c, const FP &p) {
    FP d = p - c.o;
    ld d2 = dot(d, d), h2 = d2 - c.r * c.r;
    if(h2 < -EPS || d2 <= EPS * EPS) return {};
    if(h2 <= EPS) return {c.o + d * (c.r * c.r / d2)};
    FP q = perp(d) * (c.r * sqrtl(h2) / d2);
    FP m = c.o + d * (c.r * c.r / d2);
    return {m - q, m + q};
}

// Each pair gives one tangent line through its touching points.
vector<pair<FP, FP>> common_tangents(const Circle &a, const Circle &b) {
    vector<pair<FP, FP>> res;
    FP d = b.o - a.o;
    ld d2 = dot(d, d);
    if(d2 <= EPS * EPS) return res;
    for(int s : {-1LL, 1LL}) {
        ld r = a.r - s * b.r, h2 = d2 - r * r;
        if(h2 < -EPS) continue;
        for(int t : {-1LL, 1LL}) {
            if(h2 <= EPS && t == 1) continue;
            FP v = (d * r + perp(d) * (sqrtl(max(0.0L, h2)) * t)) / d2;
            res.eb(a.o + v * a.r, b.o + v * (s * b.r));
        }
    }
    return res;
}

ld circle_overlap_area(const Circle &a, const Circle &b) {
    ld d = dist(a.o, b.o);
    if(d >= a.r + b.r - EPS) return 0;
    if(d <= fabsl(a.r - b.r) + EPS) {
        ld r = min(a.r, b.r);
        return PI * r * r;
    }
    ld x = acosl(clamp_unit((d * d + a.r * a.r - b.r * b.r) / (2 * d * a.r)));
    ld y = acosl(clamp_unit((d * d + b.r * b.r - a.r * a.r) / (2 * d * b.r)));
    ld z = sqrtl(max(0.0L, (-d + a.r + b.r) * (d + a.r - b.r)
                               * (d - a.r + b.r) * (d + a.r + b.r))) / 2;
    return a.r * a.r * x + b.r * b.r * y - z;
}

// O(n^2 log n) area covered by at least one circle.
ld circle_union_area(const vector<Circle> &c) {
    ld res = 0;
    for(int i = 0; i < sz(c); i++) {
        if(c[i].r <= EPS) continue;
        bool covered = false;
        vector<pair<ld, ld>> seg;
        for(int j = 0; j < sz(c); j++) if(i != j) {
            ld d = dist(c[i].o, c[j].o);
            if(d + c[i].r <= c[j].r + EPS &&
               (d + c[i].r < c[j].r - EPS || i > j)) {
                covered = true;
                break;
            }
            if(d >= c[i].r + c[j].r - EPS || d + c[j].r <= c[i].r + EPS) continue;
            ld a = angle(c[j].o - c[i].o);
            ld x = acosl(clamp_unit((c[i].r * c[i].r + d * d - c[j].r * c[j].r)
                                    / (2 * c[i].r * d)));
            ld l = a - x, r = a + x;
            while(l < 0) l += 2 * PI, r += 2 * PI;
            while(l >= 2 * PI) l -= 2 * PI, r -= 2 * PI;
            if(r <= 2 * PI) seg.eb(l, r);
            else seg.eb(l, 2 * PI), seg.eb(0, r - 2 * PI);
        }
        if(covered) continue;
        sort(all(seg));
        vector<pair<ld, ld>> merged;
        for(auto [l, r] : seg) {
            if(merged.empty() || l > merged.back().second + EPS) merged.eb(l, r);
            else merged.back().second = max(merged.back().second, r);
        }
        ld last = 0;
        auto add_arc = [&](ld l, ld r) {
            res += (c[i].r * c[i].r * (r - l)
                    + c[i].r * (c[i].o.x * (sinl(r) - sinl(l))
                              - c[i].o.y * (cosl(r) - cosl(l)))) / 2;
        };
        for(auto [l, r] : merged) {
            if(last < l) add_arc(last, l);
            last = max(last, r);
        }
        if(last < 2 * PI) add_arc(last, 2 * PI);
    }
    return res;
}

ld sector_area(const FP &a, const FP &b, ld r) { return r * r * angle(a, b) / 2; }
ld circle_triangle_intersection(FP a, FP b, ld r) {
    FP d = b - a;
    ld A = dot(d, d), B = 2 * dot(a, d), C = dot(a, a) - r * r;
    vector<ld> t = {0, 1};
    ld D = B * B - 4 * A * C;
    if(A > EPS && D > EPS) {
        ld s = sqrtl(D);
        for(ld x : {(-B - s) / (2 * A), (-B + s) / (2 * A)})
            if(x > EPS && x < 1 - EPS) t.pb(x);
    }
    sort(all(t));
    ld res = 0;
    for(int i = 0; i + 1 < sz(t); i++) {
        FP p = a + d * t[i], q = a + d * t[i + 1];
        FP m = a + d * ((t[i] + t[i + 1]) / 2);
        res += dot(m, m) < r * r - EPS ? cross(p, q) / 2 : sector_area(p, q, r);
    }
    return res;
}

// Area inside both the circle and polygon.
ld circle_polygon_intersection(const Circle &c, const vector<FP> &p) {
    ld res = 0;
    for(int i = 0; i < sz(p); i++)
        res += circle_triangle_intersection(p[i] - c.o, p[(i + 1) % sz(p)] - c.o, c.r);
    return fabsl(res);
}

Circle circle_from_diameter(FP a, FP b) { return {(a + b) / 2, dist(a, b) / 2}; }
Circle circle_from_three(FP a, FP b, FP c) {
    auto o = circumcenter(a, b, c);
    if(o) return {*o, dist(*o, a)};
    Circle res = circle_from_diameter(a, b);
    for(auto [x, y] : vector<pair<FP, FP>>{{a, c}, {b, c}}) {
        Circle cur = circle_from_diameter(x, y);
        if(cur.r > res.r) res = cur;
    }
    return res;
}

// Expected O(n). Points are shuffled.
Circle minimum_enclosing_circle(vector<FP> p) {
    if(p.empty()) return {{0, 0}, 0};
    shuffle(all(p), rng);
    Circle c{p[0], 0};
    for(int i = 0; i < sz(p); i++) if(!contains(c, p[i])) {
        c = {p[i], 0};
        for(int j = 0; j < i; j++) if(!contains(c, p[j])) {
            c = circle_from_diameter(p[i], p[j]);
            for(int k = 0; k < j; k++) if(!contains(c, p[k]))
                c = circle_from_three(p[i], p[j], p[k]);
        }
    }
    return c;
}

template<class T> Wide<T> area2(const vector<Point<T>> &p) {
    Wide<T> res = 0;
    for(int i = 0; i < sz(p); i++) res += cross(p[i], p[(i + 1) % sz(p)]);
    return res;
}
ld polygon_area(const vector<FP> &p) { return fabsl(area2(p)) / 2; }
ld polygon_perimeter(const vector<FP> &p) {
    ld res = 0;
    for(int i = 0; i < sz(p); i++) res += dist(p[i], p[(i + 1) % sz(p)]);
    return res;
}
FP polygon_centroid(const vector<FP> &p) {
    ld a = 0;
    FP res{0, 0};
    for(int i = 0; i < sz(p); i++) {
        ld c = cross(p[i], p[(i + 1) % sz(p)]);
        a += c;
        res += (p[i] + p[(i + 1) % sz(p)]) * c;
    }
    assert(sgn(a) != 0);
    return res / (3 * a);
}

// -1 outside, 0 boundary, 1 inside. Polygon may be concave.
template<class T>
int point_in_polygon(const vector<Point<T>> &p, const Point<T> &q) {
    bool inside = false;
    for(int i = 0; i < sz(p); i++) {
        Point<T> a = p[i], b = p[(i + 1) % sz(p)];
        if(on_segment(q, a, b)) return 0;
        if((a.y > q.y) != (b.y > q.y))
            if((b.y > a.y) == (sgn(cross(a, b, q)) > 0)) inside = !inside;
    }
    return inside ? 1 : -1;
}

// Removes collinear boundary points unless keep_collinear is true.
template<class T>
vector<Point<T>> convex_hull(vector<Point<T>> p, bool keep_collinear = false) {
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    if(sz(p) <= 1) return p;
    vector<Point<T>> h;
    auto bad = [&](const Point<T> &a, const Point<T> &b, const Point<T> &c) {
        int s = sgn(cross(a, b, c));
        return keep_collinear ? s < 0 : s <= 0;
    };
    for(const auto &q : p) {
        while(sz(h) >= 2 && bad(h[sz(h) - 2], h.back(), q)) h.pop_back();
        h.pb(q);
    }
    int lower = sz(h);
    for(int i = sz(p) - 2; i >= 0; i--) {
        while(sz(h) > lower && bad(h[sz(h) - 2], h.back(), p[i])) h.pop_back();
        h.pb(p[i]);
    }
    h.pop_back();
    if(keep_collinear && sz(h) == 2 * sz(p) - 2) return p;
    return h;
}

// -1 outside, 0 boundary, 1 inside. Convex polygon must be CCW without duplicates.
template<class T>
int point_in_convex_polygon(const vector<Point<T>> &p, const Point<T> &q) {
    int n = sz(p);
    if(n == 0) return -1;
    if(n == 1) return q == p[0] ? 0 : -1;
    if(n == 2) return on_segment(q, p[0], p[1]) ? 0 : -1;
    int a = sgn(cross(p[0], p[1], q)), b = sgn(cross(p[0], p[n - 1], q));
    if(a < 0 || b > 0) return -1;
    if(a == 0) return on_segment(q, p[0], p[1]) ? 0 : -1;
    if(b == 0) return on_segment(q, p[0], p[n - 1]) ? 0 : -1;
    int l = 1, r = n - 1;
    while(r - l > 1) {
        int m = (l + r) / 2;
        if(sgn(cross(p[0], p[m], q)) >= 0) l = m;
        else r = m;
    }
    int s = sgn(cross(p[l], p[(l + 1) % n], q));
    return s < 0 ? -1 : s == 0 ? 0 : 1;
}

// Squared diameter of a convex polygon in CCW order.
template<class T>
Wide<T> convex_diameter2(const vector<Point<T>> &p) {
    int n = sz(p);
    if(n <= 1) return 0;
    if(n == 2) return dist2(p[0], p[1]);
    Wide<T> res = 0;
    int j = 1;
    for(int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while(cross(p[i], p[ni], p[(j + 1) % n]) > cross(p[i], p[ni], p[j]))
            j = (j + 1) % n;
        res = max(res, max(dist2(p[i], p[j]), dist2(p[ni], p[j])));
    }
    return res;
}

// Keeps the part on or left of directed line a -> b.
vector<FP> polygon_cut(const vector<FP> &p, FP a, FP b) {
    vector<FP> res;
    for(int i = 0; i < sz(p); i++) {
        FP x = p[i], y = p[(i + 1) % sz(p)];
        ld cx = cross(b - a, x - a), cy = cross(b - a, y - a);
        if(sgn(cx) >= 0) res.pb(x);
        if(sgn(cx) * sgn(cy) < 0)
            res.pb(x + (y - x) * (cx / (cx - cy)));
    }
    return res;
}

// Both polygons must be convex and CCW.
vector<FP> convex_intersection(vector<FP> a, const vector<FP> &b) {
    if(a.empty() || b.empty()) return {};
    for(int i = 0; i < sz(b) && !a.empty(); i++)
        a = polygon_cut(a, b[i], b[(i + 1) % sz(b)]);
    return a;
}

template<class T>
vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b) {
    a = convex_hull(a), b = convex_hull(b);
    if(a.empty() || b.empty()) return {};
    if(sz(a) == 1) { for(auto &p : b) p += a[0]; return b; }
    if(sz(b) == 1) { for(auto &p : a) p += b[0]; return a; }
    auto rotate_lowest = [](vector<Point<T>> &p) {
        int at = min_element(all(p), [](const auto &x, const auto &y) {
            return x.y != y.y ? x.y < y.y : x.x < y.x;
        }) - p.begin();
        rotate(p.begin(), p.begin() + at, p.end());
    };
    rotate_lowest(a), rotate_lowest(b);
    a.pb(a[0]), a.pb(a[1]);
    b.pb(b[0]), b.pb(b[1]);
    vector<Point<T>> res{a[0] + b[0]};
    int i = 0, j = 0;
    while(i + 2 < sz(a) || j + 2 < sz(b)) {
        auto x = a[i + 1] - a[i], y = b[j + 1] - b[j];
        auto c = cross(x, y);
        bool take_a = j + 2 >= sz(b) || (i + 2 < sz(a) && c >= 0);
        bool take_b = i + 2 >= sz(a) || (j + 2 < sz(b) && c <= 0);
        res.pb(res.back() + (take_a ? x : Point<T>{}) + (take_b ? y : Point<T>{}));
        i += take_a, j += take_b;
    }
    res.pop_back();
    return convex_hull(res);
}

struct ClosestPair {
    i128 d2;
    int i, j;
};

// Exact O(n log n). Returns original indices, or {-1, -1} when n < 2.
ClosestPair closest_pair(const vector<P> &p) {
    int n = sz(p);
    if(n < 2) return {-1, -1, -1};
    struct Node { P p; int id; };
    vector<Node> a(n), tmp(n);
    for(int i = 0; i < n; i++) a[i] = {p[i], i};
    sort(all(a), [](const Node &x, const Node &y) { return x.p < y.p; });
    ClosestPair ans{dist2(a[0].p, a[1].p), a[0].id, a[1].id};
    auto relax = [&](const Node &x, const Node &y) {
        i128 d = dist2(x.p, y.p);
        if(d < ans.d2) ans = {d, x.id, y.id};
    };
    auto solve = [&](auto &&self, int l, int r) -> void {
        if(r - l <= 3) {
            for(int i = l; i < r; i++) for(int j = i + 1; j < r; j++) relax(a[i], a[j]);
            sort(a.begin() + l, a.begin() + r, [](const Node &x, const Node &y) {
                return x.p.y != y.p.y ? x.p.y < y.p.y : x.p.x < y.p.x;
            });
            return;
        }
        int m = (l + r) / 2;
        int x = a[m].p.x;
        self(self, l, m), self(self, m, r);
        merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r,
              tmp.begin(), [](const Node &u, const Node &v) {
                  return u.p.y != v.p.y ? u.p.y < v.p.y : u.p.x < v.p.x;
              });
        copy(tmp.begin(), tmp.begin() + r - l, a.begin() + l);
        vector<Node> strip;
        for(int i = l; i < r; i++) {
            i128 dx = (i128)a[i].p.x - x;
            if(dx * dx >= ans.d2) continue;
            for(int j = sz(strip) - 1; j >= 0; j--) {
                i128 dy = (i128)a[i].p.y - strip[j].p.y;
                if(dy * dy >= ans.d2) break;
                relax(a[i], strip[j]);
            }
            strip.pb(a[i]);
        }
    };
    solve(solve, 0, n);
    if(ans.i > ans.j) swap(ans.i, ans.j);
    return ans;
}

int lattice_boundary(const vector<P> &p) {
    int res = 0;
    for(int i = 0; i < sz(p); i++) {
        P d = p[(i + 1) % sz(p)] - p[i];
        res += gcd(llabs(d.x), llabs(d.y));
    }
    return res;
}
i128 lattice_interior(const vector<P> &p) {
    i128 a = area2(p);
    if(a < 0) a = -a;
    return (a - lattice_boundary(p) + 2) / 2;
}

struct Halfplane {
    FP p, v;
    ld a;
    Halfplane(FP _p, FP q) : p(_p), v(q - _p), a(atan2l(v.y, v.x)) {}
    bool outside(const FP &q) const { return cross(v, q - p) < -EPS; }
};

// Directed lines keep their left side. Returns a bounded intersection polygon.
vector<FP> halfplane_intersection(vector<Halfplane> h) {
    sort(all(h), [](const Halfplane &a, const Halfplane &b) {
        if(a.a != b.a) return a.a < b.a;
        return cross(a.v, b.p - a.p) < 0;
    });
    vector<Halfplane> lines;
    for(const auto &x : h) {
        if(!lines.empty() && sgn(cross(lines.back().v, x.v)) == 0 && dot(lines.back().v, x.v) > 0) {
            if(x.outside(lines.back().p)) lines.back() = x;
        } else lines.pb(x);
    }
    deque<Halfplane> q;
    deque<FP> p;
    for(const auto &x : lines) {
        while(!p.empty() && x.outside(p.back())) p.pop_back(), q.pop_back();
        while(!p.empty() && x.outside(p.front())) p.pop_front(), q.pop_front();
        if(!q.empty()) {
            auto at = line_intersection({q.back().p, q.back().v}, {x.p, x.v});
            if(!at) return {};
            p.pb(*at);
        }
        q.pb(x);
    }
    while(!p.empty() && q.front().outside(p.back())) p.pop_back(), q.pop_back();
    while(!p.empty() && q.back().outside(p.front())) p.pop_front(), q.pop_front();
    if(sz(q) < 3) return {};
    auto at = line_intersection({q.back().p, q.back().v}, {q.front().p, q.front().v});
    if(!at) return {};
    p.pb(*at);
    return vector<FP>(all(p));
}

template<class T>
struct Point3 {
    T x, y, z;
    Point3(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
    Point3 operator+(const Point3 &p) const { return {x + p.x, y + p.y, z + p.z}; }
    Point3 operator-(const Point3 &p) const { return {x - p.x, y - p.y, z - p.z}; }
    Point3 operator*(T k) const { return {x * k, y * k, z * k}; }
    Point3 operator/(T k) const { return {x / k, y / k, z / k}; }
    bool operator==(const Point3 &p) const { return x == p.x && y == p.y && z == p.z; }
};

using P3 = Point3<int>;
using FP3 = Point3<ld>;

template<class T> Wide<T> dot(const Point3<T> &a, const Point3<T> &b) {
    return (Wide<T>)a.x * b.x + (Wide<T>)a.y * b.y + (Wide<T>)a.z * b.z;
}
template<class T> Point3<Wide<T>> cross(const Point3<T> &a, const Point3<T> &b) {
    return {(Wide<T>)a.y * b.z - (Wide<T>)a.z * b.y,
            (Wide<T>)a.z * b.x - (Wide<T>)a.x * b.z,
            (Wide<T>)a.x * b.y - (Wide<T>)a.y * b.x};
}
template<class T> Wide<T> volume6(const Point3<T> &a, const Point3<T> &b,
                                  const Point3<T> &c, const Point3<T> &d) {
    auto u = b - a, v = c - a, w = d - a;
    auto n = cross(u, v);
    return (Wide<T>)n.x * w.x + (Wide<T>)n.y * w.y + (Wide<T>)n.z * w.z;
}
ld norm(const FP3 &p) { return sqrtl(dot(p, p)); }
FP3 unit(const FP3 &p) { return p / norm(p); }
ld distance_plane(FP3 p, FP3 a, FP3 b, FP3 c) {
    FP3 n = cross(b - a, c - a);
    return fabsl(dot(p - a, n)) / norm(n);
}
optional<FP3> line_plane_intersection(FP3 p, FP3 v, FP3 a, FP3 b, FP3 c) {
    FP3 n = cross(b - a, c - a);
    ld d = dot(v, n);
    if(sgn(d) == 0) return nullopt;
    return p + v * (dot(a - p, n) / d);
}
FP3 rotate_around_axis(FP3 p, FP3 axis, ld a) {
    axis = unit(axis);
    FP3 q = cross(axis, p);
    return p * cosl(a) + q * sinl(a) + axis * (dot(axis, p) * (1 - cosl(a)));
}
}

// using namespace geo; P is exact integer, FP is long double.
// Hulls and convex polygons are CCW. Circle and line routines use FP.
