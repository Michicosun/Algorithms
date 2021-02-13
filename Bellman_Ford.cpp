#include<iostream>
#include<vector>

using namespace std;

const int INF = 1e9;

struct edge{
    int s, f, w;
    edge(int s = 0, int f = 0, int w = 0){
        this->s = s;
        this->f = f;
        this->w = w;
    }
};

int main(){
    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f;
    vector <int> dist(n + 1, INF);
    vector <int> dist_new;
    dist[s] = 0;
    vector <edge> edges(m);
    for (int i = 0; i < m; ++i){
        cin >> edges[i].s >> edges[i].f >> edges[i].w;
    }
    for (int i = 0; i < k; ++i){
        dist_new = dist;
        for (auto & edge : edges){
            int start = edge.s;
            int end = edge.f;
            int price = edge.w;
            if (dist[start] + price < dist_new[end])
                dist_new[end] = dist[start] + price;
        }
        swap(dist, dist_new);
    }
    if (dist[f] == INF)
        cout << -1 << endl;
    else
        cout << dist[f] << endl;
    return 0;
}
