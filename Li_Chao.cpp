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

const long long int maxN = 2e6 + 10;

struct Line{
    long long int k, b;
    Line(long long int k = 0, long long int b = 0){
        this->k = k;
        this->b = b;
    }
    long long int getY(long long int x){
        return k * x + b;
    }
};

typedef Line * pLine;

struct LiChao{
    vector<pLine> t;
    LiChao(){
        t.resize(4 * maxN, nullptr);
    }
    void addLine(pLine l, int v = 0, int tl = 0, int tr = maxN){
        if (tr - tl < 1)return;
        else if (t[v] == nullptr){
            t[v] = l;
        }else if (tr - tl != 1){
            int mid = (tl + tr) / 2;
            if (t[v]->getY(mid) < l->getY(mid)){
                swap(t[v], l);
            }
            if (l->k < t[v]->k){
                addLine(l, 2 * v + 1, tl, mid);
            }else{
                addLine(l, 2 * v + 2, mid, tr);
            }
        }
    }
    long long int getAns(long long int x, int v = 0, int tl = 0, int tr = maxN){
        if (t[v] == nullptr)return -1e15;
        if (tr - tl == 1)return t[v]->getY(x);
        else{
            int mid = (tl + tr) / 2;
            if (x >= mid)return max(t[v]->getY(x), getAns(x, 2 * v + 2, mid, tr));
            else return max(t[v]->getY(x), getAns(x, 2 * v + 1, tl, mid));
        }
    }
};

signed main() {
    int n; cin >> n;
    vector<long long int> x(n), c(n), t(n);
    for (int i = 0; i < n; i++){
        cin >> x[i] >> c[i] >> t[i];
        x[i] += 1e6;
    }
    LiChao tree;
    tree.addLine(new Line(-c[0], c[0] * x[0]));
    tree.addLine(new Line(c[0], -c[0] * x[0]));
    vector<long long int> dp(n, 0); dp[0] = 0;
    for (int i = 1; i < n; i++){
        dp[i] = tree.getAns(x[i]) + t[i];
        tree.addLine(new Line(-c[i], c[i] * x[i] + dp[i]));
        tree.addLine(new Line(c[i], -c[i] * x[i] + dp[i]));
    }
    cout << dp.back();
    return 0;
}
