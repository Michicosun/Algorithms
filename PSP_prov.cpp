#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<stack>
#include<vector>

using namespace std;

int main(){
    stack<char> a;
    string s;
    cin >> s;
    for (char c : s){
        if (strchr("([{", c)){
            a.push(c);
        }else if (a.size() > 0 && abs(a.top() - c) <= 2){
            a.pop();
        }else{
            cout << "NO";
            return 0;
        }
    }
    if(a.size() == 0)cout << "YES";
    else cout << "NO";
    return 0;
}
