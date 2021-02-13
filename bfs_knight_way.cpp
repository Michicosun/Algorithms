#include<iostream>
#include<queue>
#include<map>
#include<vector>

using namespace std;

const vector<pair<int, int>> ways = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

int main(){
    const int n = 8;
    const int INF = 1e9;
    char c1, c2;
    int s, f;
    cin >> c1 >> s >> c2 >> f;
    s--; f--;
    map<char, vector<pair<char, int>>> prev;
    map<char, vector<int>> dist;
    for (int i = 0; i < n; i++){
        prev['a' + i] = vector<pair<char, int>>(n);
        dist['a' + i] = vector<int>(n, INF);
    }
    queue<pair<char, int>> q;
    dist[c1][s] = 0;
    q.push({c1, s});
    while (!q.empty()){
        auto v = q.front(); q.pop();
        for (auto p : ways){
            pair<char, int> new_p = {v.first + p.first, v.second + p.second};
            if (new_p.first >= 'a' && new_p.first <= 'h' && new_p.second >= 0 && new_p.second < n){
                if (dist[new_p.first][new_p.second] > dist[v.first][v.second] + 1){
                    dist[new_p.first][new_p.second] = dist[v.first][v.second] + 1;
                    prev[new_p.first][new_p.second] = v;
                    q.push(new_p);
                }
            }
        }
    }
    vector<pair<char, int>> ans;
    while (dist[c2][f] != 0){
        ans.push_back({c2, f + 1});
        auto p = prev[c2][f];
        c2 = p.first;
        f = p.second;
    }
    ans.push_back({c2, f + 1});
    for (auto it = ans.rbegin(); it != ans.rend(); it++){
        cout << (*it).first << (*it).second << endl;
    }
    return 0;
}
