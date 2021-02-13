int n;
const int maxN = 101;

void getSuffArray(vector<int> & s, vector<int> & p){
    p.resize(n);
    vector<int> c(n), cnt(maxN, 0);
    for (int i = 0; i < n; i++)cnt[s[i]]++;
    for (int i = 1; i < maxN; i++)cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int cl = 1;
    for (int i = 1; i < n; i++){
        if (s[p[i]] != s[p[i - 1]])cl++;
        c[p[i]] = cl - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++){
        for (int i = 0; i < n; i++){
            pn[i] = (p[i] - (1 << h) + n) % n;
        }
        cnt.assign(cl, 0);
        for (int i = 0; i < n; i++){
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < cl; i++){
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--){
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        cl = 1;
        for (int i = 1; i < n; i++){
            int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
            if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])cl++;
            cn[p[i]] = cl - 1;
        }
        swap(c, cn);
    }
}
