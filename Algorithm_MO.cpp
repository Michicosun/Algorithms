#include<iostream>
#include<cmath>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<set>
#include<deque>

using namespace std;

long long k;
long long cnt[1000000 + 10];

struct query{
    long long L, R, ind;
    query(long long L = 0, long long R = 0, long long ind = 0){
        this->L = L;
        this->R = R;
        this->ind = ind;
    }
};

bool cmp(const query & a, const query & b){
    return (a.L / k) < (b.L / k) || (a.L / k == b.L / k && a.R < b.R);
}

signed main(){
    long long n, t; cin >> n >> t;
    k = 400;
    vector<long long> a(n);
    vector<query> queries;
    vector<long long> res(t);
    for (long long i = 0; i < n; i++)cin >> a[i];
    for (long long i = 0; i < t; i++){
        long long l, r; cin >> l >> r; l--;
        queries.push_back(query(l, r, i));
    }
    sort(queries.begin(), queries.end(), cmp);
    long long l = 0, r = 0, ans = 0;
    for (long long i = 0; i < t; i++){
        long long L = queries[i].L;
        long long R = queries[i].R;
        long long ind = queries[i].ind;
        while (r < R){
            ans -= (cnt[a[r]] * cnt[a[r]] * a[r]);
            cnt[a[r]]++;
            ans += (cnt[a[r]] * cnt[a[r]] * a[r]);
            r++;
        }
        while (l > L){
            l--;
            ans -= cnt[a[l]] * cnt[a[l]] * a[l];
            cnt[a[l]]++;
            ans += cnt[a[l]] * cnt[a[l]] * a[l];
        }
        while (r > R){
            r--;
            ans -= cnt[a[r]] * cnt[a[r]] * a[r];
            cnt[a[r]]--;
            ans += cnt[a[r]] * cnt[a[r]] * a[r];
        }
        while (l < L){
            ans -= cnt[a[l]] * cnt[a[l]] * a[l];
            cnt[a[l]]--;
            ans += cnt[a[l]] * cnt[a[l]] * a[l];
            l++;
        }
        res[ind] = ans;
    }
    for (long long i = 0; i < t; i++)cout << res[i] << endl;
    return 0;
}
