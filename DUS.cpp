#include<iostream>
#include<vector>
#include<string>
#include<set>

using namespace std;

struct DUS{
    vector<int> mass;
    vector<int> size;
    DUS(int len = 0){
        mass = vector<int>(len, -1);
        size = vector<int>(len, -1);
    }
    int make_set(){
        int res = (int)mass.size();
        mass.push_back((int)mass.size());
        size.push_back(1);
        return res;
    }
    void make_set(int v){
        mass[v] = v;
        size[v] = 1;
    }
    int find_set(int v) {
        if(v > mass.size() || mass[v] == -1)return -1;
        if (v == mass[v]){
            return v;
        }
        return mass[v] = find_set(mass[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a != b){
            if(size[a] < size[b])
                swap (a, b);
            mass[b] = a;
            size[a] += size[b];
        }
    }
    void print(){
        cout << "mass = {";
        for(auto i : mass)cout << i << " ";
        cout << "}" << endl;
    }
    void print_sz(){
        cout << "size = {";
        for(auto i : size)cout << i << " ";
        cout << "}" << endl;
    }
};

int main(){
    return 0;
}
