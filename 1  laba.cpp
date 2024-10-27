#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include "Pipe.h"
#include "KS.h"
using namespace std;
/*
fstream& operator >> (fstream& f, Pipe& p) {
    getline(f>>ws, p.name);
    f >> p.len; 
    f >> p.diam; 
    f >> p.fix;
    if (p.name == "") {
        p = {};
    }
    if (f.fail())
    {
        cout << "Error data in file" << endl;
        p = {};
    }
    return f;
}

fstream& operator >> (fstream& f, KS& k) {
    getline(f>>ws, k.name);
    if (k.name == "") {
        k = {};
        return f;
    }
    f >> k.rooms;
    f >> k.work;
    f >> k.kpd;
    if (f.fail())
    {
        cout << "Error data in file" << endl;
        k = {};
    }
    return f;
}

fstream& operator << (fstream& in, Pipe& pipe) {
    if (pipe.name != "") {
        in << pipe.name << '\n';
    }
    else {
        cout << "No Pipe" << endl;
        return in;
    }
    in << pipe.len << '\n';
    in << pipe.diam << '\n';
    in << pipe.fix << '\n';
    return in;
}

fstream& operator << (fstream& in, KS& ks) {
    if (ks.name != "") {
        in << ks.name << '\n';
    }
    else {
        cout << "No KS" << endl;
        return in;
    }
    in << ks.kpd << '\n';
    in << ks.rooms << '\n';
    in << ks.work << '\n';
    return in;
}

istream& operator >> (istream& in, Pipe& pipe) {
    cout << "Enter name:" << endl;
    in.ignore(1000, '\n');
    getline(in, pipe.name);
    cout << "Enter length:" << endl;
    pipe.len = proverka(0.01, 10000.0);
    cout << "Enter diametr:" << endl;
    pipe.diam = proverka(0.01, 10000.0);
    cout << "Enter fix:" << endl;
    pipe.fix = proverka(0, 1);
    return in;
}

istream& operator >> (istream& in, KS& ks) {
    cout << "Enter name:" << endl;
    in.ignore(1000, '\n');
    getline(in, ks.name);
    cout << "Enter rooms:" << endl;
    ks.rooms = proverka(1, 1000);
    cout << "Enter work:" << endl;
    ks.work = proverka(0, 1000);
    cout << "Enter kpd:" << endl;
    ks.kpd = proverka(0.0, 100.0);
    return in;
}



ostream& operator << (ostream& ou, KS& ks) {
    if (ks.rooms != -1) {
        ou << "KS:\n"<<"Name: " << ks.name << endl;
        ou << "Rooms: " << ks.rooms << endl;
        ou << "Work: " << ks.work << endl;
        ou << "Kpd: " << ks.kpd << endl;
    }
    return ou;
}


void setFix(Pipe& chfx) {
    if (chfx.diam == -1) {
        cout << "No pipe" << endl;
        return;
    }
    cout << "Enter fix:" << endl;
    chfx.fix = proverka(0, 1);
}

void setWork(KS& chwk) {
    if (chwk.rooms == -1) {
        cout << "No pipe" << endl;
        return;
    }
    cout << "Enter fix:" << endl;
    chwk.work = proverka(0, 1);
}

void WriteToFile(fstream& f, Pipe& pipe, KS& ks) {
    string ind = "0";
    if (pipe.name != "") {
        ind = "1";
    }
    (ks.name != "")?  ind += " 1": ind += " 0";
    f << ind<<'\n';
    if (pipe.name != "") {
        f << pipe;

    }
    f << ks;
    f.close();
}

void ReadFile(Pipe& p, KS& k, fstream& file) {
    string ind;
    getline(file >> ws, ind);
    if (ind[0] == '1') { file >> p; }
    if (ind[2] == '1') { file >> k; }
    else { cout << "No data in file\n"; }
    cout << p;
    cout << k;
}
*/

#define LOG_FILE "log.txt";

