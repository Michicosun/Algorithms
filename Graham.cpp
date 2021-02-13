#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<deque>

using namespace std;

const double PI = atan2(0, -1);
const int INF = 1e9;


struct Point{
    double x, y;
    Point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {};
};

Point first = Point(INF, INF);

struct Vector{
    double x, y;
    Vector(double x0 = 0, double y0 = 0){
        this->x = x0;
        this->y = y0;
    };
    Vector(const Point & A, const Point & B){
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
    
    double len(){
        return sqrt(x * x + y * y);
    }
    
    double angle(){
        return atan2(y, x);
    }
};

Vector operator / (Vector A, double d){
    return Vector(A.x / d, A.y / d);
};

Vector operator * (Vector A, double d){
    return Vector(A.x * d, A.y * d);
};

Point operator + (Point A, Vector B){
    return Point(A.x + B.x, A.y + B.y);
}

Vector operator + (Vector A, Vector B){
    return Vector(A.x + B.x, A.y + B.y);
}

istream & operator >> (istream & in, Point & P)
{
    in >> P.x >> P.y;
    return in;
}

istream & operator >> (istream & in, Vector & P)
{
    double nx, ny;
    in >> nx >> ny;
    P = Vector(nx, ny);
    return in;
}

ostream & operator << (ostream & out, Point P)
{
    out.precision(20);
    out << P.x << " " << P.y << endl;
    return out;
}

ostream & operator << (ostream & out, Vector P)
{
    out.precision(20);
    out << P.x << " " << P.y << endl;
    return out;
}

double dot_product(const Vector & A, const Vector & B){
    return A.x * B.x + A.y * B.y;
}

double cross_product(const Vector & A, const Vector & B){
    return A.x * B.y - A.y * B.x;
}

double angle(Vector A, Vector B){
    return atan2(cross_product(A, B), dot_product(A, B));
}

Vector ort(Vector A){
    return Vector(-A.y, A.x);
}

bool one(double a, double b){
    return a * b > 0;
}

bool cmp(const Point & A, const Point & B){
    Vector OA(first, A), OB(first, B);
    return cross_product(OA, OB) > 0 || (cross_product(OA, OB) == 0 && OA.len() < OB.len());
}

bool is_right_turn(Point & a, Point & b, Point & c) {
    Vector AB(a, b), BC(b, c);
    return cross_product(AB, BC) < 0;
}

bool is_on_turn(Point & a, Point & b, Point & c) {
    Vector AB(a, b), BC(b, c);
    return cross_product(AB, BC) == 0;
}


int main(){
    int n;
    cin >> n;
    vector<Point> Points(n);
    int ind = 0;
    for (int i = 0; i < n; i++){
        cin >> Points[i];
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
    deque<Point> st;
    st.push_back(first);
    for (int i = 1; i < n; i++){
        while (st.size() > 2 && is_right_turn(st[st.size() - 2], st.back(), Points[i])){
            st.pop_back();
        }
        if (st.size() > 2 && is_on_turn(st[st.size() - 2], st.back(), Points[i]))st.pop_back();
        st.push_back(Points[i]);
    }
    vector<Point> ans;
    for (auto i : st){
        ans.push_back(i);
    }
    ans.push_back(first);
    //for (auto i : ans)cout << i;
    double p = 0;
    for (int i = 0; i < (int)ans.size() - 1; i++){
        Vector a(ans[i], ans[i + 1]);
        p += a.len();
    }
    cout.precision(20);
    cout << p;
    return 0;
}
