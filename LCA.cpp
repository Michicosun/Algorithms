int max_log;
vector<vector<int>> dp;
vector<int> tin, tout;
int t = 0;

void paint(int v, int p, const vector<vector<pair<int, int>>> & g) {
    for (int l = 1; l < max_log; l++){
        dp[v][l] = dp[dp[v][l - 1]][l - 1];
    }
    tin[v] = t++;
    for (auto u : g[v]) {
        if(u.first != p){
            dp[u.first][0] = v;
            paint(u.first, v, g);
        }
    }
    tout[v] = t++;
}

bool ancestor(int u, int v) {
    return tin[u] <= tin[v] && tin[v] <= tout[u];
}

int LCA(int v, int u) {
    if (ancestor(v, u))return v;
    if (ancestor(u, v))return u;
    for (int l = max_log - 1; l >= 0; l--)
        if (!ancestor(dp[v][l], u))
            v = dp[v][l];
    return dp[v][0];
}

void init(int n, const vector<vector<pair<int, int>>> & g){
    max_log = 1;
    int max_log_ans = 1;
    while (max_log_ans <= n){
        max_log_ans *= 2;
        max_log += 1;
    }
    dp.resize(n, vector<int>(max_log, 0));
    tin.resize(n);
    tout.resize(n);
    paint(0, -1, g);
}
