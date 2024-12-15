#include "Node.h"
using namespace std;

vector<int> Node::getInP() { return inP; }
vector<int> Node::grtOutP() { return outP; }

void Node::setInP(int idP)
{
    inP.push_back(idP);
}
void Node::setOutP(int idP)
{
    outP.push_back(idP);
}

Node::Node()
{
	cout << "";
}

