#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "Pipe.h"
#include "KS.h"

template <typename T1, typename T2 >
using Filtr = bool(*)(T1 obj, T2 param);

template <typename T>
bool FiltrName(T obj, std::string name) {
	return obj.getName().find(name);
}

bool FiltrFix(Pipe obj, int Fix) {
	return obj.getFix() == Fix;
}

bool FiltrWork(KS obj, int Work) {
	return obj.getWork() <= Work;
}