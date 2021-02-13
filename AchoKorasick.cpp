#include<iostream>
#include<cmath>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<set>
#include<deque>

using namespace std;

struct node{
    char c;
    bool term;
    bool used;
    node * suffLink;
    node * pred;
    node * termlink;
    vector<node *> suffGo;
    vector<node *> next;
    vector<int> ind;
    node(){
        this->used = false;
        this->pred = nullptr;
        this->suffLink = nullptr;
        this->termlink = nullptr;
        this->suffGo.resize(26, nullptr);
        this->next.resize(26, nullptr);
        this->term = false;
        this->c = 0;
        this->ind = {};
    }
};

typedef node * pnode;
pnode root;

void add(const string & s, int ind){
    pnode v = root;
    for (int i = 0; i < s.size(); i++){
        int c = s[i] - 'a';
        if (v->next[c] == nullptr){
            v->next[c] = new node();
            v->next[c]->pred = v;
            v->next[c]->c = c;
        }
        v = v->next[c];
    }
    v->term = true;
    v->ind.push_back(ind);
}

void print(pnode v, string s){
    if (!v)return;
    else if (v->term)cout << s << endl;
    else{
        for (int i = 0; i < 26; i++){
            char c = (char)(i + 'a');
            if (v->next[i]){
                s.push_back(c);
                print(v->next[i], s);
                s.pop_back();
            }
        }
    }
}

pnode go(pnode v, char c);

pnode get_link(pnode v){
    if (v->suffLink == nullptr){
        if (v == root || v->pred == root){
            v->suffLink = root;
        }else{
            v->suffLink = go(get_link(v->pred), v->c);
        }
    }
    return v->suffLink;
}

pnode go(pnode v, char c){
    if (v->suffGo[c] == nullptr){
        if (v->next[c] != nullptr){
            v->suffGo[c] = v->next[c];
        }else{
            if (v == root)v->suffGo[c] = root;
            else v->suffGo[c] = go(get_link(v), c);
        }
    }
    return v->suffGo[c];
}

pnode getTerm(pnode v){
    if (v == root)return root;
    if (v->termlink == nullptr){
        if (get_link(v)->term)v->termlink = get_link(v);
        else v->termlink = getTerm(get_link(v));
    }
    return v->termlink;
}

void init(){
    root = new node();
    root->pred = root;
    root->suffLink = root;
    root->termlink = root;
}

void calc(pnode v, vector<bool> & is){
    if (v->used)return;
    if (v->term){
        for (auto ind : v->ind){
            is[ind] = true;
        }
    }
    v->used = true;
    calc(getTerm(v), is);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        add(s, i);
    }
    vector<bool> is(n, false);
    string t; cin >> t;
    pnode v = root;
    for (int i = 0; i < t.size(); i++){
        char c = (t[i] - 'a');
        v = go(v, c);
        calc(v, is);
    }
    for (auto i : is){
        if (i)cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}

