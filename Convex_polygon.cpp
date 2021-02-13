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
    return a * b > 0;
}

bool cmp(Vector & a, Vector & b){
    return a.ang < b.ang || (a.ang == b.ang && a.len() > b.len());
}

int main(){
    int n, pl = 0, ot = 0;
    cin >> n;
    vector<Point> V(n);
    for (int i = 0; i < n; i++)cin >> V[i];
    for (int i = 0; i < n; i++){
        Vector A(V[i % n], V[(i + 1) % n]);
        Vector B(V[(i + 1) % n], V[(i + 2) % n]);
        double cross = cross_product(A, B);
        if (cross > 0)pl++;
        else if (cross < 0)ot++;
    }
    if (ot * pl != 0)cout << "NO";
    else cout << "YES";
    return 0;
}
