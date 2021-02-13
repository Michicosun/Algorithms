struct Hash{
    vector<long long int> h;
    vector<long long int> p;
    long long int b = 255;
    long long int m = 1e9 + 7;
    Hash(string & s){
        int n = (int)s.size();
        h = vector<long long int>(n + 1, 0);
        p = vector<long long int>(n + 1, 1);
        for(int i = 1; i <= n; i++){
            h[i] = (h[i - 1] * b + s[i - 1]) % m;
            p[i] = (p[i - 1] * b) % m;
        }
    }
    long long int get_hash_by_len(int ind, int len){
        return (h[ind + len - 1] - (h[ind - 1] * p[len]) % m + m) % m;
    }
    long long int get_hash_segm(int l, int r){
        return (h[r] - (h[l - 1] * p[r - l + 1]) % m + m) % m;
    }
};
