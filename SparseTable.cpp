struct sparseTable{
    int MAXLOGN = 30;
    vector<vector<pair<int, int>>> st;
    vector<int> maxLog;
    sparseTable(const vector<int> & a){
        getLog(a.size());
        st.resize(a.size(), vector<pair<int, int>>(MAXLOGN, {1e9, 1e9}));
        for (int i = 0; i < a.size(); i++){
            st[i][0] = {a[i], i};
        }
        for (int j = 1; j < MAXLOGN; j++){
            for (int i = 0; i + (1 << j) <= a.size(); i++){
                auto left = st[i][j - 1];
                auto right = st[i + (1 << (j - 1))][j - 1];
                if(left.first > right.first)st[i][j] = left;
                else st[i][j] = right;
            }
        }
    }
    
    void getLog(int n){
        maxLog.resize(n + 1);
        maxLog[0] = maxLog[1] = 0;
        for (int i = 2; i <= n; i++){
            maxLog[i] = maxLog[i / 2] + 1;
        }
    }
    
    pair<int, int> getQ(int l, int r){
        int j = maxLog[r - l + 1];
        auto left = st[l][j];
        auto right = st[r - (1 << j) + 1][j];
        if(left.first > right.first)return left;
        else return right;
    }
    
};
