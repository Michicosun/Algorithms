#include<iostream>
#include<queue>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

const int INF = 1e9;
int n;

int d(vector<vector<pair<int, int>>> & g, int start){
    vector<int> dist(n, INF);
    vector<bool> used(n, false);
    dist[start] = 0;
    int u = start;
    while (u != -1){
        used[u] = true;
        for (auto p : g[u]){
            int v = p.first, w = p.second;
            dist[v] = min(dist[v], max(dist[u], w));
        }
        int min_dist = INF;
        u = -1;
        for (int i = 0; i < n; i++){
            if (!used[i] && min_dist > dist[i]){
                min_dist = dist[i];
                u = i;
            }
        }
    }
    return *(max_element(dist.begin(), dist.end()));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<vector<pair<int, int>>> gr(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int a;
            cin >> a;
            g[i].push_back({j, a});
            gr[j].push_back({i, a});
        }
    }
    int d1 = d(g, 0);
    int d2 = d(gr, 0);
    cout << max(d1, d2);
    return 0;
}
