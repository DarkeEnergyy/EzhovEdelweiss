#pragma once
#include "KS.h"
#include <vector>

class Node
{
private:
	KS ks;
	vector<int> inP;
	vector<int> outP;
public:
	vector<int> getInP();
	vector<int> grtOutP();

	void setInP(int idP);
	void setOutP(int outP);

	Node();
};

