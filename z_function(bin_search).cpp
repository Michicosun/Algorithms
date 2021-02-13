void prefix_func(string & s, vector<int> & ans){
    Hash h(s);
    for(int i = 0; i < s.size(); i++){
        int l = 0, r = (int)s.size() - i;
        while (r - l > 1) {
            int mid = (r + l) / 2;
            if(h.get_hash_segm(1, mid + 1) == h.get_hash_segm(i + 1, i + mid + 1)){
                l = mid;
            }else{
                r = mid;
            }
        }
        if(l == 0)ans[i] = (s[i] == s[0]);
        else ans[i] = l + 1;
    }
}
