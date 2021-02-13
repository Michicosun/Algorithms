#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int main(){
    const int INF = 1e9;
    int n, s, m;
    cin >> n >> s >> m;
    s--;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[b - 1].push_back(a - 1);
    }
    queue<int> q;
    vector<long long int> dist(n, INF);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()){
        int v = q.front(); q.pop();
        for (auto u : g[v]){
            if (dist[u] > dist[v] + 1){
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    for (auto i : dist){
        if (i == INF)cout << -1 << " ";
        else cout << i << " ";
    }
    return 0;
}
