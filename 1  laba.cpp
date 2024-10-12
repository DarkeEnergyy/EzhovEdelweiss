#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
using namespace std;

struct Puppe {
    string name;
    float len=-1;
    float diam=-1;
    int fix = -1;
};

struct KS {
    string name;
    int rooms=-1;
    int work=-1;
    float kpd=-1;
};
template <typename T1>
T1 proverka(T1 min, T1 max) {
    T1 i;
    cout << "Enter number in range: "<<min<<"; "<<max << endl;
    while (true) {
        cin >> i;
        if (cin.fail() || i < min || i>max) {
            cout << "Enter Correct data" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        return i;
    }
}

fstream& operator >> (fstream& f, Puppe& p) {
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

fstream& operator << (fstream& in, Puppe& puppe) {
    if (puppe.name != "") {
        in << puppe.name << '\n';
    }
    else {
        cout << "No Pipe" << endl;
        return in;
    }
    in << puppe.len << '\n';
    in << puppe.diam << '\n';
    in << puppe.fix << '\n';
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

istream& operator >> (istream& in, Puppe& puppe) {
    cout << "Enter name:" << endl;
    in.ignore(1000, '\n');
    getline(in, puppe.name);
    cout << "Enter length:" << endl;
    puppe.len = proverka(0.01, 10000.0);
    cout << "Enter diametr:" << endl;
    puppe.diam = proverka(0.01, 10000.0);
    cout << "Enter fix:" << endl;
    puppe.fix = proverka(0, 1);
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

ostream& operator << (ostream& ou, Puppe& puppe) {
    if (puppe.len != -1) {
        ou << "Pipe:\n" << "Name: " << puppe.name << endl;
        ou << "len: " << puppe.len << endl;
        ou << "diam: " << puppe.diam << endl;
        ou << "fix: " << puppe.fix << endl;
    }
    return ou;
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

void setFix(Puppe& chfx) {
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

void WriteToFile(fstream& f, Puppe& puppe, KS& ks) {
    string ind = "0";
    if (puppe.name != "") {
        ind = "1";
    }
    (ks.name != "")?  ind += " 1": ind += " 0";
    f << ind<<'\n';
    if (puppe.name != "") {
        f << puppe;

    }
    f << ks;
    f.close();
}

void ReadFile(Puppe& p, KS& k, fstream& file) {
    string ind;
    getline(file >> ws, ind);
    if (ind[0] == '1') { file >> p; }
    if (ind[2] == '1') { file >> k; }
    else { cout << "No data in file\n"; }
    cout << p;
    cout << k;
}

int main()
{
    fstream file("file1.txt");
    if (!file.is_open()) {
        cout << "Error open file";
        return 0; 
    }
    Puppe puppe1;
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
            cin >> puppe1; break;
        case 2:
            cin >> ks1; break;
        case 3:
            setFix(puppe1); break;
        case 4:
            setWork(ks1); break;
        case 5:
            file.seekp(0, ios::beg);
            WriteToFile(file, puppe1, ks1); break;
        case 6:
            ReadFile(puppe1, ks1, file); break;
        case 7:
            cout << puppe1;
            cout << ks1;
            break;
        case 8:
            fl = 0; break;
        default:
            cout << "Enter number from menu" << endl;
        }
    }
}
