#include "Pipe.h"
#include "Proverka.h"
#include <string>
#include <iostream>
#include <fstream>
#include <optional>
#include <unordered_map>

using namespace std;

int Pipe::next_id = 0;

Pipe::Pipe() : id(getNextId()), name(""), len(-1), diam(-1), fix(-1) {}
Pipe::Pipe(fstream& in)
{
    in >> *this;
}
Pipe::Pipe(string name, double len, double diam, int fix) : id(getNextId()), name(name), len(len), diam(diam), fix(fix) {}

string Pipe::getName() const { return name;  }
double Pipe::getLen() const { return len;  }
double Pipe::getDiam() const { return diam; }
int Pipe::getFix() const { return fix; }
int Pipe::getID() const { return id; }

int Pipe::getNextId()
{
    return ++next_id;
}

void Pipe::setNext_ID(int next) {
    next_id = next;
}
void Pipe::setFix(int Fix) {
	fix = Fix;
}



ostream& operator << (ostream& ou, const Pipe& pipe) {
    if (pipe.len != -1) {
        ou << "Name: " << pipe.name << endl;
        ou << "len: " << pipe.len << endl;
        ou << "diam: " << pipe.diam << endl;
        ou << "fix: " << pipe.fix << endl;
        ou << "ID: " << pipe.id << endl;
    }
    return ou;
}
istream& operator >> (istream& in, Pipe& pipe)
{
    cout << "Enter name:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, pipe.name);
    cerr << pipe.name << endl;
    cout << "Enter length:" << endl;
    pipe.len = proverka(0.01, 10000.0);
    cout << "Enter diametr:" << endl;
    pipe.diam = proverka(0.01, 10000.0);
    cout << "Enter fix:" << endl;
    pipe.fix = proverka(0, 1);
    cout << "Enter id: " << endl;
    pipe.id = proverka(0, 1000);
    return in;
}
fstream& operator << (fstream& out, const Pipe& pipe) {
    if (pipe.name != "") {
        out << pipe.name << '\n';
    }
    else {
        cout << "No Pipe" << endl;
        return out;
    }
    out << pipe.len << '\n';
    out << pipe.diam << '\n';
    out << pipe.fix << '\n';
    out << pipe.id << '\n';
    return out;
}
fstream& operator >> (fstream& f, Pipe& pipe) {
    getline(f >> ws, pipe.name);
    f >> pipe.len;
    f >> pipe.diam;
    f >> pipe.fix;
    f >> pipe.id;
    return f;
}



