//
//  main.cpp
//  PA2_Rebuild
//
//  Created by Yizhuang Zhou on 13/11/2016.
//  Copyright © 2016 Yizhuang Zhou. All rights reserved.
//

#include <iostream>
#include <fstream>

// Stringlization
#define S(x) _S(x)
#define _S(x) #x

// Select input source
#ifdef LOCAL
std::ifstream f(S(TARGET_DIR/test_data));
#define SRC f
#else
#define SRC std::cin
#endif

using namespace std;

#define index int

void writeTo(int* dst, int n) {
    for (int i = 0; i < n; i++) {
        SRC >> *dst++;
    }
}
void readFrom(int* dst, int n) {
    for (int i = 0; i < n; i++) cout << *dst++ << " ";
    cout << endl;
}

#define BinNodePosi(T) BinNode<T>*

template <typename T>
struct BinNode {
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    T data; int height;
    BinNode() {}
    BinNode(T const &e, BinNodePosi(T) p): data(e), parent(p) {}
    BinNodePosi(T) insertAsLC(T const &e) {
        return lc = new BinNode(e, this);
    }
    BinNodePosi(T) insertAsRC(T const &e) {
        return rc = new BinNode(e, this);
    }
    BinNodePosi(T) succ();
    int size() {
        int s = 1;
        if (lc) s += lc->size();
        if (rc) s += rc->size();
        return s;
    }
};

template <typename T>
class BinTree {
#define stature(p) ( (p) ? (p)->height : -1 )
protected:
    int size_;
    BinNodePosi(T) root_;
    int updateHeight(BinNodePosi(T) x) {
        return x->height = 1 + max(stature(x->lc), stature(x->rc));
    }
    void updateHeightAbove(BinNodePosi(T) x) {
        while (x) { updateHeight(x); x = x->parent; }
    }
public:
    int size() const { return size_; }
    bool empty() const { return !root_; }
    BinNodePosi(T) & root() { return root_; }
    
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e) {
        size_++; x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e) {
        size_++; x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* & S) {
        if (x->lc = S->root_) x->lc->parent = x;
        size_ += S->size();
        updateHeightAbove(x);
        S->root_ = NULL; S->size_ = 0; S = NULL;
        return x;
    }
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* & S) {
        if (x->rc = S->root_) x->rc->parent = x;
        size_ += S->size();
        updateHeightAbove(x);
        S->root_ = NULL; S->size_ = 0; S = NULL;
        return x;
    }
    template <typename VST> void travPost(BinNodePosi(T) x, VST & visit) {
        if (!x) return;
        travPost(x->lc, visit);
        travPost(x->rc, visit);
        visit(x->data);
    }
#undef stature
};

bool find(index &ind, const int* ord, const int e, size_t n) { // find e in list ord (sz=n), return index;
    for (ind = 0; ind < n; ind++) { if (ord[ind] == e) return true; }
    return false;
}

BinNodePosi(int) constructBinTree(const int* pre, const int* in, const int n, bool &flag) {
    if (n) {
        index root_ind;
        if (find(root_ind, in, *pre, n)) {
            BinNodePosi(int) x = new BinNode<int>(*pre, NULL);
            x->lc = constructBinTree(pre + 1, in, root_ind, flag);
            x->rc = constructBinTree(pre + 1 + root_ind, in + 1 + root_ind, n - root_ind - 1, flag);
            return x;
        } else {
            flag = false;
        }
    }
    return NULL;
}

BinTree<int> mainConstructBinTree(const int* pre, const int* in, const int n, bool &flag) {
    BinTree<int> bt;
    bt.root() = constructBinTree(pre, in, n, flag);
    return bt;
}

void visit(int x) {
    printf("%d ", x);
}

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency

    // insert code here...
    
    int n;
    SRC >> n;
    
    int preOrder[n];
    int inOrder[n];
    
    writeTo(preOrder, n);
    writeTo(inOrder, n);
    
    bool flag = true;
    
    BinTree<int> bt = mainConstructBinTree(preOrder, inOrder, n, flag);
    
    if (flag) {
        bt.travPost(bt.root(), visit);
        printf("\n");
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}
