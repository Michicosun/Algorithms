#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

int n;

void build(vector<long long int> & a, vector<long long int> & tree, int v = 1, int vl = 0, int vr = n) {
    if (vr - vl == 1) {
        tree[v] = a[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(a, tree, 2 * v, vl, vm);
    build(a, tree, 2 * v + 1, vm, vr);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update_point(vector<long long int> & tree, int i, int new_val, int v = 1, int vl = 0, int vr = n) {
    if (vr - vl == 1) {
        tree[v] = new_val;
        return;
    }
    int vm = (vl + vr) / 2;
    if (i < vm) {
        update_point(tree, i, new_val, 2 * v, vl, vm);
    }else {
        update_point(tree, i, new_val, 2 * v + 1, vm, vr);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

long long int sum_on_seg(vector<long long int> & tree, int L, int R, int v = 1, int vl = 0, int vr = n) {
    if (L <= vl && vr <= R) return tree[v];
    if (vr <= L || R <= vl) return 0;
    int vm = (vl + vr) / 2;
    return sum_on_seg(tree, L, R, 2 * v, vl, vm) + sum_on_seg(tree, L, R, 2 * v + 1, vm, vr);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x, y, m;
    char c;
    cin >> n >> m;
    vector<long long int> a(n, 0);
    vector<long long int> tree(4 * n);
    build(a, tree);
    for (int i = 0; i < m; i++){
        cin >> c >> x >> y;
        if (c == 'A'){
            update_point(tree, x - 1, y);
        }else{
            cout << sum_on_seg(tree, x - 1, y) << endl;
        }
    }
    return 0;
}
