#include<iostream>
#include<algorithm>
#include<map>
#include<string>
#include<cstdlib>
#include<vector>

#define int long long int

using namespace std;

struct node{
    int x, y, d;
    node* left;
    node* right;
    node(int val){
        this->x = val;
        this->y = rand();
        this->d = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~node(){
        if(this->left)delete this->left;
        if(this->right)delete this->right;
    }
};

typedef node* pnode;



int cnt(pnode t) {
    if(t)return t->d;
    else return 0;
}

void recalc(pnode t) {
    if(t)t->d = 1 + cnt(t->left) + cnt(t->right);
}

pair<pnode, pnode> split(pnode root, int val){
    if(root == nullptr)return {nullptr, nullptr};
    if(root->x <= val){
        auto res = split(root->right, val);
        root->right = res.first;
        recalc(root);
        recalc(res.second);
        return {root, res.second};
    }else{
        auto res = split(root->left, val);
        root->left = res.second;
        recalc(res.first);
        recalc(root);
        return {res.first, root};
    }
}

pnode merge(pnode left, pnode right){
    if(left == nullptr)return right;
    if(right == nullptr)return left;
    if(left->y <= right->y){
        left->right = merge(left->right, right);
        recalc(left);
        return left;
    }else{
        right->left = merge(left, right->left);
        recalc(right);
        return right;
    }
}

bool exists(pnode root, int val){
    if(root == nullptr)return false;
    if(root->x == val)return true;
    else if(root->x > val)return exists(root->left, val);
    else return exists(root->right, val);
}

pnode insert(pnode root, int val){
    if(exists(root, val))return root;
    else{
        auto res = split(root, val);
        pnode newnode = new node(val);
        return merge(merge(res.first, newnode), res.second);
    }
}

pnode erase(pnode root, int val){
    if(!exists(root, val))return root;
    else{
        auto res1 = split(root, val);
        auto res = split(res1.first, val - 1);
        return merge(res.first, res1.second);
    }
}

void print(pnode root){
    if(root == nullptr)return;
    else{
        print(root->left);
        cout << "{ " << root->x << " left = ";
        if(root->left)cout << root->left->x << "  right = ";
        else cout << "--  right = ";
        if(root->right)cout << root->right->x << "}\n";
        else cout << "--}\n";
        print(root->right);
    }
}

int get_depth(pnode root){
    if(root == nullptr)return 0;
    else return 1 + max(get_depth(root->left), get_depth(root->right));
}

int get_kth(pnode root, int k){
    if(root == nullptr)return -1;
    else if(cnt(root->left) + 1 == k)return root->x;
    else if(cnt(root->left) >= k)return get_kth(root->left, k);
    else return get_kth(root->right, k - cnt(root->left) - 1);
}

signed main(){
    pnode root = nullptr;
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 2);
    root = insert(root, 9);
    root = insert(root, 7);
    root = insert(root, 18);
    print(root);
    cout << get_depth(root) << endl;
    cout << get_kth(root, 1);
    return 0;
}
