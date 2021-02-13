vector<int> z(string s){
    int n = (int)s.size();
    vector<int> ans(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++){
        if (i <= r){
            ans[i] = min(r - i + 1, ans[i - l]);
        }
        while (i + ans[i] < n && s[ans[i]] == s[i + ans[i]]){
            ans[i] += 1;
        }
        if (i + ans[i] - 1 > r){
            l = i;
            r = i + ans[i] - 1;
        }
    }
    return ans;
}

