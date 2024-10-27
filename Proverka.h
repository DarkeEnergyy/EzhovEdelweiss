#pragma once
#include <iostream>
using namespace std;


template <typename T1>
T1 proverka(T1 min, T1 max) {
    cout << "Enter number in range: " << min << "; " << max << endl;
    while (true) {
        /*if (i != 0) {
            if (cin.fail() || i < min || i>max) {
                cout << "Wrong data in file" << endl;
                cin.clear();
                cin.ignore(100, '\n');
                exit(0);
            }
            else {
                return i;
            }
        }*/
        T1 j;
        cout << "Enter data: " << endl;
        cin >> j;
        if (cin.fail() || j < min || j>max) { // type of T1 , T2
            cout << "Enter Correct data" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        return i;
    }
}