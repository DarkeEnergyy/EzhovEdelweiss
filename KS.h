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
    int id;
public:
    KS();
    KS(string name, int room, int work, int kpd, int id);
    string getName() const;
    int getRoom() const;
    int getWork() const;
    double getKpd() const;
    int getID() const;
    static int getNextId();

    void setName(string name);
    void setRoom(int room);
    void setWork(int work);
    void setKpd(int Kpd);
    void printKS();

    //unordered_map<int, KS>& FtoKSmap(int& count, unordered_map<int, KS>& map, fstream& f);       //file to map with number of KS
    friend void operator >> (KS& ks, unordered_map<int, KS>& k);
    //void KSToMap(unordered_map<int, KS>& k);                                                     //KS to map
    //KS& newKS();                                                                                 //KS in
    friend ostream& operator << (ostream& ou, const KS& ks);                                            //cout KS
    friend ostream& operator << (ostream& out, unordered_map<int, KS>& k);                              //cout map
    friend fstream& operator << (fstream& in, KS& ks);                                                  //KS to file for "map to file"
    friend fstream& operator << (fstream& file, unordered_map<int, KS>& k);                             //map to file
    //void changeWork(unordered_map<int, KS>& k);                                                  //change work in one ks
    //void EditPackKS(unordered_map<int, KS>& k, vector<int>& vecKs);                              // pack edit
    //void DeletePackKS(unordered_map<int, KS>& k, vector<int>& vecKs);                            //pack delete
    //vector<int>& FindForParam(unordered_map<int, KS>& k, vector<int>& vecKs);
};
