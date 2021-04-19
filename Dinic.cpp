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

struct edge{
    int a, b, c, f;
    edge(int a = 0, int b = 0, int c = 0, int f = 0) : a(a), b(b), c(c), f(f) {}
};

const int INF = 1e15;

int n, m;
vector<vector<int>> g;
vector<edge> e;

int st, fn;

void addEdge(int a, int b, int c) {
    g[a].push_back(e.size());
    e.emplace_back(a, b, c, 0);
    g[b].push_back(e.size());
    e.emplace_back(b, a, 0, 0);
}

vector<int> d;

bool bfs() {
    d.assign(n, INF);
    d[st] = 0;
    queue<int> q; q.push(st);
    while (!q.empty()) {
        int a = q.front(); q.pop();
        for (auto id : g[a]) {
            int b = e[id].b;
            int canPush = e[id].c - e[id].f;
            if (canPush > 0 && d[b] > d[a] + 1) {
                d[b] = d[a] + 1;
                q.push(b);
            }
        }
    }
    return d[fn] < INF;
}

vector<int> ind;

int dfs(int v, int flow) {
    if (flow == 0) return 0;
    if (v == fn) return flow;
    for (; ind[v] < g[v].size(); ++ind[v]) {
        int id = g[v][ind[v]];
        int to = e[id].b;
        if (d[to] != d[v] + 1) continue;
        int canPush = e[id].c - e[id].f;
        int pushed = dfs(to, min(flow, canPush));
        if (pushed > 0) {
            e[id].f += pushed;
            e[id ^ 1].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

int Dinic() {
    int flow = 0;
    while (bfs()) {
        ind.assign(n, 0);
        while (int pushed = dfs(st, INF)) flow += pushed;
    }
    return flow;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        addEdge(a, b, c);
    }
    st = 0;
    fn = n - 1;
    cout << Dinic() << "\n";
    return 0;
}

