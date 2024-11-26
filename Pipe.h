#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Pipe {
private:
    static int next_id;
    string name;
    double len = -1;
    double diam = -1;
    int fix = -1;
    int id = -1;
public:
    Pipe();
    Pipe(std::fstream& in);
    Pipe(string name, double len, double diam, int fix);
    string getName() const;
    double getLen() const;
    double getDiam() const;
    int getFix() const;
    int getID() const;
    static int getNextId();

    ////void setID(int id) {};
    //void setName(string name);
    //void setLen(double len);
    //void setDiam(double diam);
    void setNext_ID(int next);
    void setFix(int Fix);


    friend ostream& operator << (ostream& ou, const Pipe& pipe);                                            //cout pipe
    friend fstream& operator << (fstream& out, const Pipe& pipe);                                                  //pipe to file for "map to file"
    friend fstream& operator >> (fstream& f, Pipe& pipe);                                                  //pipe to file for "map to file"
    friend istream& operator >> (istream& in, Pipe& pipe);                  

};