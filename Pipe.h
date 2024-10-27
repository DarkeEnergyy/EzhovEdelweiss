#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Pipe {
private:
    static int next_id;
    string name;
    double len = -1;
    double diam = -1;
    int fix = -1;
    int id;
public:
    Pipe() : name(""), len(-1), diam(-1), fix(-1) {}
    Pipe(string name, double len, double diam, int fix, int id) {}
    string getName() const {}
    double getLen() const {}
    double getDiam() const {}
    int getFix() const {}
    int getID() const {}
    int getNextId() const {}

    //void setNextId(int next_id) {}
    void setName(string name) {}
    void setLen(double len) {}
    void setDiam(double diam) {}
    void setFix(int Fix) {}
    void printPipe() {}

    friend unordered_map<int, Pipe>& FtoPipemap(int& count, unordered_map<int, Pipe>& map, fstream& f);     //file to map with number of pipe
    friend istream& operator >> (Pipe& pipe, unordered_map<int, Pipe>& p);                                  //pipe to map
    friend Pipe& newPipe();                                                                                 //pipe in
    friend ostream& operator << (ostream& ou, const Pipe& pipe);                                            //cout pipe
    friend ostream& operator << (ostream& out, unordered_map<int, Pipe>& p);                                //cout map
    friend fstream& operator << (fstream& in, Pipe& pipe);                                                  //pipe to file for "map to file"
    friend fstream& operator << (fstream& file, unordered_map<int, Pipe>& p);                               //map to file
    friend void setFix(Pipe& chfx);
    friend void EditPackPipe(unordered_map<int, Pipe>& p, vector<int>& vec);                                // pack edit
    friend void DeletePackPipe(unordered_map<int, Pipe>& p, vector<int>& vec);                              //pack delete
    friend vector<int>& FindForParam(unordered_map<int, Pipe>& p, vector<int>& vec);
};