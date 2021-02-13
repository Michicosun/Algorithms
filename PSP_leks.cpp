#include<iostream>
#include<vector>

using namespace std;

void go(int i, int bal, int n, string pref){
    if(i == 2 * n){
        cout << pref << endl;
        return;
    }
    if(2 * n - (i + 1) >= bal){
        pref.push_back('(');
        go(i + 1, bal + 1, n, pref);
        pref.pop_back();
    }
    if(bal > 0){
        pref.push_back(')');
        go(i + 1, bal - 1, n, pref);
        pref.pop_back();
    }
}

int main(){
    int n;
    cin >> n;
    go(0, 0, n, "");
    return 0;
}
