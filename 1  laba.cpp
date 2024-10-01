#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Puppe {
    string name = "";
    float len = -1;
    float diam = -1;
    int fix = -1;
};

struct KS {
    string name = "";
    int rooms = -1;
    int work = -1;
    float kpd= -1;
};

int operator << (fstream& in, Puppe& puppe) {
    int fl=1;
    if (puppe.name != "") {
        in << puppe.name << " ";
    }
    else {
        cout << "Pipe"<<endl<<"No name" << endl;
        fl = 0;
    }
    if (puppe.diam != -1) {
        in << puppe.len << " ";
        fl = 0;
    }
    else {
        cout << "No len" << endl;
        fl = 0;
    }
    if (puppe.diam != -1) {
        in << puppe.diam << " ";
    }
    else {
        cout << "No diam" << endl;
        fl = 0;
    }
    if (puppe.fix == 1 || puppe.fix == 0) {
        in << puppe.fix << " ";
    }
    else {
        cout << "No fix" << endl;
        fl = 0;
    }
    return fl;
}

void operator << (fstream& in, KS& ks) {
    if (ks.name != "") {
        in << ks.name << " ";
    }
    else {
        cout << "KS:"<<endl<< "No name" << endl;
    }
    if (ks.kpd != -1) {
        in << ks.kpd << " ";
    }
    else {
        cout << "No kpd" << endl;
    }
    if (ks.rooms != -1) {
        in << ks.rooms << " ";
    }
    else {
        cout << "No rooms" << endl;
    }
    if (ks.work != -1) {
        in << ks.work << " ";
    }
    else {
        cout << "No work" << endl;
    }
}

void operator >> (istream& in, Puppe& puppe) {
    cin.ignore(1000, '\n');
    cout << "Enter name:" << endl;
    getline(cin, puppe.name);
    cout << "Enter length:" << endl;
    in >> puppe.len;
    if (cin.fail() || puppe.len <= 0) {
        cout << "\nEnter Correct data" << endl;
    }
    cout << "Enter diametr:" << endl;
    in >> puppe.diam;
    if (cin.fail() || puppe.diam <= 0) {
        cout << "\nEnter Correct data" << endl;
    }
    cout << "Enter fix:" << endl;
    in >> puppe.fix;
    if (cin.fail() || puppe.fix != 0 || puppe.fix != 1) {
        cout << "\nEnter Correct data" << endl;
    }
}

void operator >> (istream& in, KS& ks) {
    cout << "Enter name:" << endl;
    if (ks.name != " ") {
        cin.ignore(1000, '\n');
        getline(cin, ks.name);
    }
    cout << "Enter rooms:" << endl;
    in >> ks.rooms;
    if (cin.fail() || ks.rooms < 0) {
        cout << "\nEnter Correct data" << endl;
    }
    cout << "Enter work:" << endl;
    in >> ks.work;
    if (cin.fail() || ks.work < 0) {
        cout << "\nEnter Correct data" << endl;
    }
    cout << "Enter kpd:" << endl;
    in >> ks.kpd;
    if (cin.fail() || ks.kpd <0 || ks.kpd >= 100) {
        cout << "\nEnter Correct data" << endl;
    }
}

void operator << (ostream& ou, Puppe& puppe) {
    if (puppe.name != " ") {
        cout << "Name: " << puppe.name << endl;
    }
    if (puppe.len != -1) {
        cout << "len: " << puppe.len << endl;;
    }
    if (puppe.diam != -1) {
        cout << "diam: " << puppe.diam << endl;
    }
    if (puppe.fix != -1) {
        cout << "fix: " << puppe.fix << endl;
    }
}

void operator << (ostream& ou, KS& ks) {
    if (ks.name != " ") {
        cout << "Name: " << ks.name << endl;
    }
    if (ks.rooms != -1) {
        cout << "Rooms: " << ks.rooms << endl;
    }
    if (ks.work != -1) {
        cout << "Work" << ks.work << endl;
    }
    if (ks.kpd != -1) {
        cout << "Kpd: " << ks.kpd << endl;
    }
}

void WriteToFile(fstream& f, Puppe& puppe, KS& ks) {
    if (f << puppe) {
        f << puppe;
    }
    else {
        f << '\n';
    }
    f << ks;
    f.close();
}

void ReadFile(Puppe& p, KS& k) {
    string outs;
    fstream file("file1.txt");
    if (!file.is_open()) {
        cout << "Error open file";
    }
    cout << "Pipe:" << endl;
    getline(file, outs);
    if (outs == ""){
        p.diam = -1; p.fix = -1; p.len = -1; p.name = "";
    }
    cout << outs<<endl;
    cout << "KS:" << endl;
    getline(file, outs);
    if (outs == "") {
        k.kpd = -1; k.rooms = -1; k.work = -1; k.name = "";
    }
    cout << outs << endl;
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
        switch (choice) {
        case 1:
            cin >> puppe1; break;
        case 2:
            cin >> ks1; break;
        case 3:
            int fx;
            cin >> fx;
            if (cin.fail() || fx < 0) {
                cout << "\nIncorrect data" << endl;
            }
            puppe1.fix = fx;
            break;
        case 4:
            int wk;
            cin >> wk;
            if (cin.fail() || wk < 0) {
                cout << "\nIncorrect data" << endl;
            }
            puppe1.fix = fx;
            break;
        case 5:
            WriteToFile(file, puppe1, ks1); break;
        case 6:
            ReadFile(puppe1, ks1); break;
        case 7:
            int choice2;
            cout << "What do you want to see?\n1. Pipe\n2. KS" << endl;
            cin >> choice2;
            switch (choice2) {
            case 1:
                cout << puppe1; break;
            case 2:
                cout << ks1; break;
            }
            break;
        case 8:
            fl = 0; break;
        default:
            cout << "Enter number from menu" << endl;
        }
    }
}
