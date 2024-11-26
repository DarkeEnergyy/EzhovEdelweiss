#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

template <typename T1, typename T2 >
using Filtr = bool(*)(T1 obj, T2 param);

template <typename T>
bool FiltrName(T obj, string name) {

}