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

int n, m;

struct node{
    node * l;
    node * r;
    int summ;
    node(int summ = 0){
        this->l = nullptr;
        this->r = nullptr;
        this->summ = summ;
    }
    node(node * l, node * r){
        this->l = l;
        this->r = r;
        this->summ = 0;
        if (l)this->summ += l->summ;
        if (r)this->summ += r->summ;
    }
};

typedef node * pnode;

int get_summ(pnode r){
    if (r)return r->summ;
    else return 0;
}

vector<pnode> roots;

pnode build(int tl, int tr){
    if (tr - tl == 1){
        return new node(0);
    }else{
        int mid = (tl + tr) / 2;
        pnode left = build(tl, mid);
        pnode right = build(mid, tr);
        return new node(left, right);
    }
}

pnode update(pnode n, int tl, int tr, int ind, int d){
    if (tr - tl == 1){
        return new node(get_summ(n) + d);
    }else{
        int mid = (tl + tr) / 2;
        if (ind < mid){
            return new node(update(n->l, tl, mid, ind, d), n->r);
        }else{
            return new node(n->l, update(n->r, mid, tr, ind, d));
        }
    }
}

void print(pnode r, int tl = 0, int tr = n){
    if (r){
        cout << tl << " " << tr << " : " << get_summ(r) << " l = " << get_summ(r->l) << " r = " << get_summ(r->r) << endl;
        print(r->l, tl, (tl + tr) / 2);
        print(r->r, (tl + tr) / 2, tr);
    }
}

int getL(pnode r, int k, int tl, int tr){
    if (tr - tl == 1)return tl;
    else{
        int mid = (tl + tr) / 2;
        if (get_summ(r->l) >= k)return getL(r->l, k, tl, mid);
        else return getL(r->r, k - get_summ(r->l), mid, tr);
    }
}

signed main() {
    cin >> n >> m;
    vector<int> a(n);
    roots.push_back(build(0, n));
    for (int i = 0; i < n; i++)cin >> a[i];
    vector<int> last_ind(m + 1, -1);
    for (int i = n - 1; i >= 0; i--){
        if (last_ind[a[i]] == -1){
            last_ind[a[i]] = i;
            roots.push_back(update(roots.back(), 0, n, i, 1));
        }else{
            roots.push_back(update(roots.back(), 0, n, last_ind[a[i]], -1));
            roots.back() = update(roots.back(), 0, n, i, 1);
            last_ind[a[i]] = i;
        }
    }
    reverse(roots.begin(), roots.end());
    int q; cin >> q;
    int p = 0;
    for (int i = 0; i < q; i++){
        int x, y; cin >> x >> y;
        int l = ((x + p) % n);
        int k = ((y + p) % m) + 1;
        if (get_summ(roots[l]) < k)p = -1;
        else p = getL(roots[l], k, 0, n);
        p++;
        cout << p << endl;
    }
    return 0;
}
