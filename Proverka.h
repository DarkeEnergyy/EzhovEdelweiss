#pragma once
#include <iostream>
using namespace std;


template <typename T1>
T1 proverka(T1 min, T1 max) {
    cout << "Enter number in range: " << min << "; " << max << endl;
    while (true) {
        T1 j;
        cin >> j;
        if (cin.fail() || j < min || j>max) {
            cout << "Enter Correct data" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        return j;
    }
}