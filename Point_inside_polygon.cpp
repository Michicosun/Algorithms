#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

const double PI = atan2(0, -1);

struct Point{
    double x, y;
    Point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {};
};

struct Vector{
    double x, y, ang;
    Vector(double x0 = 0, double y0 = 0){
        this->x = x0;
        this->y = y0;
        this->ang = atan2(y0, x0);
    };
    Vector(const Point & A, const Point & B){
        this->x = B.x - A.x;
        this->y = B.y - A.y;
        this->ang = atan2(B.y - A.y, B.x - A.x);
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
    return a * b >= 0;
}

bool cmp(Vector & a, Vector & b){
    return a.ang < b.ang || (a.ang == b.ang && a.len() > b.len());
}

bool check(Point & A, Point & B, Point & C, Point & D){
    Vector AC(A, C), AD(A, D), AB(A, B), DC(D, C), DA(D, A), DB(D, B);
    double cross_AB_AD = cross_product(AB, AD);
    double cross_AC_AB = cross_product(AC, AB);
    double cross_DB_DC = cross_product(DB, DC);
    double cross_DC_DA = cross_product(DC, DA);
    return one(cross_AB_AD, cross_AC_AB) && one(cross_DB_DC, cross_DC_DA);
}

int main(){
    const int INF = 1e9;
    int n;
    cin >> n;
    Point A;
    cin >> A;
    Point INF_P = Point(INF, A.y);
    vector<Point> Points(n);
    for (int i = 0; i < n; i++)cin >> Points[i];
    Points.push_back(Points[0]);
    vector<int> loc(n + 1);
    for (int i = 0; i < n; i++){
        Vector P0A(Points[i], A), P0P1(Points[i], Points[i + 1]), P1A(Points[i + 1], A), P1P0(Points[i + 1], Points[i]);
        if (cross_product(P0A, P0P1) == 0 && one(dot_product(P0A, P0P1), dot_product(P1A, P1P0))){
            cout << "YES";
            return 0;
        }
    }
    for (int i = 0; i <= n; i++){
        loc[i] = Points[i].y > A.y;
    }
    //for(auto i : loc)cout << i << " ";
    //cout << endl;
    int pos = 0;
    int prev = 0;
    for (int i = 1; i <= n; i++){
        if (loc[i] != loc[prev]){
            //cout << Points[prev] << Points[i] << "------------" << endl;
            pos += check(Points[i], Points[prev], A, INF_P);
        }
        prev = i;
    }
    if (pos % 2 != 0)cout << "YES";
    else cout << "NO";
    return 0;
}
