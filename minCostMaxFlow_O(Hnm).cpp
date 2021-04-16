vector<vector<int>> w, f, c;

struct edge {
    int a, b, w;
    edge(int a = 0, int b = 0, int w = 0) : a(a), b(b), w(w) {}
};

vector<edge> build() {
    vector<edge> ans;
    for (int i = 0; i < 2 * k + 2; ++i) {
        for (int j = 0; j < 2 * k + 2; ++j) {
            if (i == j) continue;
            int c0 = c[i][j] - f[i][j];
            if (c0 > 0) ans.push_back({i, j, w[i][j]});
        }
    }
    return ans;
}

const int INF = 1e15;

vector<int> getPath(int st, const vector<edge>& edges) {
    vector<int> d(2 * k + 2, INF); d[st] = 0;
    vector<int> p(2 * k + 2, -1);
    for (int w = 0; w < 2 * k + 2; ++w) {
        bool has_path = false;
        for (const auto& e : edges) {
            if (d[e.a] < INF) {
                if (d[e.b] > d[e.a] + e.w) {
                    d[e.b] = d[e.a] + e.w;
                    p[e.b] = e.a;
                    has_path = true;
                }
            }
        }
        if (!has_path) break;
    }
    
    if (d[2 * k + 1] == INF) return {};
    else {
        vector<int> path;
        for (int cur = 2 * k + 1; cur != -1; cur = p[cur]) path.push_back (cur);
        reverse (path.begin(), path.end());
        return path;
    }
}

bool pushFlow(const vector<int>& path) {
    if (path.empty()) return 0;
    int sz = path.size();
    for (int i = 1; i < sz; ++i) {
        ++f[path[i - 1]][path[i]];
        --f[path[i]][path[i - 1]];
    }
    return 1;
}

void minCostMaxFlow() {
    while (true) {
        auto edges = build();
        auto path = getPath(0, edges);
        if (!pushFlow(path)) return;
    }
}
