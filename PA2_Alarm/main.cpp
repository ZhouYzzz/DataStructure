//
//  main.cpp
//  PA2_Alarm
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

typedef unsigned int uint;

typedef unsigned long long int ulong;

struct Alarm {
    ulong X;
    ulong Y;
//    ulong S;
};

struct Point {
    ulong X;
    ulong Y;
};

void writeToAlarm(Alarm* dst, int n) {
    for (int i = 0; i < n; i++) {
        SRC >> dst->X;
        SRC >> dst->Y;
//        dst->S = dst->X * dst->Y;
        dst++;
    }
}

void writeToPoint(Point* dst, int n) {
    for (int i = 0; i < n; i++) {
        SRC >> dst->X;
        SRC >> dst->Y;
        dst++;
    }
}

bool compare(const Point p, const Alarm a) {
    return (a.X * p.Y + a.Y * p.X >= a.X * a.Y);
}

int search(const Point p, const Alarm* A, const int n) {
    int L = 0;
    int R = n-1;
    int m = (L + R) / 2;
    while (L <= R) {
        m = (L + R) / 2;
        if (compare(p, A[m])) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return L;
}

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(false);    // improve IO efficiency

    // ----- IO begin -----
    int n, m;
    SRC >> n;
    SRC >> m;
    
    Alarm* A = new Alarm[n];
    
    writeToAlarm(A, n);
    
    Point* P = new Point[m];
    
    writeToPoint(P, m);
    
    for (int i = 0; i < m; i++) {
        printf("%d\n", search(P[i], A, n));
    }

    return 0;
}
