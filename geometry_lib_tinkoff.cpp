#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_set>
#include<map>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<cassert>
#include<sstream>
#include<set>

#define double long double

using namespace std;

const double PI = 3.14159265358979323846;
const double maxN = 1e10;

double sqr(double a){
    return a * a;
}

struct Point{
    double x, y;
    int ind;
    Point(double x0 = 0, double y0 = 0, int ind = 0){
        this->x = x0;
        this->y = y0;
        this->ind = ind;
    }
};

bool operator == (const Point & a, const Point & b){
    return a.x == b.x && a.y == b.y;
}

bool operator < (const Point & a, const Point & b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

struct Vector{
    double x, y;
    int ind;
    Vector(double x0 = 0, double y0 = 0){
        this->x = x0;
        this->y = y0;
    }
    Vector(const Point & A, const Point & B, int ind = 0){
        this->x = B.x - A.x;
        this->y = B.y - A.y;
        this->ind = ind;
    }
    double len(){
        return sqrt(x * x + y * y);
    }
    double angle() const{
        return atan2(y, x);
    }
};

struct Circle{
    double x, y, r;
    Circle(double x0 = 0, double y0 = 0, double r0 = 0){
        this->x = x0;
        this->y = y0;
        this->r = r0;
    }
    Point get_center(){
        return Point(this->x, this->y);
    }
    double getSubS(double ang){
        return ang * r;
    }
};

bool operator == (Circle & a, Circle & b){
    return a.x == b.x && a.y == b.y && a.r == b.r;
}

Vector operator / (Vector A, double d){
    return Vector(A.x / d, A.y / d);
};

Vector operator * (Vector A, double d){
    return Vector(A.x * d, A.y * d);
};

Point operator + (Point A, Vector B){
    return Point(A.x + B.x, A.y + B.y);
}

struct Line{
    double a, b, c;
    Line(double a0 = 0, double b0 = 0, double c0 = 0){
        this->a = a0;
        this->b = b0;
        this->c = c0;
    }
    Line(Point & A, Point & B){
        Vector AB(A, B);
        b = -AB.x;
        a = AB.y;
        c = -a * A.x - b * A.y;
    }
    Line(Point & A, Vector & C){
        Point B = A + C;
        Line(A, B);
    }
    Vector normal(){
        return Vector(a, b);
    }
    Point getPoint(){
        double x = -(a * c) / (a * a + b * b);
        double y = -(b * c) / (a * a + b * b);
        return Point(x, y);
    }
    double get(Point & A){
        return a * A.x + b * A.y + c;
    }
    double perp_sz(const Point & C){
        return (a * C.x + b * C.y + c) / sqrt(a * a + b * b);
    }
    Point proection(const Point & A){
        double d = perp_sz(A);
        Vector n = normal();
        n = n / n.len();
        Vector n1 = n * d, n2 = n * (-d);
        Point A1 = A + n1, A2 = A + n2;
        if(get(A1) == 0)return A1;
        else return A2;
    }
};

struct Ray{
    Point A, B;
    Ray(){};
    Ray(Point & A, Point & B){
        this->A = A;
        this->B = B;
    }
};

istream & operator >> (istream & in, Circle & P){
    return in >> P.x >> P.y >> P.r;
}

istream & operator >> (istream & in, Point & P){
    return in >> P.x >> P.y;
}

istream & operator >> (istream & in, Vector & P){
    return in >> P.x >> P.y;
}

istream & operator >> (istream & in, Line & P){
    return in >> P.a >> P.b >> P.c;
}

ostream & operator << (ostream & out, Point P){
    out.precision(20);
    return out << P.x << " " << P.y;
}

ostream & operator << (ostream & out, Vector P){
    out.precision(20);
    return out << P.x << " " << P.y << endl;
}

ostream & operator << (ostream & out, Line P){
    out.precision(20);
    return out << P.a << " " << P.b << " " << P.c << endl;
}

double dot_product(const Vector & A, const Vector & B){
    return A.x * B.x + A.y * B.y;
}

double cross_product(const Vector & A, const Vector & B){
    return A.x * B.y - A.y * B.x;
}

double angle(Vector A, Vector B){
    return fabs(atan2(cross_product(A, B), dot_product(A, B)));
}

Vector ort(Vector A){
    return Vector(-A.y, A.x);
}

bool one(double a, double b){
    return a * b >= 0;
}

Vector rotate_v(const Vector & A, double angle_rad){
    return Vector((A.x * cos(angle_rad) - A.y * sin(angle_rad)), (A.x * sin(angle_rad) + A.y * cos(angle_rad)));
}

Point zero = Point(0, 0);

vector<Point> intersect(Line & a, Line & b){
    if(cross_product(a.normal(), b.normal()) == 0)return {};
    double x = (b.c * a.b - b.b * a.c) / (b.b * a.a - a.b * b.a);
    double y = (b.c * a.a - a.c * b.a) / (a.b * b.a - b.b * a.a);
    return {Point(x, y)};
}

vector<Point> intersect(Circle & c, Line & a){
    if(a.perp_sz(c.get_center()) > c.r)return {};
    else if(a.perp_sz(c.get_center()) == c.r)return {a.proection(c.get_center())};
    else{
        Point S = a.proection(c.get_center());
        Vector n = ort(a.normal());
        n = n / n.len();
        double sz = sqrt(sqr(c.r) - sqr(a.perp_sz(c.get_center())));
        Vector n1 = n * sz;
        Vector n2 = n * (-sz);
        return {S + n1, S + n2};
    }
}

vector<Point> intersect(Circle & a, Circle & b){
    Vector AB(a.get_center(), b.get_center());
    if(AB.len() > a.r + b.r)return {};
    else{
        double la = 2 * a.x - 2 * b.x;
        double lb = 2 * a.y - 2 * b.y;
        double lc = sqr(b.x) + sqr(b.y) - sqr(b.r) - sqr(a.x) - sqr(a.y) + sqr(a.r);
        Line l(la, lb, lc);
        return intersect(a, l);
    }
}

bool cmpAndrew(const Point & a, const Point & b) {
    if(a.x == b.x)return a.y < b.y;
    return a.x < b.x;
}

bool cw(Point a, Point b, Point c){
    return cross_product(Vector(b, a), Vector(b, c)) > 0;
}

bool ccw(Point a, Point b, Point c){
    return cross_product(Vector(b, a), Vector(b, c)) < 0;
}

vector<Point> Andrew(vector<Point> & points){
    sort(points.begin(), points.end(), cmpAndrew);
    vector<Point> up, down;
    up.push_back(points[0]);
    down.push_back(points[0]);
    Point p1 = points[0], p2 = points.back();
    int n = (int)points.size();
    for(int i = 1; i < n; i++) {
        if (i == n - 1 || cw(p1, points[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], points[i])) {
                up.pop_back();
            }
            up.push_back(points[i]);
        }
        if (i == n - 1 || ccw(p1, points[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], points[i])) {
                down.pop_back();
            }
            down.push_back(points[i]);
        }
    }
    vector<Point> convexHall;
    for(auto i : down)convexHall.push_back(i);
    for(int i = (int)up.size() - 2; i >= 1; i--)convexHall.push_back(up[i]);
    return convexHall;
}

