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

int n;
vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<int> ans;

void dfs(int v){
    while (!g[v].empty()){
        if (!used[g[v].back().second]){
            auto to = g[v].back();
            used[to.second] = true;
            g[v].pop_back();
            dfs(to.first);
        }else{
            g[v].pop_back();
        }
    }
    ans.push_back(v);
}

signed main(){
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    cin >> n;
    g.resize(n);
    int start = 0;
    int ind = 0;
    int summ = 0;
    for (int i = 0; i < n; i++){
        int k; cin >> k;
        summ += k;
        if (k % 2 == 1){
            start = i;
        }
        for (int j = 0; j < k; j++){
            int to; cin >> to; to--;
            if (i <= to){
                g[i].push_back({to, ind});
                g[to].push_back({i, ind});
                ind++;
            }
        }
    }
    used.resize(ind, false);
    dfs(start);
    assert(summ / 2 == ans.size() - 1);
    cout << ans.size() - 1 << endl;
    for (auto i : ans)cout << i + 1 << " ";
    return 0;
}
