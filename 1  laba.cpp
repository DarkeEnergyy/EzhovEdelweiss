#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include <utility>
#include "Pipe.h"
#include "KS.h"
#include "Proverka.h"

//ID and NextID without ++
//logging from Git
//cout vec

using namespace std;

#include <iostream>
#include <fstream>
#include <string>

#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>


class CinLogger : public streambuf {
public:
    CinLogger(istream& input, const string& filename)
        : originalBuffer(input.rdbuf()), logFile(filename, ios::out) {
        if (!logFile.is_open()) {
            throw ios_base::failure("Не удалось открыть файл для логирования.");
        }
        input.rdbuf(this);
    }

    ~CinLogger() {
        cin.rdbuf(originalBuffer);
        if (logFile.is_open()) {
            logFile.close();
        }
    }

protected:
    int overflow(int c) override {
        if (c != EOF) {
            logFile.put(static_cast<char>(c));
            logFile.flush();
        }
        return originalBuffer->sputc(c);
    }

private:
    streambuf* originalBuffer;
    ofstream logFile;
};


int& ProverCin(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || min > choice || max < choice) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter correct data" << endl;
            continue;
        }
        return choice;
    }
}

template<typename T>
void OutVec (vector<int>& vec, unordered_map<int, T>& p) {
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            cout << it->second << endl;
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
    cout << endl;
}

unordered_map<int, Pipe>& FtoPipemap(int& count, unordered_map<int, Pipe>& map, fstream& f) {
    map.clear();
    string nam = "";
    double len = -1;
    double diam = -1;
    int fix = -1;
    double a;
    for (int j = 0; j < count; j++) {
        getline(f>>ws, nam);
        f >> len;
        f >> diam;
        f >> fix;
        if (nam == "") {
            return map;
        }
        if (f.fail())
        {
            cout << "Error data in file" << endl;
            return map;
        }
        Pipe pipe(nam, len, diam, fix);
        map.emplace(pipe.getID(), pipe);
    }
    return map;
}
//pipe in
Pipe newPipe() {
    Pipe pipe;
    string nam;
    cout << "Enter name:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, nam);
    pipe.setName(nam);
    cout << "Enter length:" << endl;
    pipe.setLen(proverka(0.01, 10000.0));
    cout << "Enter diametr:" << endl;
    pipe.setDiam(proverka(0.01, 10000.0));
    cout << "Enter fix:" << endl;
    pipe.setFix(proverka(0, 1));
    return pipe;
}
void PipeToMap(unordered_map<int, Pipe>& p) {
    Pipe pipe = newPipe();
    p.emplace(pipe.getID(), pipe);
}
void changeFix(unordered_map<int, Pipe>& p) {
    cout << "Enter id of changing pipe" << endl;
    int idfind = proverka(1, 10000);
    bool fl = 0;
    for (auto& [id, pipe] : p) {
        if (id == idfind) {
            pipe.setFix(proverka(0, 1));
            fl = 1;
        }
    }
    if (!fl) {
        cout << "Wrong id" << endl;
    }
}
void DeletePackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cout << "No pipes for delete(vec0)" << endl; return; }
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            p.erase(it);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}
void EditPackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cout << "No pipes for edit(vec0)" << endl; return; }
    cout << "What Fix do you wnat to install: ";
    int fix = proverka(0, 1);
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            it->second.setFix(fix);
        }
        else {
            cout << "Wrong element in vector" << endl;
        }
    }
}
vector<int> FindForParam(unordered_map<int, Pipe>& p, vector<int>& vec) {
    vector<int> found;
    string name = "";
    double len = -1;
    double diam = -1;
    int fix = -1;
    cout << "For what do you want to find: \n1. Name\n2. Length\n3. Diametr \n4. Fix" << endl;
    switch (ProverCin(1, 4)) {
    case 1: cin.ignore(100, '\n'); getline(cin >> ws, name); break;
    case 2: len = proverka(0.0, 10000.0); break;
    case 3: diam = proverka(0.0, 10000.0); break;
    case 4: fix = proverka(0, 1); break;
    }
    cout << "Where you want to find: \n1. Map \n2.Vec" << endl;
    switch (ProverCin(1,2)) {
    case 1:
        for (auto& [id, pipe] : p) {
            if (pipe.getFix() == fix || pipe.getDiam() == diam || pipe.getLen() == len || pipe.getName() == name) {
                found.push_back(pipe.getID());
            }
        }
        OutVec(found, p);
        return found;
    case 2:
        int i = 0;
        for (auto& [id, pipe] : p) {
            if (id == vec[i]) {
                if (pipe.getFix() == fix || pipe.getDiam() == diam || pipe.getLen() == len || pipe.getName() == name) {
                    found.push_back(pipe.getID());
                    ++i;
                }
            }
        }
    }
    if (found.size() == 0) {
        cout << "No such pipes" << endl;
    }
    OutVec(found, p);
    return found;
}

