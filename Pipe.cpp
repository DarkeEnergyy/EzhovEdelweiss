#include "Pipe.h"
#include "Proverka.h"
#include <string>
#include <iostream>
using namespace std;

int Pipe::next_id = 1;

Pipe::Pipe(string name, double len, double diam, int fix, int id) : id(++next_id), name(name), len(len), diam(diam), fix(fix) {}

string Pipe::getName() const { return name;  }
double Pipe::getLen() const { return len;  }
double Pipe::getDiam() const { return diam; }
int Pipe::getFix() const { return fix; }
int Pipe::getID() const { return id; }

void Pipe::setName(string name) {
	this->name = name;
}
void Pipe::setLen(double len) {
	this->len = len;
}
void Pipe::setDiam(double diam) {
	this->diam = diam;
}
void Pipe::setFix(int Fix) {
	fix = Fix;
}

void Pipe::printPipe() {
	cout << "Pipe:\nId: " << id << "\nName: " << name << "\nLen: " << len << "\nDiam: " << diam << "\nFix: " << fix << endl;;
}