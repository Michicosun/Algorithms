#include<iostream>
#include<cmath>
#include<map>
#include<queue>
#include<set>
#include<cassert>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;

struct Line{
    long long int k, b;
    Line(long long int k = 0, long long int b = 0){
        this->k = k;
        this->b = b;
    }
    long double getY(long double x){
        return k * x + b;
    }
};

long double intersect(Line & a, Line & b){
    return ((long double)(a.b - b.b) / (b.k - a.k));
}

struct convexHallTrick{
    vector<Line> lines;
    vector<long double> points;
    convexHallTrick(Line l){
        lines.push_back(l);
    }
    void addLine(Line & l){
        while(lines.size() > 1 && intersect(lines.back(), l) < points.back()){
            points.pop_back();
            lines.pop_back();
        }
        points.push_back(intersect(l, lines.back()));
        lines.push_back(l);
    }
    long long int getAns(long double x){
        long long int ind = (long long int)(upper_bound(points.begin(), points.end(), x) - points.begin());
        Line l = lines[ind];
        return l.getY(x);
    }
};

signed main() {
    long long int n; cin >> n;
    vector<long long int> a(n), b(n);
    for(long long int i = 0; i < n; i++)cin >> a[i];
    for(long long int i = 0; i < n; i++)cin >> b[i];
    convexHallTrick cht(Line(b[0], 0));
    vector<long long int> dp(n, 0);
    for(long long int i = 1; i < n; i++){
        dp[i] = cht.getAns(a[i]);
        Line newL(b[i], dp[i]);
        cht.addLine(newL);
    }
    cout << dp.back();
    return 0;
}
