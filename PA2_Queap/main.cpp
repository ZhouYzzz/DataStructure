//
//  main.cpp
//  PA2_Queap
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

#define MAX std::max

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

class Stack
{
public:
    Stack() {}
    ~Stack() {}
    bool empty();
    void push(int);
    int pop();
    int top();
private:
    Vector<int> s;
};

bool Stack::empty() {
    return bool(s.size()==0);
}

void Stack::push(int value) {
    s.push(value);
}

int Stack::pop() {
    return s.pop();
}

int Stack::top() {
    return s.top();
}

class Queap
{
public:
    Queap() {};
    void enqueap(int);
    int dequeap();
    int max();
private:
    Stack si;
    Stack so;
    Stack sim;  // top of which is the max value of sim
    Stack som;  // top of which is the max value of som
};

void Queap::enqueap(int value) {
    si.push(value);
    sim.push(MAX(value, sim.empty() ? value : sim.top()));
}

int Queap::dequeap() {
    if (so.empty()) {
        while (!si.empty()) {
            int tmp = si.pop();
            sim.pop();
            so.push(tmp);
            som.push(MAX(tmp, som.empty() ? tmp : som.top()));
        }
    }
    som.pop();
    return so.pop();
}

int Queap::max()
{
    return MAX((sim.empty()?som.top():sim.top()),(som.empty()?sim.top():som.top()));
    return 0;
}


int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency

    // insert code here...
    int n;
    SRC >> n;
    
    char c[10];
    int m;
    
    Queap q;

    for (int i = 0; i < n; i++) {
        SRC >> c;
        if (*c == 'E') {
            SRC >> m;
            q.enqueap(m);
        } else if (*c == 'D') {
            printf("%d\n", q.dequeap());
        } else if (*c == 'M') {
            printf("%d\n", q.max());
        } else {
            return 1;
        }

    }

    return 0;
}
