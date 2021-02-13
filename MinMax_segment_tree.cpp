#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

int n;
const int INF = 1e9;

struct node{
    long long int mn, mx;
    node(long long int mn = 0, long long int mx = 0){
        this->mn = mn;
        this->mx = mx;
    }
};

void recalc(vector<node> & tree, long long int v){
    tree[v].mn = min(tree[2 * v].mn, tree[2 * v + 1].mn);
    tree[v].mx = max(tree[2 * v].mx, tree[2 * v + 1].mx);
}

void update_point(vector<node> & tree, long long int i, long long int new_val, long long int v = 1, long long int vl = 0, long long int vr = n) {
    if (vr - vl == 1) {
        tree[v] = {new_val, new_val};
        return;
    }
    long long int vm = (vl + vr) / 2;
    if (i < vl || i >= vr)return;
    if (i < vm) {
        update_point(tree, i, new_val, 2 * v, vl, vm);
    }else {
        update_point(tree, i, new_val, 2 * v + 1, vm, vr);
    }
    recalc(tree, v);
}

long long int get_min(vector<node> & tree, long long int L, long long int R, long long int v = 1, long long int vl = 0, long long int vr = n){
    if (vl >= R || vr <= L)return INF;
    if (vr - vl <= 1){
        long long int m = tree[v].mn;
        tree[v].mn = INF;
        tree[v].mx = -INF;
        return m;
    }
    long long int vm = (vl + vr) / 2;
    long long int res_m = 0;
    if (tree[2 * v].mn < tree[2 * v + 1].mn){
        res_m = get_min(tree, L, R, 2 * v, vl, vm);
    }else{
        res_m = get_min(tree, L, R, 2 * v + 1, vm, vr);
    }
    recalc(tree, v);
    return res_m;
}

long long int get_max(vector<node> & tree, long long int L, long long int R, long long int v = 1, long long int vl = 0, long long int vr = n){
    if (vl >= R || vr <= L)return -INF;
    if (vr - vl <= 1){
        long long int m = tree[v].mx;
        tree[v].mx = -INF;
        tree[v].mn = INF;
        return m;
    }
    long long int vm = (vl + vr) / 2;
    long long int res_m = 0;
    if (tree[2 * v].mx > tree[2 * v + 1].mx){
        res_m = get_max(tree, L, R, 2 * v, vl, vm);
    }else{
        res_m = get_max(tree, L, R, 2 * v + 1, vm, vr);
    }
    recalc(tree, v);
    return res_m;
}


int main(){
    cin >> n;
    vector<node> tree(4 * n, {INF, -INF});
    int kol = 0;
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        if (s[0] == 'G'){
            if (s[4] == 'i'){
                cout << get_min(tree, 0, n) << endl;
            }
            else{
                cout << get_max(tree, 0, n) << endl;
            }
        }else{
            int a = stoi(s.substr(7, s.size() - 8));
            update_point(tree, kol, a);
            kol++;
        }
    }
    return 0;
}
