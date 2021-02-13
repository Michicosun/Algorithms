cartesianTree(const vector<ele> & elem){
    pnode tree = new node(elem[0].a, elem[0].b, elem[0].i);
    pnode last = tree;
    for (int i = 1; i < elem.size(); ++i){
        pnode newNode = new node(elem[i].a, elem[i].b, elem[i].i);
        if(last->y < newNode->y){
            last->right = newNode;
            last->right->pred = last;
            last = last->right;
        }
        else{
            pnode cur = last;
            while (cur->pred != nullptr && cur->y >= newNode->y)
                cur = cur->pred;
            if (cur->y >= newNode->y){
                last = newNode;
                last->left = cur;
                if(last->left)last->left->pred = last;
            }else{
                last = newNode;
                last->left = cur->right;
                last->left->pred = last;
                last->pred = cur;
                cur->right = last;
            }
        }
    }
    while(last->pred != nullptr){
        last = last->pred;
    }
    root = last;
    }
