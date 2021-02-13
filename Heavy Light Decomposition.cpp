#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define int long long int

using namespace std;

const int maxLog = 30;
int timer = 0;
vector<vector<int>> g;
vector<int> sz;
vector<int> tin;
vector<int> GetRoot;
vector<int> levels;
vector<int> a;
vector<vector<int>> dp;

struct SegmentTree{
private:
    vector<int> tree;
    void build(int v, int tl, int tr, const vector<int> & a){
        if(tr - tl == 1){
            tree[v] = a[tl];
        }else{
            int mid = (tl + tr) / 2;
            build(2 * v + 1, tl, mid, a);
            build(2 * v + 2, mid, tr, a);
            tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
    
    int query1(int L, int R, int v, int tl, int tr){
        if(tr <= L || tl >= R || tr - tl < 1)return -1e9;
        else if(L <= tl && tr <= R)return tree[v];
        else{
            int mid = (tl + tr) / 2;
            auto left = query1(L, R, 2 * v + 1, tl, mid);
            auto right = query1(L, R, 2 * v + 2, mid, tr);
            return max(left, right);
        }
    }
    
    void query2(int ind, int val, int v, int tl, int tr){
        if(tl > ind || tr <= ind || tr - tl < 1)return;
        else if(tr - tl == 1)tree[v] = val;
        else{
            int mid = (tl + tr) / 2;
            if(ind >= mid)query2(ind, val, 2 * v + 2, mid, tr);
            else query2(ind, val, 2 * v + 1, tl, mid);
            tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
public:
    SegmentTree(const vector<int> & a){
        tree.resize(4 * a.size());
        build(0, 0, a.size(), a);
    }
    
    int getMax(int L, int R){
        return query1(L, R, 0, 0, a.size());
    }
    
    void change(int ind, int val){
        query2(ind, val, 0, 0, a.size());
    }
    
};

void get_size(int v = 0, int p = 0){
    sz[v] = 1;
    int maxSizeInd = -1;
    int pos = -1;
    for(auto to : g[v]){
        pos++;
        if(to == p)continue;
        get_size(to, v);
        sz[v] += sz[to];
        if(maxSizeInd == -1 || sz[to] > sz[g[v][maxSizeInd]]) {
            maxSizeInd = pos;
        }
    }
    if(maxSizeInd > -1)swap(g[v][0], g[v][maxSizeInd]);
}

void hld(int v = 0, int p = 0, int root = -1){
    tin[v] = timer++;
    a.push_back(levels[v]);
    dp[v][0] = p;
    if(root == -1)root = v;
    GetRoot[v] = root;
    bool continuePath = true;
    for(auto to : g[v]) {
        if(to == p)continue;
        if(continuePath){
            hld(to, v, root);
            continuePath = false;
        }else hld(to, v);
    }
}

int isParent(int a, int b) {
    return tin[a] <= tin[b] && tin[b] <= tin[a] + sz[a] - 1;
}

int LCA(int a, int b){
    if(isParent(a, b))return a;
    if(isParent(b, a))return b;
    for(int p = maxLog - 1; p >= 0; p--){
        if(!isParent(dp[a][p], b)){
            a = dp[a][p];
        }
    }
    return dp[a][0];
}

void init(int n){
    g.resize(n);
    sz.resize(n);
    tin.resize(n);
    GetRoot.resize(n);
    levels.resize(n);
    dp.resize(n, vector<int>(maxLog));
}

void PreProcess(int n){
    get_size();
    hld();
    for(int p = 1; p < maxLog; p++){
        for(int v = 0; v < n; v++){
            dp[v][p] = dp[dp[v][p - 1]][p - 1];
        }
    }
}

int getAns(int u, int v, SegmentTree & tree){
    int w = LCA(u, v);
    int ans = 0;
    while(!isParent(GetRoot[u], w)){
        ans = max(ans, tree.getMax(tin[GetRoot[u]], tin[u] + 1));
        u = dp[GetRoot[u]][0];
    }
    ans = max(ans, tree.getMax(tin[w], tin[u] + 1));
    while(!isParent(GetRoot[v], w)){
        ans = max(ans, tree.getMax(tin[GetRoot[v]], tin[v] + 1));
        v = dp[GetRoot[v]][0];
    }
    ans = max(ans, tree.getMax(tin[w], tin[v] + 1));
    return ans;
}

signed main(){
    int n; cin >> n;
    init(n);
    for(int i = 0; i < n; i++)cin >> levels[i];
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v; u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    PreProcess(n);
    SegmentTree tree(a);
    int k; cin >> k;
    for(int i = 0; i < k; i++){
        char c;
        int l, r;
        cin >> c >> l >> r;
        if(c == '?'){
            cout << getAns(l - 1, r - 1, tree) << endl;
        }else{
            tree.change(tin[l - 1], r);
        }
    }
    return 0;
}
