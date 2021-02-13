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
    double x, y;
    Vector(double x0 = 0, double y0 = 0) : x(x0), y(y0){};
    Vector(const Point & A, const Point & B) : x(B.x - A.x), y(B.y - A.y){};
    
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
    in >> P.x >> P.y;
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

int main(){
    int n;
    cin >> n;
    vector<Vector> Points(n);
    for (int i = 0; i < n; i++)cin >> Points[i];
    Points.push_back(*(Points.begin()));
    Vector last = Points[0];
    double square = 0;
    for (int i = 1; i <= n; i++){
        Vector n = Points[i];
        square += cross_product(last, n) / 2;
        last = n;
    }
    cout.precision(20);
    cout << fabs(square);
    return 0;
}
