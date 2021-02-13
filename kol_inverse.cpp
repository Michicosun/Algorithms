#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>

using namespace std;

long long int ans = 0;

void merge(vector<int> & a, vector<int> & buf, int l, int m, int r){
    int i = l, j = m + 1;
    for(int k = l; k <= r; k++){
        if(j > r || (i <= m && a[i] <= a[j])){
            buf[k] = a[i++];
        }else{
            buf[k] = a[j++];
            ans += m + 1 - i;
        }
    }
    for(int i = l; i <= r; i++){
        a[i] = buf[i];
    }
}

void mergeSort(vector<int> & a, vector<int> & buf, int l, int r){
    if(l >= r)return;
    else{
        int m = (l + r) / 2;
        mergeSort(a, buf, l, m);
        mergeSort(a, buf, m + 1, r);
        
        merge(a, buf, l, m, r);
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> buf(n);
    for(int i = 0; i < n; i++)scanf("%d", &a[i]);
    mergeSort(a, buf, 0, (int)a.size() - 1);
    cout << ans;
    return 0;
}
