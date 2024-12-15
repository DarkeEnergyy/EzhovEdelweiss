#pragma once
#include <string>
#include <unordered_map>
#include "Proverka.h"
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


    static void setNext_ID(const unordered_map<int, KS>& all)
    {
        next_id = MaxKey(all);
    }
    void setWork(int work);



    friend ostream& operator << (ostream& ou, const KS& pipe);
    friend istream& operator >> (istream& in, KS& ks);
    friend fstream& operator << (fstream& f, KS& pipe);
    friend fstream& operator >> (fstream& f, KS& ks);
};
