#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

struct Point{
    double x, y;
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
};

Point S(0, 1), L(1, 0);

double get_l(const Point & a, const Point & b){
    double dx = fabs(a.x - b.x);
    double dy = fabs(a.y - b.y);
    return sqrt(dx * dx + dy * dy);
}

double get_time(const Point & b, int Vp, int Vf){
    double len_to_S = get_l(b, S);
    double len_to_L = get_l(b, L);
    return len_to_S / Vp + len_to_L / Vf;
}

double tern(int Vp, int Vf, double a){
    double l = 0, r = 1;
    for (int i = 0; i < 100; i++){
        double m1 = (2 * l + r) / 3;
        double m2 = (l + 2 * r) / 3;
        double fm1 = get_time(Point(m1, a), Vp, Vf);
        double fm2 = get_time(Point(m2, a), Vp, Vf);
        if (fm1 < fm2){
            r = m2;
        }else{
            l = m1;
        }
    }
    return (l + r) / 2;
}

int main(){
    int Vp, Vf;
    double a;
    cin >> Vp >> Vf >> a;
    cout.precision(20);
    cout << tern(Vp, Vf, a);
    return 0;
}