Point first;

struct node{
    Point now, up, down;
    node(Point & now){
        this->now = now;
    }
    node(Point & down, Point & now){
        this->down = down;
        this->now = now;
    }
};

bool cmpGraham(const Point & A, const Point & B){
    Vector OA(first, A);
    Vector OB(first, B);
    return cross_product(OA, OB) > 0 || (cross_product(OA, OB) == 0 && OA.len() < OB.len());
}

vector<node> Graham(vector<Point> & points, unordered_set<int> & ind){
    first = Point(1e10, 1e10);
    int n = (int)points.size();
    for(int i = 0; i < n; i++){
        if(points[i] < first)first = points[i];
    }
    sort(points.begin(), points.end(), cmpGraham);
    vector<node> convex = {node(points[0]), node(points[0], points[1])};
    convex[0].up = points[1];
    for(int i = 2; i < n; i++){
        int l = (int)convex.size();
        Vector oldV(convex[l - 2].now, convex[l - 1].now), newV(convex[l - 1].now, points[i]);
        while (cross_product(oldV, newV) < 0){
            convex.pop_back();
            l = (int)convex.size();
            oldV = Vector(convex[l - 2].now, convex[l - 1].now);
            newV = Vector(convex[l - 1].now, points[i]);
        }
        Point down = convex.back().now;
        convex.back().up = points[i];
        if(cross_product(oldV, newV) == 0)convex.pop_back();
        convex.push_back(node(down, points[i]));
    }
    convex[0].down = convex.back().now;
    convex.back().up = convex[0].now;
    for(auto i : convex)ind.insert(i.now.ind);
    return convex;
}

vector<Point> convexHall;
vector<Vector> up, down;

bool cmpV(const Vector & a, const Vector & b){
    return cross_product(a, b) > 0;
}

void preTangents(vector<Point> & points){
    convexHall = Andrew(points);
    for(int i = 0; i < convexHall.size(); i++){
        Point A = convexHall[i], B = convexHall[(i + 1) % convexHall.size()];
        Vector AB(A, B, i);
        if(AB.angle() >= 0 || fabs(AB.angle()) == PI)up.push_back(AB);
        else down.push_back(AB);
    }
    sort(up.begin(), up.end(), cmpV);
    sort(down.begin(), down.end(), cmpV);
}

vector<Point> tangents(Line & l){
    if(convexHall.size() == 1)return {convexHall[0], convexHall[0]};
    else if(convexHall.size() == 2)return convexHall;
    else{
        Vector n1 = ort(l.normal());
        Vector n2 = n1 * -1;
        int ind1, ind2;
        if(n1.angle() >= 0 || fabs(n1.angle()) == PI){
            auto it = lower_bound(up.begin(), up.end(), n1, cmpV);
            if(it != up.end())ind1 = (*it).ind;
            else ind1 = down[0].ind;
        }else{
            auto it = lower_bound(down.begin(), down.end(), n1, cmpV);
            if(it != down.end())ind1 = (*it).ind;
            else ind1 = up[0].ind;
        }
        if(n2.angle() >= 0 || fabs(n2.angle()) == PI){
            auto it = lower_bound(up.begin(), up.end(), n2, cmpV);
            if(it != up.end())ind2 = (*it).ind;
            else ind2 = down[0].ind;
        }else{
            auto it = lower_bound(down.begin(), down.end(), n2, cmpV);
            if(it != down.end())ind2 = (*it).ind;
            else ind2 = up[0].ind;
        }
        return {convexHall[ind1], convexHall[ind2]};
    }
}

