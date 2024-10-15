#pragma once
#include <string>
using namespace std;

class KS {
private:
    static int next_id;
    string name;
    int room = -1;
    int work = -1;
    double kpd = -1;
    int id;
public:
    KS(string name, int room, int work, int kpd, int id) {}
    string getName() const {}
    int getRoom() const {}
    int getWork() const {}
    double getKpd() const {}
    int getID() const {}

    void setName(string name) {}
    void setRoom(int room) {}
    void setWork(int work) {}
    void setKpd(int Kpd) {}
    void printKS() {}
};
