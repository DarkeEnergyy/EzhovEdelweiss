#include "KS.h"
#include <string>
#include <iostream>
using namespace std;

int KS::next_id = 1;

KS::KS(string name, int room, int work, int kpd, int id) : id(++next_id), name(name), room(room), work(work), kpd(kpd) {}

string KS::getName() const { return name; }
int KS::getRoom() const { return room; }
int KS::getWork() const { return work; }
double KS::getKpd() const { return kpd; }
int KS::getID() const { return id; }

void KS::setKpd(int Kpd) {
	kpd = Kpd;
}

void KS::printKS() {
	cout << "KS:\nId: " << id << "\nName: " << name << "\nRoom: " << room << "\nDiam: " << work << "\nFix: " << kpd << endl;;
}