bool intersect_1(double a, double b, double c, double d) {
    if (a > b)swap(a, b);
    if (c > d)swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect(Point & A, Point & B, Point & C, Point & D){
    Vector AB(A, B), BA(B, A), AC(A, C), AD(A, D), BC(B, C), BD(B, D);
    Vector CD(C, D), DC(D, C), DA(D, A), DB(D, B), CA(C, A), CB(C, B);
    if(cross_product(AB, AC) == 0 && cross_product(AB, AD) == 0){
        if(intersect_1(A.x, B.x, C.x, D.x) && intersect_1(A.y, B.y, C.y, D.y))return true;
        else return false;
    }
    bool ans = (!one(cross_product(AB, AC), cross_product(AB, AD)) && !one(cross_product(CD, CA), cross_product(CD, CB)));
    return ans;
}

double dist(Point A, Point B){
    Vector AB(A, B);
    return AB.len();
}

double dist(Point A, Point B, Point C){
    Vector BC(B, C), CB(C, B), BA(B, A), CA(C, A);
    Line l(B, C);
    if(dot_product(BC, BA) >= 0 && dot_product(CB, CA) >= 0)return fabs(l.perp_sz(A));
    else if(dot_product(BC, BA) < 0)return dist(A, B);
    else return dist(A, C);
}

double dist(Point A, Ray Q){
    Point B = Q.A, C = Q.B;
    Vector BC(B, C), BA(B, A);
    Line l(B, C);
    if(dot_product(BC, BA) < 0)return dist(A, B);
    else return fabs(l.perp_sz(A));
}

double dist(Point A, Line L){
    return fabs(L.perp_sz(A));
}

double dist(Point A, Point B, Point C, Point D){
    if(intersect(A, B, C, D))return 0;
    else return min({dist(A, C, D), dist(B, C, D), dist(C, A, B), dist(D, A, B)});
}

double dist(Point A, Point B, Ray Q){
    Point C = Q.A, D = Q.B;
    Vector CD(C, D);
    CD = CD * maxN;
    D = D + CD;
    return dist(A, B, C, D);
}

double dist(Point A, Point B, Line L){
    Point C = L.getPoint();
    Vector n = ort(L.normal());
    Vector n1 = n * maxN, n2 = n * (-maxN);
    C = C + n1;
    Point D = C + n2;
    return dist(A, B, C, D);
}

double dist(Ray Q1, Ray Q2){
    Point A = Q1.A, B = Q1.B, C = Q2.A, D = Q2.B;
    Vector AB(A, B), CD(C, D);
    AB = AB * maxN;
    CD = CD * maxN;
    B = B + AB;
    D = D + CD;
    return dist(A, B, C, D);
}

double dist(Ray Q, Line L){
    Point A = Q.A, B = Q.B, C = L.getPoint();
    Vector AB(A, B);
    AB = AB * maxN;
    B = B + AB;
    Vector n = ort(L.normal());
    Vector n1 = n * maxN, n2 = n * (-maxN);
    C = C + n1;
    Point D = C + n2;
    return dist(A, B, C, D);
}

double dist(Line L1, Line L2){
    Point A = L1.getPoint();
    Vector n = ort(L1.normal());
    Vector n1 = n * maxN, n2 = n * (-maxN);
    A = A + n1;
    Point B = A + n2;
    Point C = L2.getPoint();
    Vector m = ort(L2.normal());
    Vector m1 = m * maxN, m2 = m * (-maxN);
    C = C + m1;
    Point D = C + m2;
    return dist(A, B, C, D);
}

signed main(){
    Point A, B, C, D; cin >> A >> B >> C >> D;
    cout.precision(20);
    cout << dist(A, C) << endl;
    cout << dist(A, C, D) << endl;
    cout << dist(A, Ray(C, D)) << endl;
    cout << dist(A, Line(C, D)) << endl;
    cout << dist(C, A, B) << endl;
    cout << dist(A, B, C, D) << endl;
    cout << dist(A, B, Ray(C, D)) << endl;
    cout << dist(A, B, Line(C, D)) << endl;
    cout << dist(C, Ray(A, B)) << endl;
    cout << dist(C, D, Ray(A, B)) << endl;
    cout << dist(Ray(A, B), Ray(C, D)) << endl;
    cout << dist(Ray(A, B), Line(C, D)) << endl;
    cout << dist(C, Line(A, B)) << endl;
    cout << dist(C, D, Line(A, B)) << endl;
    cout << dist(Ray(C, D), Line(A, B)) << endl;
    cout << dist(Line(A, B), Line(C, D)) << endl;
    return 0;
}
