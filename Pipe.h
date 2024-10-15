#pragma once
#include <string>
using namespace std;

class Pipe {
private:
    static int next_id;
    string name;
    double len = -1;
    double diam = -1;
    int fix = -1;
    int id;
public:
    Pipe(string name, double len, double diam, int fix, int id) {}
    string getName() const {}
    double getLen() const {}
    double getDiam() const{}
    int getFix() const {}
    int getID() const {}

    void setFix(int Fix) {}
    void printPipe() {}
};