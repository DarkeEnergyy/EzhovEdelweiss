#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include <utility>
#include "Pipe.h"
#include "KS.h"
#include "Proverka.h"
#include "Filtr.h"
#include <chrono>
#include <format>


using namespace std;
using namespace chrono;


#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl



unordered_map<int, Pipe>& FtoPipemap(int& count, unordered_map<int, Pipe>& map, fstream& f) {
    map.clear();
    for (int j = 0; j < count; j++) {
        if (f.fail())
        {
            cout << "Error data in file" << endl;
            return map;
        }
        Pipe pipe(f);
        map.emplace(pipe.getID(), pipe);
    }
    return map;
}
Pipe newPipe() {
    Pipe pipe;
    cin >> pipe;
    return pipe;
}
void PipeToMap(unordered_map<int, Pipe>& p) {
    cerr << "Add new pipe:" << endl;
    Pipe pipe = newPipe();
    if (p.contains(pipe.getID())) {
        int choice;
        cout << "Pipe with this id is already in map. Do you want to rewrite it?" << endl;
        cerr << "KS with this id is already in map. Do you want to rewrite it?: ";
        choice = proverka(0, 1);
        if (!choice) {
            cerr << "KS wasn't added. Cause: same id exist" << endl;
            return;
        }
    }
    p.erase(pipe.getID());
    p.emplace(pipe.getID(), pipe);
}
void changeFix(unordered_map<int, Pipe>& p) {
    cout << "Enter id of changing pipe" << endl;
    cerr << "Changing fix of pipe with id; to status: " << endl;
    int idfind = proverka(1, 1000);
    bool fl = 0;
    if (p.contains(idfind))
    {
        cout << "enter fix: " << endl;
        p[idfind].setFix(proverka(0, 1));
    }
    else {
        cerr << "no id, changing fix is interrapted" << endl;
        cout << "no id" << endl;
    }
}
void DeletePackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cerr << "No pipes for delete" << endl; cout << "No pipes for delete(vec0)" << endl; return; }
    for (auto& a : vec) {
        auto it = p.find(a);
        if (it != p.end()) {
            p.erase(it);
        }
        else {
            cerr << "Wrong element in vector" << endl;
            cout << "Wrong element in vector" << endl;
        }
    }
}
void EditPackPipe(unordered_map<int, Pipe>& p, vector<int>& vec) {
    if (vec.size() == 0) { cerr << "No pipes for edit(vec0)" << endl; cout << "No pipes for edit(vec0)" << endl; return; }
    cout << "What Fix do you wnat to install: ";
    cerr << "Fix: ";
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

template <typename T1, typename T2>
vector<int> Find(unordered_map<int, T1>& map, vector<int>& vec, Filtr<T1, T2> f, T2 param) {
    vector<int> found;

    cout << "Where you want to find: \n1. Map \n2.Vec" << endl;
    switch (proverka(1, 2)) {
    case 1:
        for (auto& [id, obj] : map) {
            if (f(obj, param)) {
                found.push_back(obj.getID());
            }
        }
        // OutVec(found, p);
    }
    if (found.size() == 0)
        cout << "No such objects" << endl;

    return found;
}

vector<int> FindForParam(unordered_map<int, Pipe>& p, vector<int>& vec) {
    cout << "For what do you want to find: \n1. Name \n2. Fix" << endl;
    switch (proverka(1, 4)) {
    case 1:
    {
        string s;
        INPUT_LINE(cin, s);
        return Find(p, vec, FiltrName, s);
    }
    case 2:
    {
        int param = proverka(0, 1);
        return Find(p, vec, FiltrFix, param);
    }
    }
}

vector<int> FindForParam(unordered_map<int, KS>& k, vector<int>& vec) {
    cout << "For what do you want to find: \n1. Name \n2. Work" << endl;
    switch (proverka(1, 4)) {
    case 1:
    {
        string s;
        INPUT_LINE(cin, s);
        return Find(k, vec, FiltrName, s);
    }
    case 2:
    {
        int param = proverka(0, 1);
        return Find(k, vec, FiltrWork, param);
    }
    }
}

unordered_map<int, KS>& FtoKSmap(int& count, unordered_map<int, KS>& map, fstream& f) {
    map.clear();
    for (int j = 0; j < count; j++) {
        if (f.fail())
        {
            cout << "Error data in file" << endl;
            return map;
        }
        KS ks(f);
        map.emplace(ks.getID(), ks);
        ks.setNext_ID(ks.getID());
    }
    return map;
}
KS newKS() {
    KS ks;
    cin >> ks;
    return ks;
}
void KSToMap(unordered_map<int, KS>& k) {
    cerr << "Add KS: " << endl;
    KS ks = newKS();
    if (k.contains(ks.getID())) {
        int choice;
        cout << "KS with this id is already in map. Do you want to rewrite it?" << endl;
        cerr << "KS with this id is already in map. Do you want to rewrite it?: ";
        choice = proverka(0, 1);
        if (!choice) {
            cerr << "KS wasn't added. Cause: same id exist" << endl;
            return;
        }
    }
    k.erase(ks.getID());
    k.emplace(ks.getID(), ks);
}
//vector<int> FindForParam(unordered_map<int, KS>& k, vector<int>& vecKs) {
//    vector<int> found;
//    string name = "";
//    double room = -1;
//    double work = -1;
//    int kpd = -1;
//    cout << "For what do you want to find: \n1. Name\n2. Roomgth\n3. Worketr \n4. Kpd" << endl;
//    switch (proverka(1,4)) {
//    case 1: cin.ignore(100, '\n'); getline(cin >> ws, name); break;
//    case 2: room = proverka(0, 10000); break;
//    case 3: work = proverka(0, 10000); break;
//    case 4: kpd = proverka(0, 100); break;
//    }
//    cout << "Where you want to find: \n1. Map \n2.vec" << endl;
//    switch (proverka(1, 2)) {
//    case 1:
//        for (auto& [id, ks] : k) {
//            if (ks.getKpd() == kpd || ks.getWork() == work || ks.getRoom() == room || ks.getName() == name) {
//                found.push_back(ks.getID());
//            }
//        }
//        OutVec(found, k);
//        return found;
//    case 2:
//        int i = 0;
//        for (auto& [id, ks] : k) {
//            if (id == vecKs[i]) {
//                if (ks.getKpd() == kpd || ks.getWork() == work || ks.getRoom() == room || ks.getName() == name) {
//                    found.push_back(ks.getID());
//                    ++i;
//                }
//                else { cout << "Wrong data in vector" << endl; return found; }
//            }
//        }
//    }
//    if (found.size() == 0) {
//        cout << "No such ks" << endl;
//    }
//    OutVec(found, k);
//    return found;
//}
void changeWork(unordered_map<int, KS>& k) {
    cerr << "Changing fix of pipe with id; to status: " << endl;
    cout << "Enter id of changing pipe" << endl;
    int idfind = proverka(1, 1000);
    bool fl = 0;
    for (auto& [id, ks] : k) {
        if (id == idfind) {
            ks.setWork(proverka(0, 1));
            fl = 1;
        }
    }
    if (!fl) {
        cerr << "no id, changing fix is interrapted" << endl;
        cout << "Wrong id" << endl;
    }
}
void DeletePackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
    if (vecKs.size() == 0) { cerr << "No pipes for delete" << endl; cout << "No ks for delete(vec0)" << endl; return; }
    for (auto& a : vecKs) {
        auto it = k.find(a);
        if (it != k.end()) {
            k.erase(it);
        }
        else {
            cerr << "Wrong element in vector" << endl;
            cout << "Wrong element in vector" << endl;
        }
    }
}
void EditPackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
    if (vecKs.size() == 0) { cerr << "No ks for edit(vec0)" << endl; cout << "No ks for edit(vec0)" << endl; return; }
    cout << "What Kpd do you wnat to install: ";
    cerr << "Kpd: " << endl;
    int kpd = proverka(0, 1);
    for (auto& a : vecKs) {
        auto it = k.find(a);
        if (it != k.end()) {
            it->second.setWork(kpd);
        }
        else {
            cout << "Wrong element in vector" << endl;
            cout << "Wrong element in vector" << endl;
        }
    }
}

