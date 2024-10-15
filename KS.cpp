#include "KS.h"
#include "Proverka.h"
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

void KS::setName(string name) {
	this->name = name;
}
void KS::setRoom(int room) {
	this->room = room;
}
void KS::setWork(int work) {
	this->work = work;
}
void KS::setKpd(int kpd) {
	this->kpd = kpd;
}

void KS::printKS() {
	cout << "KS:\nId: " << id << "\nName: " << name << "\nRoom: " << room << "\nDiam: " << work << "\nFix: " << kpd << endl;;
}