#define CURRENT_TIME() [] {\
    time_t now = time(0);\
    tm* ltm = localtime(&now);\
    char buffer[20];\
    strftime(buffer, sizeof(buffer), %Y-%m-%d %H:%M:%S, ltm);\
    return string(buffer);\
}()

#define LOG(level, massege){\
    ofstream logFile(LOG_FILE, ios_base::app);\
    if (logFile.is_open()){\
        logFile << "["<<CURRENT_TIME<<"] ["<< level << "] "<<massege<<endl;\
        logFile.close();\
    } else { \
        cerr << "Error opening log file"<<endl;}\
}

#define LOG_INFO(massege) LOG("INFO", massege)
#define LOG_ERROR(massege) LOG("ERROR", massege)


void LoadFromFile(fstream& f, unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    string Fname;
    cout << "Enter File name" << endl;
    cin >> Fname;
    fstream file(Fname);
    string ind;
    getline(f >> ws, ind);
    if (!stoi(ind)) {
        cout << "Wrong data in file" << endl;
        return;
    }
    int count = stoi(ind);
    if (stoi(ind) != 0) {
        FtoPipemap(count, p, f);
    }
    getline(f >> ws, ind);
    if (!stoi(ind)) {
        cout << "Wrong data in file" << endl;
        return;
    }
    count = stoi(ind);
    if (stoi(ind) != 0) {
        //FtoKSmap(count, p, f);
    }
}

void SaveToFile(unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    string Fname;
    cout << "Enter File name" << endl;
    getline(cin, Fname);
    fstream f(Fname);
    string ind;
    ind = to_string(p.size());
    f << ind << '\n';
    ind = to_string(p.size());
    f << ind << '\n';
    f << p;
    //f << k;
    f.close();
}

void Pack(vector<int> vec, unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    int ch1, ch2;
    cout << "1. Delete\n2. Edit" << endl;
    cin >> ch1;
    cout << "1. Pipe\n2. KS" << endl;
    switch (ch2) {
    case 1:
        switch (ch1) {
        case 1: DeletePackPipe(p, vec);
        case 2: EditPackPipe(p, vec);
        }
    case 2:
        switch (ch2) {
        case 1: //DeletePackKS(k, vec);
        case 2: //EditPackKS(k, vec);
        }
    }
}

vector<int> HandVec(unordered_map<int, Pipe>& p) {
    vector<int> vec;
    int id;
    cout << "Enter id of pipes. For stop press -1" << endl;
    while (true) {
        cin >> id;
        if (id == -1) { return vec; }
        auto it = p.find(id);
        if (it != p.end()) {
            vec.push_back(it->first);
        }
        else { cout << "Wrong id. Try again: "; }
    }
}

vector<int> MakeVec(unordered_map<int, Pipe>& p) {
    vector<int> vec;
    int choice;
    cout << "1. I want to enter id\n2. I want to sort map" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        return HandVec(p);
    case 2:
        int flag;
        while (flag) {
            cout << "Do you want to continue finding?(0, 1)" << endl;
            cin >> flag;
            FindForParam(p, vec);
        }
    }
    return vec;
}

int main()
{
 /*   fstream file("file1.txt");
    if (!file.is_open()) {
        cout << "Error open file";
        return 0; 
    }
    Pipe pipe1;
    KS ks1;
    int choice;
    bool fl = 1;
    while (fl) {
        cout << "\n1. Create Pipe\n2. Create KS\n3. Change fixing status\n4. Change number of working KS\n5. Write to file\n6. Read from file\n7. Read data\n8. Exit" << endl;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Only digit" << endl;
            continue;
        }
        switch (choice) {
        case 1:
            cin >> pipe1; break;
        case 2:
            cin >> ks1; break;
        case 3:
            setFix(pipe1); break;
        case 4:
            setWork(ks1); break;
        case 5:
            file.seekp(0, ios::beg);
            WriteToFile(file, pipe1, ks1); break;
        case 6:
            ReadFile(pipe1, ks1, file); break;
        case 7:
            cout << pipe1;
            cout << ks1;
            break;
        case 8:
            fl = 0; break;
        default:
            cout << "Enter number from menu" << endl;
        }
    }*/
}
