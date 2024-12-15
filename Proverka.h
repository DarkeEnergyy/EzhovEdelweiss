#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

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

std::string InputString();

template <typename T1>
T1 proverka(T1 min, T1 max) {
    std::cout<< "Enter number in range: " << min << "; " << max << std::endl;
    while (true) {
        T1 j;
        std::cin >> j;
        if (std::cin.fail() || j < min || j>max) {
            std::cout<< "Enter Correct data" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }
        std::cerr << j << std::endl;;
        return j;
    }
}

template <typename T1>
T1 proverka(T1 val, T1 val1, T1 val2, T1 val3) {
    std::cout << "Enter number in range: " << min << "; " << max << std::endl;
    while (true) {
        T1 j;
        std::cin >> j;
        if (std::cin.fail() || (j != val && j != val1 && j != val2 && j != val3)) {
            std::cout << "Enter Correct data" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }
        std::cerr << j << std::endl;;
        return j;
    }
}

template <typename T>
int proverka(std::unordered_map<int, T> map) {
    while (true) {
        int j;
        std::cin >> j;
        if (std::cin.fail() || j < 0 || j > MaxKey(map) || !(map.contains(j))) {
            std::cout << "Enter Correct data" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }
        std::cerr << j << std::endl;;
        return j;
    }
}

template<typename T>
void OutVec(std::vector<int>& vec, std::unordered_map<int, T>& p) {
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            std::cout<< it->second << std::endl;
        }
        else {
            std::cout<< "Wrong element in vector" << std::endl;
        }
    }
    std::cout<< std::endl;
}

template <typename T>
int MaxKey(const std::unordered_map<int, T>& map) {
    int maxKey = 0;
    for (auto& [k, v] : map) {
        maxKey = maxKey > k ? maxKey : k;
    }
    if (maxKey == 0) { std::cout<< "Empty map" << std::endl; }
    return maxKey;
}

template <typename T>
std::vector <int> HandVec(std::unordered_map<int, T>& k) {
    std::unordered_set<int> ids;
    int id;
    std::cout<< "Enter obj's id. For stop press 0" << std::endl;
   // std::cerr << "Entered id: " << std::endl;
    int i = MaxKey(k) + 1;
    while (true) {
        id = proverka<int>(0, i);
        if (id == 0) 
        {
            return std::vector<int> (ids.begin(), ids.end());
        }
        if (k.contains(id))
            ids.insert(id);
        else 
            std::cout<< "Wrong id. Try again: ";
    }
}

template <typename T>
std::vector<int> MakeVec(std::unordered_map<int, T>& objs) {
    std::vector<int> vec;
    std::cout << "1. I want to enter id\n2. I want to filtr map or vec" << std::endl;
    //cerr << "Make vector for id or filtr(1, 2): ";
    switch (proverka(1, 2))
    {
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
            std::cout << "Do you want to continue finding?(0, 1)" << std::endl;
            //cerr << "Do you want to continue finding?(0, 1): ";
            flag = proverka(0, 1);
        }
        break;
    }
    }
    return vec;
}



template <typename T>
std::ostream& operator << (std::ostream& ou, const std::unordered_map<int, T>& map) {
    for (auto& [id, item] : map) {
        ou << item;
    }
    return ou;
}

template <typename T>
std::fstream& operator << (std::fstream& fou, const std::unordered_map<int, T>& map) {
    for (auto& [id, item] : map) {
        fou << item;
    }
    return fou;
}
