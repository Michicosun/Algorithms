#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

void Quick(vector<int> & a, int l, int r){
    cout << l << r << endl;
    if(l >= r)return;
    else{
        int ind = l + rand() % (r - l + 1);
        int x = a[ind];
        int i = l, j = r;
        while(i <= j){
            while(a[i] <= x)i++;
            while(a[j] > x)j--;
            if(i <= j)swap(a[i++], a[j--]);
        }
        Quick(a, i, r);
        Quick(a, l, j);
    }
}


int main(){
    vector<int> a = {5, 4, 3, 2, 1};
    Quick(a, 0, a.size() - 1);
    for(auto i : a)cout << i << " ";
    return 0;
}
