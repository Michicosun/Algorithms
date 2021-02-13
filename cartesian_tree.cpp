mt19937 mt_rand(42);

struct node{
    int data, y, size;
    bool reversed;
    int summ;
    node * left;
    node * right;
    node(int data = 0){
        this->data = data;
        this->summ = data;
        this->y = mt_rand();
        this->size = 1;
        this->reversed = false;
        this->left = nullptr;
        this->right = nullptr;
    }
};

typedef node * pnode;

class cartesianTree{
public:
    pnode root;
    
    int getSize(pnode tree){
        if(!tree)return 0;
        else return tree->size;
    }
    
    int getSumm(pnode tree){
        if(!tree)return 0;
        else return tree->summ;
    }
    
    void recalc(pnode tree){
        if(!tree)return;
        else{
            tree->size = getSize(tree->left) + getSize(tree->right) + 1;
            tree->summ = tree->data + getSumm(tree->left) + getSumm(tree->right);
        }
    }
    
    void push(pnode tree){
        if(!tree)return;
        if(!tree->reversed)return;
        pnode p = tree->left;
        tree->left = tree->right;
        tree->right = p;
        if(tree->left)tree->left->reversed ^= true;
        if(tree->right)tree->right->reversed ^= true;
        tree->reversed = false;
    }
    
    pair<pnode, pnode> split(pnode tree, int x){
        if(!tree)return {nullptr, nullptr};
        push(tree);
        if(getSize(tree->left) >= x){
            auto p = split(tree->left, x);
            tree->left = p.second;
            recalc(tree);
            return {p.first, tree};
        }else{
            auto p = split(tree->right, x - getSize(tree->left) - 1);
            tree->right = p.first;
            recalc(tree);
            return {tree, p.second};
        }
    }
    
    pnode merge(pnode left, pnode right){
        if(!left)return right;
        else if(!right)return left;
        push(left);
        push(right);
        if(left->y >= right->y){
            left->right = merge(left->right, right);
            recalc(left);
            return left;
        }else{
            right->left = merge(left, right->left);
            recalc(right);
            return right;
        }
    }
    cartesianTree(){
        root = nullptr;
    }
    
    pnode getRoot(){
        return root;
    }
    
    void push_back(int x){
        pnode newNode = new node(x);
        root = merge(root, newNode);
    }
    
    void insert(int ind, int x){
        pnode newNode = new node(x);
        auto res = split(root, ind);
        root = merge(merge(res.first, newNode), res.second);
    }
    
    void reverse(int l, int r){
        auto res1 = split(root, l);
        auto res2 = split(res1.second, r - l + 1);
        if(res2.first)res2.first->reversed ^= true;
        root = merge(merge(res1.first, res2.first), res2.second);
    }
    
    int getSummSegm(int l, int r){
        auto res1 = split(root, l);
        auto res2 = split(res1.second, r - l + 1);
        int ans = res2.first->summ;
        root = merge(merge(res1.first, res2.first), res2.second);
        return ans;
    }
    
    void pprint(pnode tree){
        if(!tree)return;
        push(tree);
        pprint(tree->left);
        cout << tree->data << " ";
        pprint(tree->right);
    }
    
    void print(){
        pprint(root);
        cout << endl;
    }
};
