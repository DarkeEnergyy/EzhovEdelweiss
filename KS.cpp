#include "KS.h"
#include "Proverka.h"
#include <string>
#include <iostream>
#include <fstream>
#include <optional>
using namespace std;

int KS::next_id = 0;

KS::KS() : id(++next_id), name(""), room(-1), work(-1), kpd(-1) {}

KS::KS(fstream& in)
{
    in >> *this;
}

KS::KS(string name, int room, int work, int kpd) : id(getNextId()), name(name), room(room), work(work), kpd(kpd) {}

string KS::getName() const { return name; }
int KS::getRoom() const { return room; }
int KS::getWork() const { return work; }
double KS::getKpd() const { return kpd; }
int KS::getID() const { return id; }
int KS::getNextId() { return next_id; }
int KS::getCurID() { return next_id; }
bool KS::getinGraph() { return inGraph; }
void KS::setinGraph(bool b) {
    inGraph = b;
}


void KS::setWork(int work) {
	this->work = work;
}




ostream& operator << (ostream& ou, const KS& ks) {
    if (ks.getRoom() != -1) {
        ou << /*"Name: " <<*/ ks.name << endl;
        ou << /*"room: " <<*/ ks.room << endl;
        ou << /*"work: " <<*/ ks.work << endl;
        ou << /*"kpd: " <<*/ ks.kpd << endl;
        ou << /*"ID: " <<*/ ks.id << endl;
    }
    return ou;
}
istream& operator >> (istream& in, KS& ks)
{
    cout << "Enter name:" << endl;
    ks.name = InputString();
    clog << ks.name << endl;
    cout << "Enter room:" << endl;
    ks.room = proverka(1, 10000);
    cout << "Enter work:" << endl;
    ks.work = proverka(1, 10000);
    cout << "Enter kpd:" << endl;
    ks.kpd = proverka(0.001, 100.0);
    // cout << "Enter id: " << endl;
    // ks.id = proverka(0, 1000);
    return in;
}
fstream& operator << (fstream& out, const KS& ks) {
    if (ks.getName() != "") {
        out << ks.getName() << '\n';
    }
    else {
        cout << "No KS" << endl;
        return out;
    }
    out << ks.getRoom() << '\n';
    out << ks.getWork() << '\n';
    out << ks.getKpd() << '\n';
    out << ks.getID() << '\n';
    return out;
}
fstream& operator >> (fstream& f, KS& ks) {
    getline(f >> ws, ks.name);
    f >> ks.room;
    f >> ks.work;
    f >> ks.kpd;
    f >> ks.id;
    return f;
}

