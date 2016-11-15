//
//  main.cpp
//  PA2_Train
//
//  Created by Yizhuang Zhou on 05/11/2016.
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

#define Posi(T) Node<T>*
template <typename T>
struct Node {
    T data;
    Posi(T) pred;
    Node(T e, Posi(T) p = NULL)
    : data(e), pred(p){}
    Posi(T) append(T const & e) {
        Posi(T) x = new Node<T>(e, this);
        return x;
    }
};

template <typename T>
class Vector {
    Posi(T) root;
    size_t size_ = 0;
public:
    Vector() {}
    Vector(size_t n) {}
    void push(T const & e) {
        root = root->append(e);
        size_++;
    }
    size_t size() {
        return size_;
    }
    T top() {
        return root->data;
    }
    T pop() {
        size_--;
        T poped_data = root->data;
        Posi(T) poped = root;
        root = root->pred;
        delete poped;
        return poped_data;
    }
};

template <typename T>
class Stack {
    Vector<T> s;
public:
    Stack() {}
    Stack(int n): s(Vector<T>(n)) {
        for (int i = 0; i < n; i++) {
            s.push(i + 1);
        }
    }
    void push(T const & e) {
        s.push(e);
    }
    T top() {
        return s.top();
    }
    T pop() {
        return s.pop();
    }
    size_t size() {
        return s.size();
    }
};

void writeTo(int* dst, int n) {
    for (int i = 0; i < n; i++) {
        SRC >> *dst++;
    }
}
void readFrom(int* dst, int n) {
    for (int i = 0; i < n; i++) cout << *dst++ << " ";
    cout << endl;
}

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency
    
    // ----- IO begin -----
    int n, m;
    SRC >> n;
    SRC >> m;
    
    int* order = new int[n];
    
    writeTo(order, n);
    
#ifdef DEBUG
    readFrom(order, n);
#endif
    
    int lastTrain = 0;
    int comingTrain = 1;
    int finishTrain = order[n-1];
    // start from lastTrain, stack is from 1 to lastTrain - 1
    
//    Stack<int> stack(lastTrain - 1);
    Stack<int> stack;
    
//    bool processing = true;
    int nextTrain = *order++;
    
    while (1) {

#ifdef DEBUG
        cout << " * LAST IS `"<< lastTrain << "` NEXT SHOULD BE `" << nextTrain << "` COMING `" << comingTrain << "` TOP IS `" << stack.top() << "`" << endl;
#endif
        // processing nextTrain
        if (nextTrain == stack.top()) {
#ifdef DEBUG
            cout << " - POP " << nextTrain << endl;
#endif
            
            lastTrain = stack.pop();
            nextTrain = *order++;
        } else if (nextTrain == comingTrain) {
#ifdef DEBUG
            cout << " - PASS BY" << endl;
#endif
            lastTrain = comingTrain;
            comingTrain++;
            nextTrain = *order++;
        } else {
#ifdef DEBUG
            cout << " - PUSH " << comingTrain << endl;
#endif
            stack.push(comingTrain);
            comingTrain++;
        }
        // check if NO
        if (stack.size() > m) {
            cout << "No" << endl;
            return 0;
        }
        // check if OK
        if (lastTrain == finishTrain) {
            break;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
