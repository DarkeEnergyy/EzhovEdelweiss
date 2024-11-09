#include "KS.h"
#include "Proverka.h"
#include <string>
#include <iostream>
#include <fstream>
#include <optional>
using namespace std;

int KS::next_id = 0;

KS::KS() : name(""), room(-1), work(-1), kpd(-1) {}

KS::KS(string name, int room, int work, int kpd, int id) : id(++next_id), name(name), room(room), work(work), kpd(kpd) {}

string KS::getName() const { return name; }
int KS::getRoom() const { return room; }
int KS::getWork() const { return work; }
double KS::getKpd() const { return kpd; }
int KS::getID() const { return id; }
int KS::getNextId() const { return ++next_id; }

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
	cout << "KS:\nId: " << id << "\nName: " << name << "\nRoom: " << room << "\nWork: " << work << "\nKpd: " << kpd << endl;;
}

//file to map with number of ks
/*unordered_map<int, KS>& KS::FtoKSmap(int& count, unordered_map<int, KS>& map, fstream& f) {
    map.clear();
    KS ks;
    string nam;
    for (int j = 0; j < count; j++) {
        getline(f, nam);
        ks.setName(nam);
        ks.setRoom(proverka(0.01, 10000.0));
        ks.setWork(proverka(0.01, 10000.0));
        ks.setKpd(proverka(0, 1));
        map.emplace(ks.getNextId(), ks);
    }
    return map;
}*/

//ks to map
void operator >> (KS& ks, unordered_map<int, KS>& k) {
    k.emplace(ks.getNextId(), ks);
}
/*
void KS::KSToMap(unordered_map<int, KS>& k) {
    KS ks = newKS();
    k.emplace(ks.getNextId(), ks);
}

//ks in
KS& KS::newKS() {
    KS ks;
    string nam;
    cout << "Enter name:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, nam);
    ks.setName(nam);
    cout << "Enter roomgth:" << endl;
    ks.setRoom(proverka(0.01, 10000.0));
    cout << "Enter worketr:" << endl;
    ks.setWork(proverka(0.01, 10000.0));
    cout << "Enter kpd:" << endl;
    ks.setKpd(proverka(0, 1));
    return ks;
}
*/
//cout ks
ostream& operator << (ostream& ou, const KS& ks) {
    if (ks.getRoom() != -1) {
        ou << "KS:\n" << "Name: " << ks.getName() << endl;
        ou << "room: " << ks.getRoom() << endl;
        ou << "work: " << ks.getWork() << endl;
        ou << "kpd: " << ks.getKpd() << endl;
    }
    return ou;
}
//cout map
ostream& operator << (ostream& out, unordered_map<int, KS>& k) {
    for (const auto& [id, ks] : k) {
        out << "id: " << id << ks << endl;
    }
    return out;
}

//ks to file for "map to file"
fstream& operator << (fstream& in, KS& ks) {
    if (ks.getName() != "") {
        in << ks.getName() << '\n';
    }
    else {
        cout << "No KS" << endl;
        return in;
    }
    in << ks.getRoom() << '\n';
    in << ks.getWork() << '\n';
    in << ks.getKpd() << '\n';
    return in;
}
//map to file
fstream& operator << (fstream& file, unordered_map<int, KS>& k) {
    for (auto& [id, ks] : k) {
        file << ks << endl;
    }
    return file;
}
/*
vector<int>& KS::FindForParam(unordered_map<int, KS>& k, vector<int>& vecKs) {
    vector<int> found;
    string name = "";
    double room = -1;
    double work = -1;
    int kpd = -1;
    int choice;
    cout << "For what do you want to find: \n1. Name\n2. Roomgth\n3. Worketr \n4. Kpd" << endl;
    cin >> choice;
    switch (choice) {
    case 1: cin >> name;
    case 2: cin >> room;
    case 3: cin >> work;
    case 4: cin >> kpd;
    }
    int choice2;
    cout << "Where you want to find: \n1. Map \2.vec" << endl;
    cin >> choice2;
    switch (choice2) {
    case 1:
        for (auto& [id, ks] : k) {
            if (ks.getKpd() == kpd || ks.getWork() == work || ks.getRoom() == room || ks.getName() == name) {
                found.push_back(ks.getID());
            }
        }
        return found;
    case 2:
        int i = 0;
        for (auto& [id, ks] : k) {
            if (id == vecKs[i]) {
                if (ks.getKpd() == kpd || ks.getWork() == work || ks.getRoom() == room || ks.getName() == name) {
                    found.push_back(ks.getID());
                    ++i;
                }
                else { cout << "Wrong data in vector" << endl; return found; }
            }
        }
    }
    if (found.size() == 0) {
        cout << "No such ks" << endl;
    }
    return found;
}

void KS::changeWork(unordered_map<int, KS>& k) {
    cout << "Enter id of changing pipe" << endl;
    int idfind = proverka(1, 10000);
    bool fl = 0;
    for (auto& [id, ks] : k) {
        if (id == idfind) {
            ks.setWork(proverka(0, 1));
            fl = 1;
        }
    }
    if (!fl) {
        cout << "Wrong id" << endl;
    }
}

void KS::DeletePackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
    if (vecKs.size() == 0) { cout << "No ks for delete(vec0)" << endl; return; }
    for (auto& a : vecKs) {
        auto it = k.find(a);
        if (it != k.end()) {
            k.erase(it);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}

void KS::EditPackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
    if (vecKs.size() == 0) { cout << "No ks for edit(vec0)" << endl; return; }
    cout << "What Kpd do you wnat to install: ";
    int kpd = proverka(0, 1);
    for (auto& a : vecKs) {
        auto it = k.find(a);
        if (it != k.end()) {
            it->second.setKpd(kpd);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}*/

