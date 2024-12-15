#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Proverka.h"
using namespace std;

class Pipe {
private:
    static int next_id;
    string name;
    double len = -1;
    double diam = -1;
    int fix = -1;
    int id = -1;
    int inKs;
    int outKs;
public:
    Pipe();
    Pipe(std::fstream& in);
    Pipe(string name, double len, double diam, int fix);
    string getName() const;
    double getLen() const;
    double getDiam() const;
    int getFix() const;
    int getID() const;
    static int getNextId() { return next_id; }
    int getInKs();
    int getOutKs();

    static void setNext_ID(const unordered_map<int, Pipe>& all)
    {
        next_id = MaxKey(all);
    }
    void setFix(int Fix);
    void setInKs(int idKs);
    void setOutKs(int outKs);


    friend ostream& operator << (ostream& ou, const Pipe& pipe);                                            //cout pipe
    friend fstream& operator << (fstream& out, const Pipe& pipe);                                                  //pipe to file for "map to file"
    friend fstream& operator >> (fstream& f, Pipe& pipe);                                                  //pipe to file for "map to file"
    friend istream& operator >> (istream& in, Pipe& pipe);                  

};