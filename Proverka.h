#pragma once
#include <iostream>
using namespace std;


template <typename T1>
T1 proverka(T1 min, T1 max) {
    T1 i;
    cout << "Enter number in range: " << min << "; " << max << endl;
    while (true) {
        cin >> i;
        if (cin.fail() || i < min || i>max) {
            cout << "Enter Correct data" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        return i;
    }
}