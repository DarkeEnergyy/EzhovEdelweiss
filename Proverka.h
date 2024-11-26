#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }
    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};



template <typename T1>
T1 proverka(T1 min, T1 max) {
    std::cout << "Enter number in range: " << min << "; " << max << std::endl;
    while (true) {
        T1 j;
        std::cin >> j;
        if (std::cin.fail() || j < min || j>max) {
            std::cout << "Enter Correct data" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }
        cerr << j << endl;;
        return j;
    }
}

template<typename T>
void OutVec(vector<int>& vec, unordered_map<int, T>& p) {
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            cout << it->second << endl;
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
    cout << endl;
}

template <typename T>
int MaxKey(unordered_map<int, T>& map) {
    int maxKey = 0;
    for (auto& it : map) {
        maxKey = max(maxKey, it.first);
    }
    if (maxKey == 0) { cout << "Empty map" << endl; }
    return maxKey;
}

template <typename T>
std::vector <int> HandVec(unordered_map<int, T>& k) {
    std::vector<int> vec;
    int id;
    cout << "Enter obj's id. For stop press 0" << endl;
    cerr << "Entered id: " << endl;
    int i = MaxKey(k) + 1;
    while (true) {
        id = proverka<int>(0, i);
        if (id == 0) 
        {
            return vec; 
        }
        if (std::find(vec.begin(), vec.end(), id) != vec.end()) {
            cout << "Pipe with this ID just added" << endl;
        }
        if (k.contains(id))
            vec.push_back(id);
        cout << "Pipe added" << endl;
        else {
            cout << "Wrong id. Try again: ";
            cerr << "Wrong id" << endl;
        }
    }
}

template <typename T>
std::vector<int> MakeVec(unordered_map<int, T>& objs) {
    vector<int> vec;
    int h = 0;
    cout << "1. I want to enter id\n2. I want to filtr map or vec" << endl;
    cerr << "Make vector for id or filtr(1, 2): ";
    switch (proverka(1, 2)) {
    case 1:
    {
        vec = HandVec(objs);
        break;
    }
    case 2:
    {
        int flag = 1;
        while (flag) {
            vec = FindForParam(objs, vec);
            cout << "Do you want to continue finding?(0, 1)" << endl;
            h = 1;
            cerr << "Do you want to continue finding?(0, 1): ";
            flag = proverka(0, 1);
        }

        break;
    }
    }
    return vec;
}



template <typename T>
std::ostream& operator << (std::ostream& ou, std::unordered_map<int, T>& map) {
    for (auto& [id, item] : map) {
        ou << item;
    }
    return ou;
}

template <typename T>
std::fstream& operator << (std::fstream& fou, std::unordered_map<int, T>& map) {
    for (auto& [id, item] : map) {
        fou << item;
    }
    return fou;
}

//
//
//fstream& operator << (fstream& file, unordered_map<int, Pipe>& p);                               //map to file
//fstream& operator >> (fstream& file, unordered_map<int, Pipe>& p);                               //from file to map
//ostream& operator << (ostream& out, unordered_map<int, Pipe>& p);                                //cout map
//void operator >> (Pipe& pipe, unordered_map<int, Pipe>& p);
