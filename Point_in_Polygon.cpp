#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<deque>

using namespace std;

const double PI = atan2(0, -1);
const long long int INF = 1e9;

#define double long double

struct Point{
    long long int x, y;
    Point(long long int x0 = 0, long long int y0 = 0) : x(x0), y(y0) {};
};

Point first = Point(INF, INF);
Point Q;

struct Vector{
    long long int x, y;
    Vector(long long int x0 = 0, long long int y0 = 0){
        this->x = x0;
        this->y = y0;
    };
    Vector(const Point & A, const Point & B){
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
    Vector(const Point & A){
        this->x = A.x;
        this->y = A.y;
    }
    
    long long int len2(){
        return x * x + y * y;
    }
};

Vector operator + (Vector A, Vector B){
    return Vector(A.x + B.x, A.y + B.y);
}

istream & operator >> (istream & in, Point & P){
    return in >> P.x >> P.y;
}

ostream & operator << (ostream & out, Point P){
    return out << P.x << " " << P.y << endl;
}

bool operator == (const Point & A, const Point & B){
    return (A.x == B.x && A.y == B.y);
}

long long int dot_product(const Vector & A, const Vector & B){
    return A.x * B.x + A.y * B.y;
}

long long int cross_product(const Vector & A, const Vector & B){
    return A.x * B.y - A.y * B.x;
}

bool cmp(const Point & A, const Point & B){
    Vector OA(first, A), OB(first, B);
    return cross_product(OA, OB) > 0 || (cross_product(OA, OB) == 0 && OA.len2() < OB.len2());
}

bool is_right_turn(Point & a, Point & b, Point & c) {
    Vector AB(a, b), BC(b, c);
    return cross_product(AB, BC) <= 0;
}

void getConvex(vector<Point> & Points, vector<Point> & st){
    int ind = 0;
    int n = (int)Points.size();
    for (int i = 0; i < n; i++){
        if (Points[i].y < first.y){
            first = Points[i];
            ind = i;
        }else if (Points[i].y == first.y && Points[i].x < first.x){
            first = Points[i];
            ind = i;
        }
    }
    swap(Points[ind], Points[0]);
    sort(Points.begin() + 1, Points.end(), cmp);
    st.push_back(first);
    for (int i = 1; i < n; i++){
        if (st.back() == Points[i])continue;
        while (st.size() >= 2 && (is_right_turn(st[st.size() - 2], st.back(), Points[i]))){
            st.pop_back();
        }
        st.push_back(Points[i]);
    }
}

bool cmp2(const Point & A, const Point & B){
    Vector f(first, A);
    Vector s(first, B);
    Vector o(first, Q);
    return cross_product(f, o) > cross_product(s, o);
}

bool onSegment(const Point & A, const Point & B){
    Vector AB(A, B);
    Vector BA(B, A);
    Vector AQ(A, Q);
    Vector BQ(B, Q);
    return cross_product(AB, AQ) == 0 && dot_product(AB, AQ) >= 0 && dot_product(BA, BQ) >= 0;
}

bool in(vector<Point> & convex){
    int ind1 = (int)(lower_bound(convex.begin() + 1, convex.end(), Q, cmp2) - convex.begin());
    int ind2 = ind1 - 1;
    if (ind1 == convex.size())return onSegment(convex[0], convex.back());
    else if (ind1 == 1){
        return onSegment(convex[0], convex[1]);
    }else{
        Vector Q1(Q, convex[ind1]);
        Vector Q2(Q, convex[ind2]);
        Vector Qf(Q, first);
        Vector f1(first, convex[ind1]);
        Vector f2(first, convex[ind2]);
        int s1 = (int)abs(cross_product(f1, f2));
        int s2 = (int)(abs(cross_product(Q1, Q2)) + abs(cross_product(Q2, Qf)) + abs(cross_product(Qf, Q1)));
        bool ans = (s1 == s2);
        return (ans || onSegment(convex[ind2], convex[ind1]));
    }
}

signed main(){
    int n, m, k; cin >> n >> m >> k;
    vector<Point> Points(n), convex;
    for (int i = 0; i < n; i++)cin >> Points[i];
    getConvex(Points, convex);
    for (int i = 0; i < m; i++){
        cin >> Q;
        k -= in(convex);
    }
    if (k <= 0)cout << "YES";
    else cout << "NO";
    return 0;
}
