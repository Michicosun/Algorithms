void find_bridges(int v, int p = -1, int ind = -1){
    if(p == -1)d[v] = 0;
    else d[v] = d[p] + 1;
    used[v] = true;
    dp[v] = d[v];
    for(auto to : g[v]){
        if(!used[to.first]){
            find_bridges(to.first, v, to.second);
            dp[v] = min(dp[v], dp[to.first]);
        }else if(ind != to.second){
            dp[v] = min(dp[v], d[to.first]);
        }
    }
    if(p != -1 && dp[v] == d[v]){
        bridges.insert(ind);
    }
}
