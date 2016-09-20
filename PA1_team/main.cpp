//
//  main.cpp
//  PA1_team
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


using namespace std;

// ---------- FCNS ----------

void writeTo(int* dst, int n) {
    for (int i = 0; i < n; i++) {
        SRC >> *dst++;
    }
}

void readFrom(int* dst, int n) {
    for (int i = 0; i < n; i++) {
        cout << *dst++ << " ";
    }
    cout << endl;
}

inline void loop(int& i) { i += (i==2) ? -2 : 1;}
inline void inv_loop(int& i) { i += (i==0) ? 2 : -1;}

inline int picking(const int k, const int n, int* A, int* B, int* C) {
    bool* picked = new bool[n]();
    int* t[3] = {A,B,C};
    int i = 0;
    int mem;
    mem = *t[i];
    while (mem != k) {
        while (picked[*t[i]]) {
            t[i] += 1;
        } // next A until not picked
        picked[*t[i]] = true;
        mem = *t[i];
        loop(i);
    }
    inv_loop(i);
    return i;
}

// ---------- MAIN ----------

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency
    
    // ----- IO begin -----
    
    int n;
    SRC >> n;
    
    int* A = new int[n];
    int* B = new int[n];
    int* C = new int[n];
    
    writeTo(A, n);
    writeTo(B, n);
    writeTo(C, n);
    
    int k;
    SRC >> k;
    
    // ----- IO finished -----
    
    int i = picking(k, n, A, B, C);
    
    // ----- output -----
    
    char result[3] = {'A', 'B', 'C'};
    cout << result[i] << endl;
    return 0;
}
