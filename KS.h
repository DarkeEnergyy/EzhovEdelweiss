#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class KS {
private:
    static int next_id;
    string name;
    int room = -1;
    int work = -1;
    double kpd = -1;
    int id = -1;
public:
    KS();
    KS(std::fstream& in);
    KS(string name, int room, int work, int kpd);
    string getName() const;
    int getRoom() const;
    int getWork() const;
    double getKpd() const;
    int getID() const;
    static int getNextId();
    static int getCurID();

    /////*void setName(string name);
    //void setRoom(int room);
    void setNext_ID(int next);
    void setWork(int work);
    //void setKpd(int Kpd);


    friend ostream& operator << (ostream& ou, const KS& pipe);
    friend istream& operator >> (istream& in, KS& ks);
    friend fstream& operator << (fstream& f, KS& pipe);
    friend fstream& operator >> (fstream& f, KS& ks);
};
