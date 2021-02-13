struct node{
    int data, ind;
    int tl, tr;
    node * left;
    node * right;
    node(int data = 0, int ind = 0, int tl = 0, int tr = 0){
        this->data = data;
        this->ind = ind;
        this->left = nullptr;
        this->right = nullptr;
    }
};

typedef node * pnode;

class segment_tree{
    pnode root;
public:
    segment_tree(vector<int> & a){
        build(root, 0, a.size(), a);
    }
    
    pair<int, int> get(int L, int R){
        return pget(this->root, L, R);
    }
private:
    void build(pnode & root, int l, int r, vector<int> & a){
        root = new node();
        root->tl = l;
        root->tr = r;
        if(r - l == 1){
            root->data = a[l];
            root->ind = l;
        }else{
            int mid = (l + r) / 2;
            build(root->left, l, mid, a);
            build(root->right, mid, r, a);
            if(root->left->data >= root->right->data){
                root->data = root->left->data;
                root->ind = root->left->ind;
            }else{
                root->data = root->right->data;
                root->ind = root->right->ind;
            }
        }
    }
    
    pair<int, int> pget(pnode & root, int L, int R){
        if(root->tr <= L || root->tl >= R)return {-1e9, -1};
        else if(root->tl >= L && root->tr <= R)return {root->data, root->ind};
        else{
            auto left = pget(root->left, L, R);
            auto right = pget(root->right, L, R);
            if(left.first >= right.first)return left;
            else return right;
        }
    }
};
