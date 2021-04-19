#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<set>
#include<random>
#include<algorithm>
#include<queue>
#include<stack>
#include<deque>
#include<bitset>
#include<cstdio>
#include<cassert>
#include<sstream>
#include<set>
#include<list>

#define int long long int

using namespace std;

struct edge {
    int a, b, cap, cost, flow, id_back;
    edge(int a = 0, int b = 0, int cap = 0, int cost = 0, int flow = 0, int id_back = 0) {
        this->a = a;
        this->b = b;
        this->cap = cap;
        this->cost = cost;
        this->flow = flow;
        this->id_back = id_back;
    }
};

int n, m, k;
vector<edge> edge;
vector<vector<int>> indReal;

void addEdge(int a, int b, int cap, int cost) {
    int sz = edge.size();
    indReal.back().push_back(sz);
    edge.emplace_back(a, b, cap, cost, 0, sz + 1);
    edge.emplace_back(b, a, 0, -cost, 0, sz);
};

const int INF = 1e15;

vector<int> getPath(int st, int fn) {
    vector<int> d(n, INF); d[st] = 0;
    vector<pair<int, int>> pr(n, {-1, -1});
    for (int r = 0; r < n; ++r) {
        for (int id = 0; id < edge.size(); ++id) {
            const auto& e = edge[id];
            int a = e.a, b = e.b, canPush = e.cap - e.flow, cost = e.cost;
            if (canPush > 0 && d[b] > d[a] + cost) {
                d[b] = d[a] + cost;
                pr[b] = {a, id};
            }
        }
    }
    if (d[fn] > 1e14) return {};
    else {
        vector<int> path;
        while (fn != -1) {
            if (pr[fn].second > -1) path.push_back(pr[fn].second);
            fn = pr[fn].first;
        }
        reverse(path.begin(), path.end());
        return path;
    }
}

bool pushFlow(const vector<int>& path) {
    if (path.empty()) return 0;
    for (auto id : path) {
        ++edge[id].flow;
        --edge[edge[id].id_back].flow;
    }
    return 1;
}

int minCostMaxFlow(int k) {
    int flow = 0;
    for (int i = 0; i < k; ++i) {
        auto path = getPath(0, n - 1);
        if (!pushFlow(path)) break;
        else ++flow;
    }
    return flow;
}

vector<vector<pair<int, int>>> g;
vector<vector<int>> ans;

void dfs(int v, vector<int>& path) {
    if (!g[v].empty()) {
        path.push_back(g[v].back().second);
        dfs(g[v].back().first, path);
        g[v].pop_back();
    }
}

signed main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        indReal.push_back({});
        addEdge(a, b, 1, w);
        addEdge(b, a, 1, w);
    }
    int flow = minCostMaxFlow(k);
    if (flow < k) {
        cout << -1 << "\n";
        return 0;
    }
    int sumCost = 0;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        for (auto id : indReal[i]) {
            if (edge[id].flow > 0) {
                sumCost += edge[id].flow * edge[id].cost;
                g[edge[id].a].push_back({edge[id].b, i});
            }
        }
    }
    while (!g[0].empty()) {
        vector<int> path;
        dfs(0, path);
        ans.push_back(path);
    }
    cout.precision(20);
    cout << 1.0 * sumCost / k << "\n";
    for (const auto& i : ans) {
        cout << i.size() << " ";
        for (auto j : i) cout << j + 1 << " ";
        cout << "\n";
    }
    return 0;
}
