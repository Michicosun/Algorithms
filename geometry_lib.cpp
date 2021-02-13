#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

double PI = 3.14159265358979323846;

struct Point{
    double x, y;
    Point(double x0 = 0, double y0 = 0){
        this->x = x0;
        this->y = y0;
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
};

struct Vector{
    double x, y;
    Vector(double x0 = 0, double y0 = 0){
        this->x = x0;
        this->y = y0;
    }
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

struct Line{
    double a, b, c;
    Line(double a0 = 0, double b0 = 0, double c0 = 0){
        this->a = a0;
        this->b = b0;
        this->c = c0;
    }
    
    Vector normal(){
        return Vector(a, b);
    }
    
    double perp_sz(const Point & C){
        return (a * C.x + b * C.y + c) / sqrt(a * a + b * b);
    }
    
    Point perp(const Point & A){
        double d = perp_sz(A);
        Vector n = normal();
        n = n / n.len();
        n = n * (-d);
        return A + n;
    }
    
};

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

istream & operator >> (istream & in, Circle & P)
{
    in >> P.x >> P.y >> P.r;
    return in;
}

istream & operator >> (istream & in, Line & P)
{
    in >> P.a >> P.b >> P.c;
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

ostream & operator << (ostream & out, Circle P)
{
    out.precision(20);
    out << P.x << " " << P.y << " " << P.r << endl;
    return out;
}

ostream & operator << (ostream & out, Line P)
{
    out.precision(20);
    out << P.a << " " << P.b << " " << P.c << endl;
    return out;
}

double dot_product(const Vector & A, const Vector & B){
    return A.x * B.x + A.y * B.y;
}

double cross_product(const Vector & A, const Vector & B){
    return A.x * B.y - A.y * B.x;
}

double angle(Vector A, Vector B){
    double ans = dot_product(A, B) / (A.len() * B.len());
    cout << B << "-" << endl;
    if(ans < -1)ans = -1;
    if(ans > 1)ans = 1;
    return ans;
}

Vector ort(Vector A){
    return Vector(-A.y, A.x);
}

bool one(double a, double b){
    return a * b > 0;
}

Vector rotate_v(const Vector & A, double angle_rad){
    return Vector((A.x * cos(angle_rad) - A.y * sin(angle_rad)), (A.x * sin(angle_rad) + A.y * cos(angle_rad)));
}
