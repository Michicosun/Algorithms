vector<int> tin, up;
vector<vector<pair<int, int>>> g;
vector<bool> used;
map<int, int> colors;
vector<int> k;
vector<pair<int, int>> bridges;
stack<int> st;

void paint(int v){
    int last = -1;
    while(last != v && !st.empty()){
        colors[maxColor]++;
        k[st.top()] = maxColor;
        last = st.top(); st.pop();
    }
    maxColor++;
}

void dfs(int v, int p = -1, int edge = -1){
    if(p == -1){
        tin[v] = 0;
    }else{
        tin[v] = tin[p] + 1;
    }
    up[v] = tin[v];
    used[v] = true;
    st.push(v);
    for(auto i : g[v]){
        if(!used[i.first]){
            dfs(i.first, v, i.second);
            up[v] = min(up[v], up[i.first]);
        }else if(i.second != edge){
            up[v] = min(up[v], tin[i.first]);
        }
    }
    if(p != -1 && tin[v] == up[v]){
        paint(v);
        bridges.push_back({p, v});
    }
}