//file to map with number of ks
unordered_map<int, KS>& FtoKSmap(int& count, unordered_map<int, KS>& map, fstream& f) {
    map.clear();
    KS ks;
    string nam = "";
    double room = -1;
    double work = -1;
    int kpd = -1;
    for (int j = 0; j < count; j++) {
        getline(f, nam);
        ks.setName(nam);
        f >> room;
        f >> work;
        f >> kpd;
        if (nam == "") {
            return map;
        }
        if (f.fail())
        {
            cout << "Error data in file" << endl;
            return map;
        }
    }
    return map;
}
//ks in
KS newKS() {
    KS ks;
    string nam;
    cout << "Enter name:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, nam);
    ks.setName(nam);
    cout << "Enter room:" << endl;
    ks.setRoom(proverka(0.01, 10000.0));
    cout << "Enter work:" << endl;
    ks.setWork(proverka(0.01, 10000.0));
    cout << "Enter kpd:" << endl;
    ks.setKpd(proverka(0, 1));
    return ks;
}
void KSToMap(unordered_map<int, KS>& k) {
    KS ks = newKS();
    k.emplace(ks.getNextId(), ks);
}
vector<int> FindForParam(unordered_map<int, KS>& k, vector<int>& vecKs) {
    vector<int> found;
    string name = "";
    double room = -1;
    double work = -1;
    int kpd = -1;
    cout << "For what do you want to find: \n1. Name\n2. Roomgth\n3. Worketr \n4. Kpd" << endl;
    switch (ProverCin(1,4)) {
    case 1: cin.ignore(100, '\n'); getline(cin >> ws, name); break;
    case 2: room = proverka(0, 10000); break;
    case 3: work = proverka(0, 10000); break;
    case 4: kpd = proverka(0, 100); break;
    }
    cout << "Where you want to find: \n1. Map \n2.vec" << endl;
    switch (ProverCin(1, 2)) {
    case 1:
        for (auto& [id, ks] : k) {
            if (ks.getKpd() == kpd || ks.getWork() == work || ks.getRoom() == room || ks.getName() == name) {
                found.push_back(ks.getID());
            }
        }
        OutVec(found, k);
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
    OutVec(found, k);
    return found;
}
void changeWork(unordered_map<int, KS>& k) {
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
void DeletePackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
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
void EditPackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
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
}

vector<int> HandVec(unordered_map<int, KS>& k) {
    vector<int> vec;
    int id;
    cout << "Enter id of ks. For stop press -1" << endl;
    while (true) {
        cin >> id;
        if (id == -1) { OutVec(vec, k); return vec; }
        auto it = k.find(id);
        if (it != k.end()) {
            vec.push_back(it->first);
        }
        else { cout << "Wrong id. Try again: "; }
    }
}
vector<int> HandVec(unordered_map<int, Pipe>& p) {
    vector<int> vec;
    int id;
    cout << "Enter id of pipes. For stop press -1" << endl;
    while (true) {
        cin >> id;
        if (id == -1) { OutVec(vec, p); return vec; }
        auto it = p.find(id);
        if (it != p.end()) {
            vec.push_back(it->first);
        }
        else { cout << "Wrong id. Try again: "; }
    }
}
pair<vector<int>, int> MakeVec(unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    vector<int> vec;
    int h = 0;
    cout << "1. I want to enter id\n2. I want to filtr map or vec" << endl;
    switch (ProverCin(1, 2)) {
    case 1:
    {
        cout << "1. Pipe\n2. KS" << endl;
        switch (ProverCin(1, 2))
        {
        case 1: {
            vec = HandVec(p);
            h = 1;
            break;
        }
        case 2: {
            vec = HandVec(k);
            h = 2;
            break;
        }

        }
        break;
    }
    case 2: {
        int flag = 1;
        cout << "1. Pipe\n2. KS" << endl;
        switch (ProverCin(1, 2)) {
        case 1: {
            while (flag) {
                vec = FindForParam(p, vec);
                cout << "Do you want to continue finding?(0, 1)" << endl;
                h = 1;
                cin >> flag;
            }
            break;
        }
        case 2: {
            while (flag) {
                vec = FindForParam(k, vec);
                cout << "Do you want to continue finding?(0, 1)" << endl;
                h = 2;
                cin >> flag;
            }
            break;
        }
        }
        break;
    }
    }
    return make_pair(vec, h);
}


void Pack(vector<int>& vecP, vector<int>& vecK, unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    if (vecP.size() == 0) { vecP = MakeVec(p, k).first; }
    cout << "1.Pipe\n2. KS" << endl;
    cout << "1. Delete\n2. Edit" << endl;
    int ch = ProverCin(1, 2);
    switch (ch) {
    case 1: {
        switch (ProverCin(1, 2)) {
        case 1: DeletePackPipe(p, vecP); break;
        case 2: EditPackPipe(p, vecP); break;
        }
        break;
    }
    case 2: {
        switch (ProverCin(1, 2)) {
        case 1: DeletePackKS(k, vecK); break;
        case 2: EditPackKS(k, vecK); break;
        }
        break;
    }
    }
}


void LoadFromFile(unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    string Fname;
    cout << "Enter File name" << endl;
    cin.ignore(100, '\n');
    getline(cin, Fname);
    fstream file(Fname);
    string indP, indK;
    getline(file >> ws, indP);
    getline(file >> ws, indK);
    if (!stoi(indP) && stoi(indP)!=0 || !stoi(indK) && stoi(indK) != 0) {
        cout << "Wrong data in file" << endl;
        return;
    }
    int count = stoi(indP);
    if (stoi(indP) != 0) {
        FtoPipemap(count, p, file);
    }
    count = stoi(indK);
    if (stoi(indK) != 0) {
        FtoKSmap(count, k, file);
    }
}


void SaveToFile(unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    string Fname;
    cout << "Enter File name" << endl;
    cin.ignore(100, '\n');
    getline(cin, Fname);
    fstream f(Fname);
    f.seekg(0);
    string ind;
    ind = to_string(p.size());
    f << ind << '\n';
    ind = to_string(k.size());
    f << ind << '\n';
    f << p;
    f << k;
    f.close();
}


int main()
{
    /*fstream file("file1.txt");
    if (!file.is_open()) {
        cout << "Error open file";
        return 0;
    }*/
    //try {
        //CinLogger logger(cin, "LOG.txt");

    vector<int> vecPipe, vecKS;
    unordered_map<int, Pipe> pipeMap;
    unordered_map<int, KS> ksMap;
    int choice;
    bool fl = 1;
    while (fl) {
        cout << "\n1. Add Pipe to map\n2. Add KS to map\n3. Change fixing status\n4. Change number of working\
KS\n5. Write to file\n6. Read from file\n7. Read data\n8. Choose some pipes or kss(Create vec)\n9. Delete vector\n10. Package edit\n\
11. Filter Pipes(Make vec)\n12. Filter Kss(Make vec)\n13 Read vector\n0. Exit" << endl;
        switch (ProverCin(0, 13)) {
        case 1:
            PipeToMap(pipeMap); break;
        case 2:
            KSToMap(ksMap); break;
        case 3:
            changeFix(pipeMap); break;
        case 4:
            changeWork(ksMap); break;
        case 5:
            SaveToFile(pipeMap, ksMap); break;
        case 6:
            LoadFromFile(pipeMap, ksMap); break;
        case 7:
            cout << "Map of pipe: " << endl << pipeMap;
            cout << "Map of ks: " << endl << ksMap;
            break;
        case 8: {
            auto res = MakeVec(pipeMap, ksMap);
            if (res.second == 1) {
                vecPipe = res.first;
            }
            else {
                vecKS = res.first;
            }
        }break;
        case 9:
            cout << "1. Delete vector of Pipes\n2. Delete vector of Kss" << endl;
            switch (ProverCin(1, 2)) {
            case 1:
                vecPipe = {}; break;
            case 2:
                vecKS = {}; break;
            } break;
        case 10:
            Pack(vecPipe, vecKS, pipeMap, ksMap); break;
        case 11:
            vecPipe = FindForParam(pipeMap, vecPipe); break;
        case 12:
            vecKS = FindForParam(ksMap, vecPipe); break;
        case 13:
            cout << "1. Cout vector of Pipes\n2. Cout vector of Kss" << endl;
            switch (ProverCin(1, 2)) {
            case 1: {
                for (auto a : vecPipe) {
                    cout << a << ", ";
                }
            } break;
            case 2: {
                for (auto a : vecKS) {
                    cout << a << ", ";
                }
            } break;
            cout << endl;
            }break;
        case 0:
            fl = 0; break;
        default:
            cout << "Enter number from menu" << endl;
        }
    }
    /* }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }*/
}
