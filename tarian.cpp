#pragma GCC optimize("Ofast,fast-math,inline,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,popcnt")
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <set>
#include <stack>

using namespace std;

const int maxN = 75000;

unsigned int c[maxN];
unsigned int arr[maxN];
vector<int> ind[maxN];
int st[maxN];

struct dsu{
    int p[maxN];
    int r[maxN];
    unsigned int ans[maxN];
    void init(int n){
        for (int i = 0; i < n; ++i){
            p[i] = i;
            ans[i] = arr[i];
        }
    }
    int getParent(int v){
        if (p[v] == v)return v;
        else return p[v] = getParent(p[v]);
    }
    void unite(int a, int b){
        a = getParent(a);
        b = getParent(b);
        if (a != b){
            if (r[a] > r[b])swap(a, b);
            p[a] = b;
            if (r[a] == r[b])r[b]++;
            ans[b] = min(ans[a], ans[b]);
        }
    }
    long long int getAns(int v){
        v = getParent(v);
        return ans[v];
    }
};

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    long long int a, b; cin >> n >> m >> a >> b;
    dsu s;
    while (n != 0 || m != 0 || a != 0 || b != 0){
        for (int i = 1; i <= 2 * m + n; ++i){
            c[i] = (a * i + b);
        }
        for (int i = 1; i <= n; ++i){
            arr[i - 1] = c[i];
        }
        for (int i = n + 1; i <= n + 2 * m - 1; i += 2){
            int f = c[i] % n;
            int s = c[i + 1] % n;
            if (f > s)swap(f, s);
            ind[s].push_back(f);
        }
        s.init(n);
        int st_ind = -1;
        long long int summ = 0;
        for (int i = 0; i < n; i++){
            while (st_ind > -1 && arr[st[st_ind]] >= arr[i]){
                s.unite(st[st_ind], i);
                st_ind--;
            }
            st[++st_ind] = i;
            while (!ind[i].empty()){
                int l = ind[i].back();
                summ += s.getAns(l);
                ind[i].pop_back();
            }
        }
        cout << summ << endl;
        cin >> n >> m >> a >> b;
    }
    return 0;
}
