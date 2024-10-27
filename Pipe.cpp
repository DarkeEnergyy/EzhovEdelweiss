#include "Pipe.h"
#include "Proverka.h"
#include <string>
#include <iostream>
#include <fstream>
#include <optional>

using namespace std;

int Pipe::next_id = 1;

Pipe::Pipe() : name(""), len(-1), diam(-1), fix(-1) {}

Pipe::Pipe(string name, double len, double diam, int fix, int id) : id(++next_id), name(name), len(len), diam(diam), fix(fix) {}

string Pipe::getName() const { return name;  }
double Pipe::getLen() const { return len;  }
double Pipe::getDiam() const { return diam; }
int Pipe::getFix() const { return fix; }
int Pipe::getID() const { return id; }
int Pipe::getNextId() const { return ++next_id; }

/*void Pipe::setNextId(int next_id) {
    this->next_id = next_id;
}*/
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


//file to map with number of pipe
unordered_map<int, Pipe>& FtoPipemap(int& count, unordered_map<int, Pipe>& map, fstream& f) {
    map.clear();
    Pipe pipe;
    string nam;
    double i;
    for(int j = 0; j < count ; j++) {
        getline(f, nam);
        pipe.setName(nam);
        pipe.setLen(proverka(0.01, 10000.0));
        pipe.setDiam(proverka(0.01, 10000.0));
        pipe.setFix(proverka(0, 1));
        map.emplace(pipe.getNextId(), pipe);
    }
    return map;
}

//pipe to map
istream& operator >> (Pipe& pipe, unordered_map<int, Pipe>& p) { 
    p.emplace(pipe.getNextId(), pipe);
}
//pipe in
Pipe& newPipe() {
    Pipe pipe;
    string nam;
    cout << "Enter name:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, nam);
    pipe.setName(nam);
    cout << "Enter length:" << endl;
    pipe.setLen(proverka(0.01, 10000.0));
    cout << "Enter diametr:" << endl;
    pipe.setDiam(proverka(0.01, 10000.0));
    cout << "Enter fix:" << endl;
    pipe.setFix(proverka(0, 1));
    return pipe;
}

//cout pipe
ostream& operator << (ostream& ou, const Pipe& pipe) {
    if (pipe.getLen() != -1) {
        ou << "Pipe:\n" << "Name: " << pipe.getName() << endl;
        ou << "len: " << pipe.getLen() << endl;
        ou << "diam: " << pipe.getDiam() << endl;
        ou << "fix: " << pipe.getFix() << endl;
    }
    return ou;
}
//cout map
ostream& operator << (ostream& out, unordered_map<int, Pipe>& p) {
    for (const auto& [id, pipe] : p) {
        out << "id: " << id << pipe << endl;
    }
}

//pipe to file for "map to file"
fstream& operator << (fstream& in, Pipe& pipe) {
    if (pipe.getName() != "") {
        in << pipe.getName() << '\n';
    }
    else {
        cout << "No Pipe" << endl;
        return in;
    }
    in << pipe.getLen() << '\n';
    in << pipe.getDiam() << '\n';
    in << pipe.getFix() << '\n';
    return in;
}
//map to file
fstream& operator << (fstream& file, unordered_map<int, Pipe>& p);

vector<int>& FindForParam(unordered_map<int, Pipe>& p, vector<int>& vec) {
    vector<int> found;
    string name = "";
    double len = -1;
    double diam = -1;
    int fix = -1;
    cout << "1 or 0 " << endl;
    int choice;
    cout << "For what do you want to find: \n1. Name\n2. Length\n3. Diametr \n4. Fix" << endl;
    cin >> choice;
    switch (choice) {
    case 1: cin >> name;
    case 2: cin >> len;
    case 3: cin >> diam;
    case 4: cin >> fix;
    }
    int choice2;
    cout << "Where you want to find: \n1. Map \2.vec" << endl;
    cin >> choice2;
    switch (choice2) {
    case 1:
        for (auto& [id, pipe] : p) {
            if (pipe.getFix() == fix || pipe.getDiam() == diam || pipe.getLen() == len || pipe.getName() == name) {
                found.push_back(pipe.getID());
            }
        }
        return found;
    case 2:
        int i = 0;
        for (auto& [id, pipe] : p) {
            if (id == vec[i]) {
                if (pipe.getFix() == fix || pipe.getDiam() == diam || pipe.getLen() == len || pipe.getName() == name) {
                    found.push_back(pipe.getID());
                    ++i;
                }
                else { cout << "Wrong data in vector" << endl; return found; }
            }
        }
    }
    if (found.size() == 0) {
        cout << "No such pipes" << endl;
    }
    return found;
}

void setFix(Pipe& chfx) {
    if (chfx.getDiam() == -1) {
        cout << "No pipe" << endl;
        return;
    }
    cout << "Enter fix:" << endl;
    chfx.setFix(proverka(0, 1));
}

void DeletePackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cout << "No pipes for delete(vec0)" << endl; return; }
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            p.erase(it);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}

void EditPackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cout << "No pipes for edit(vec0)" << endl; return; }
    cout << "What Fix do you wnat to install: ";
    int fix = proverka(0, 1);
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            it->second.setFix(fix);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}


/*void Pipe::printPipe() {
	cout << "Pipe:\nId: " << id << "\nName: " << name << "\nLen: " << len << "\nDiam: " << diam << "\nFix: " << fix << endl;;
}*/