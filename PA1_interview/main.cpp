//
//  main.cpp
//  PA1_interview
//
//  Created by Yizhuang Zhou on 9/20/16.
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

#define NO_IMPLEMENT std::cout << "NO_IMPLEMENT" << endl; exit(1);

using namespace std;

// ---------- CLL ----------

#define Posi(T) CListNode<T>*
template <typename T>
struct CListNode {
    T data;
    Posi(T) pred;
    Posi(T) succ;
    CListNode() {}
    CListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
    : data(e), pred(p), succ(s) {}
    Posi(T) insertAsPred(T const& e) {
        Posi(T) x = new CListNode(e, pred, this);
        pred->succ = x; pred = x; return x;
    }
    Posi(T) insertAsSucc(T const& e) {
        Posi(T) x = new CListNode(e, this, succ);
        succ->pred = x; succ = x; return x;
    }
};

template <typename T>
class CList {;
private:
    int _size;
    Posi(T) _header;
    
public:
    CList() {
        _header = new CListNode<T>;
        _header->succ = _header;
        _header->pred = _header;
        _size = 0;
#ifdef DEBUG
        cout << "CList inited" << endl;
#endif
    }
    ~CList() {}
    Posi(T) root(const T e) {
        if (_size) {
            return _header->succ;
        } else {
            Posi(T) x = new CListNode<T>(e);
            _header->succ = x; _header->pred = x;
            x->pred = x; x->succ = x;
            return x;
        }
    }
    int count() { return _size; }
    Posi(T) header() { return _header; }
    T& operator[](int n) const {
        Posi(T) p = _header->succ;
        while( 0 < n-- ) p = p->succ;
        return p->data;
    }
    
    Posi(T) insertBefore(Posi(T) p, T const e, unsigned int by = 1) {
        while (--by) p = p->pred;
        _size++;
        return p->insertAsPred(e);
    }
    Posi(T) insertAfter(Posi(T) p, T const e, unsigned int by = 1) {
        while (--by) p = p->succ;
        _size++;
        return p->insertAsSucc(e);
    }
};

// ---------- FCNS ----------

void writeTo(int* dst, int n) {
    for (int i = 0; i < n; i++) SRC >> *dst++;
}
void readFrom(int* dst, int n) {
    for (int i = 0; i < n; i++) cout << *dst++ << " ";
    cout << endl;
}

// ---------- MAIN ----------

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency
    
    // ----- IO begin -----

    int n, m;
    SRC >> n;
    SRC >> m;
    
    int* code = new int[n];
    
    writeTo(code, n);
    
    // ----- IO finished -----
    
    CList<int> c;
    
    Posi(int) x = c.root(code[0]);
    for (int i = 1; i < n; i++) {
        x = c.insertBefore(x, code[i], m);
    }
    
    for (int i = 0; i < n; i++) {
        cout << x->data << ' ';
        x = x->succ;
    }
    
    cout << endl;
    
#ifdef DEBUG
    for (int i = 0; i < c.count(); i++) cout << c[i] << " ";
    cout << endl;
#endif
    
    return 0;
}
