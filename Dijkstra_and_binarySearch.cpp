#include<iostream>
#include<queue>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

const int INF = 1e9;
const int day = 24 * 60;
int n, m;

struct edge{
    int t, w, v;
    edge(int v, int t, int w){
        this->v = v;
        this->t = t;
        this->w = w;
    }
};

int d(vector<vector<edge>> & g, int start, int kol){
    vector<int> dist(n, INF);
    vector<bool> used(n, false);
    dist[start] = 0;
    int u = start;
    while (u != -1){
        used[u] = true;
        for (auto p : g[u]){
            int time = p.t, weight = p.w, vert = p.v;
            if (weight >= kol){
                dist[vert] = min(dist[vert], dist[u] + time);
            }
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
    return *dist.rbegin();
}

bool check(vector<vector<edge>> & g, int kol){
    int ans = d(g, 0, kol);
    if (ans <= day)return true;
    else return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    vector<vector<edge>> g(n);
    for (int i = 0; i < m; i++){
        int a, b, t, w;
        cin >> a >> b >> t >> w;
        a--; b--;
        w -= 3e6;
        g[a].push_back(edge(b, t, w));
        g[b].push_back(edge(a, t, w));
    }
    int l = -1, r = 1e9;
    while (r - l > 1){
        int mid = (l + r) / 2;
        if (check(g, mid)){
            l = mid;
        }else{
            r = mid;
        }
    }
    cout << ((l == -1) ? 0 : l / 100);
    return 0;
}
