#include<iostream>
#include<queue>
#include<map>
#include<vector>

using namespace std;

int n, m;

const vector<vector<int>> ways = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<vector<int>> g;

const int INF = 1e9;

struct vert{
    int x, y, d;
    vert(int x = 0, int y = 0, int d = 0){
        this->x = x;
        this->y = y;
        this->d = d;
    }
    
    bool can_go(){
        vector<int> w = ways[d];
        int dx = x + w[0];
        int dy = y + w[1];
        return dx >= 0 && dx < n && dy >= 0 && dy < m && g[dx][dy] != 1;
    }
    
    vert go(){
        vector<int> w = ways[d];
        vert next_vert = vert(x + w[0], y + w[1], d);
        return next_vert;
    }
    
    vert rotate(){
        vert rot_vert = vert(x, y, (d + 1) % 4);
        return rot_vert;
    }
};

bool operator < (const vert & a, const vert & b){
    auto p1 = make_pair(a.x, make_pair(a.y, a.d));
    auto p2 = make_pair(b.x, make_pair(b.y, b.d));
    return p1 < p2;
}

void relax(queue<vert> & q, map<vert, int> & dist, vert & v){
    if (v.can_go()){
        vert new_v = v.go();
        if (dist[new_v] > dist[v] + 1 || dist[new_v] == 0){
            dist[new_v] = dist[v] + 1;
            q.push(new_v);
        }
    }
    vert new_v = v.rotate();
    if (new_v.can_go()){
        new_v = new_v.go();
        if (dist[new_v] > dist[v] + 1 || dist[new_v] == 0){
            dist[new_v] = dist[v] + 1;
            q.push(new_v);
        }
    }
}

int bfs(int x1, int y1, int x2, int y2){
    queue<vert> q;
    map<vert, int> dist;
    q.push(vert(x1, y1, 0));
    q.push(vert(x1, y1, 1));
    q.push(vert(x1, y1, 2));
    q.push(vert(x1, y1, 3));
    dist[vert(x1, y1, 0)] = 0;
    dist[vert(x1, y1, 1)] = 0;
    dist[vert(x1, y1, 2)] = 0;
    dist[vert(x1, y1, 3)] = 0;
    while (!q.empty()){
        vert v = q.front(); q.pop();
        relax(q, dist, v);
    }
    int ans = INF;
    for (int i = 0; i < 4; i++){
        vert f = vert(x2, y2, i);
        if (dist[f] != 0){
            ans = min(dist[f], ans);
        }
    }
    return ans;
}

int main(){
    cin >> n >> m;
    string s;
    getline(cin, s);
    int x1, y1, x2, y2;
    g = vector<vector<int>>(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++){
        getline(cin, s);
        for (int j = 0; j < m; j++){
            if (s[j] == 'X')g[i][j] = 1;
            else if (s[j] == 'S'){
                x1 = i;
                y1 = j;
            }else if (s[j] == 'F'){
                x2 = i;
                y2 = j;
            }
        }
    }
    cout << bfs(x1, y1, x2, y2);
    return 0;
}
