#include<iostream>
#include<cmath>
#include<map>
#include<stack>
#include<set>
#include<queue>
#include<algorithm>
#include<vector>

#define int long long int

using namespace std;

vector<bool> used;
vector<int> matching;
vector<vector<int>> g;

bool dfs(int v){
    if(used[v])return false;
    used[v] = true;
    for(auto to : g[v]){
        if(matching[to] == -1 || dfs(matching[to])){
            matching[to] = v;
            matching[v] = to;
            return true;
        }
    }
    return false;
}

signed main(){
    int n, s; cin >> n >> s;
    g.resize(n + s);
    for(int i = 0; i < n; i++){
        for(int j = n; j < n + s; j++){
            int num; cin >> num;
            if(num == 1)g[i].push_back(j);
        }
    }
    matching.resize(n + s, -1);
    used.resize(n + s, false);
    for(int i = 0; i < n; i++){
        used.clear();
        used.resize(n + s, false);
        dfs(i);
    }
    int kol = 0;
    for(int i = 0; i < n; i++){
        kol += (matching[i] != -1);
    }
    cout << kol;
    return 0;
}