void Pack(vector<int>& vecP, vector<int>& vecK, unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {//??
    if (vecP.size() == 0) { vecP = MakeVec(p); }
    cout << "1.Pipe\n2. KS" << endl;
    cout << "1. Delete\n2. Edit" << endl;
    cerr << "Pack: Pipe, Ks; Delete, Edit: " << endl;
    int ch = proverka(1, 2);
    switch (ch) {
    case 1: {
        switch (proverka(1, 2)) {
        case 1: DeletePackPipe(p, vecP); break;
        case 2: EditPackPipe(p, vecP); break;
        }
        break;
    }
    case 2: {
        switch (proverka(1, 2)) {
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
    cerr << "Load from file: " << Fname << endl;
    fstream file(Fname);
    if (!file.is_open()) {
        cerr << "File wasn't open" << endl;
        cout << "Wrong name of file" << endl;
        return;
    }
    string indP, indK;
    getline(file >> ws, indP);
    getline(file >> ws, indK);
    if (!stoi(indP) && stoi(indP)!=0 || !stoi(indK) && stoi(indK) != 0) {
        cout << "Wrong data in file" << endl;
        cerr << "Wrong data in file" << endl;
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
    cerr << "Saving to file: " << Fname << endl;
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
    redirect_output_wrapper cerr_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);

    vector<int> vecPipe, vecKS;
    unordered_map<int, Pipe> pipeMap;
    unordered_map<int, KS> ksMap;
    int choice;
    bool fl = 1;
    while (fl) {
        cout << "\n1. Add Pipe to map\n2. Add KS to map\n3. Change fixing status\n4. Change number of working\
KS\n5. Write to file\n6. Read from file\n7. Read data\n8. Choose some pipes or kss(Create vec)\n9. Delete vector\n10. Package edit\n\
11. Filter Pipes(Make vec)\n12. Filter Kss(Make vec)\n13 Read vector\n0. Exit" << endl;
        cerr << "Entered number in menu: ";
        switch (proverka(0, 13)) {
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
        case 8:
        {
            cout << "1. Pipe\n2. KS" << endl;
            switch (proverka(1, 2))
            {
            case 1:
            {
                vecPipe = MakeVec(pipeMap);
                break;
            }
            case 2:
            {
                vecKS = MakeVec(ksMap);
                break;
            }
            }
            break;
        }
        case 9:
            cout << "1. Delete vector of Pipes\n2. Delete vector of Kss" << endl;
            switch (proverka(1, 2)) {
            case 1:
                vecPipe = {}; break;
            case 2:
                vecKS = {}; break;
            } break;
        case 10:
            Pack(vecPipe, vecKS, pipeMap, ksMap); break;
        case 11:
            vecPipe = FindForParam(pipeMap, vecPipe);
            break;
        case 12:
            vecKS = FindForParam(ksMap, vecPipe); break;
        case 13:
            cout << "1. Cout vector of Pipes\n2. Cout vector of Kss" << endl;
            switch (proverka(1, 2)) {
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
}

