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
//#include <format>
#include "Graph.h"
#include <clocale>


using namespace std;
using namespace chrono;


#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl


template <typename T>
unordered_map<int, T> File2Map(int count, fstream& f){
    unordered_map<int, T> map;
    for (int j = 0; j < count; j++) {
        if (f.fail())
        {
            cout << "Error data in file" << endl;
            return map;
        }
        T obj(f);
        map.emplace(obj.getID(), obj);
    }
    T::setNext_ID(map);
    return map;
}
Pipe newPipe() {
    Pipe pipe;
    cin >> pipe;
    return pipe;
}

Pipe PipeToMap(unordered_map<int, Pipe>& p) {
    Pipe pipe = newPipe();
    p.emplace(pipe.getID(), pipe);
    return pipe;
}
void changeFix(unordered_map<int, Pipe>& p) {
    cout << "Enter id of changing pipe" << endl;
    int idfind = proverka(1, 1000);
    bool fl = 0;
    if (p.count(idfind))
    {
        cout << "enter fix: " << endl;
        p[idfind].setFix(proverka(0, 1));
    }
    else {
        cout << "no id" << endl;
    }
}

template<typename T, typename Graph>
bool isObjectInGraph(const Graph& graph, int id) {
    if constexpr (std::is_same_v<T, Pipe>) {
        for (const auto& [from, edges] : graph.getsmejn()) {
            for (const auto& edge : edges) {
                if (edge.pipe_id == id) {
                    return true;
                }
            }
        }
    }
    else if constexpr (std::is_same_v<T, KS>) {
        for (const auto& [from, edges] : graph.getsmejn()) {
            for (const auto& edge : edges) {
                if (edge.to == id || edge.from == id) { 
                    return true; 
                }
            }
        }
    }
    return false; 
}

template <typename T>
void DeletePack(unordered_map<int, T>& p, vector<int>& vec, GasTransportGraph graph) {
    if (vec.size() == 0) 
    {
        cout << "No objects for delete(vec0)" << endl; 
        clog << "No objects for delete(vec0)" << endl; 
        return;
    }
    for (auto& id : vec) {
        if (p.count(id)) {
            if (isObjectInGraph<T>(graph, id)) {
                cout << "Object " << id << " is in Graph. Do you realy want to delete it(Millions will die)?" << endl;
                if (proverka(0, 1)) {
                    p.erase(id);
                }
            }
        }
        else {
            clog << "Wrong element in vector" << endl;
            cout << "Wrong element in vector" << endl;
        }
        vec.clear();
    }
}
void EditPackPipe(unordered_map<int, Pipe>& p, vector<int>& vec, GasTransportGraph graph) {
    if (vec.size() == 0) 
    {
        cout << "No pipes for edit(vec0)" << endl;
        return;
    }
    cout << "What Fix do you wnat to set: ";
    clog << "Fix: ";
    int fix = proverka(0, 1);
    for (auto& a : vec) {
        if (p.count(a)) {
            p[a].setFix(fix);
            //    // Перерасчет пропускной способности трубы
            //    double new_capacity;
            //    if (fix) {
            //        new_capacity = 0;
            //    }
            //    else {  
            //        p[a].calculateCapacity(); 
            //        new_capacity = p[a].getCapacity();
            //    }

            //    for (auto& [from, edges] : graph.getsmejn()) {
            //        for (auto& edge : edges) {
            //            if (edge.pipe_id == a) {
            //                // Обновляем производительность ребра в графе
            //                edge.setCapacity(new_capacity);
            //                cout << "Updated capacity for edge (" << from << " -> " << edge.to
            //                    << ") with pipe ID " << a << ": " << new_capacity << endl;
            //            }
            //        }
            //    }
            //}
            //else {
            //    cout << "Wrong element in vector: Pipe ID " << a << " not found" << endl;
            //}
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
        return Find(p, vec, FiltrName, InputString());
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
        return Find(k, vec, FiltrName, InputString());
    }
    case 2:
    {
        int param = proverka(0, 1);
        return Find(k, vec, FiltrWork, param);
    }
    }
}

KS newKS() {
    KS ks;
    cin >> ks;
    return ks;
}
void KSToMap(unordered_map<int, KS>& k) {
    clog << "Add KS: " << endl;
    KS ks = newKS();
    /*if (k.count(ks.getID())) {
        int choice;
        cout << "KS with this id is already in map. Do you want to rewrite it?" << endl;
        clog << "KS with this id is already in map. Do you want to rewrite it?: ";
        choice = proverka(0, 1);
        if (!choice) {
            clog << "KS wasn't added. Cause: same id exist" << endl;
            return;
        }
    }
    k.erase(ks.getID());*/
    k.emplace(ks.getID(), ks);
}

void changeWork(unordered_map<int, KS>& k) {
    clog << "Changing fix of pipe with id; to status: " << endl;
    cout << "Enter id of changing pipe" << endl;
    int idfind = proverka(1, KS::getNextId());
    if (k.count(idfind))
        k[idfind].setWork(proverka(0, 1));
    else
        cout << "Wrong id" << endl;
}

void EditPackKS(unordered_map<int, KS>& k, vector<int>& vecKs) {
    if (vecKs.size() == 0)
    {
        clog << "No ks for edit(vec0)" << endl;
        cout << "No ks for edit(vec0)" << endl;
        return;
    }
    cout << "What Kpd do you wnat to set: ";
    clog << "Kpd: " << endl;
    int kpd = proverka(0, 1);
    for (auto& a : vecKs)
        if (k.count(a))
            k[a].setWork(kpd);
        else
            cout << "Wrong element in vector" << endl;
    clog << "Wrong element in vector" << endl;
}

void Pack(vector<int>& vecP, vector<int>& vecK, unordered_map<int, Pipe>& p, unordered_map<int, KS>& k, GasTransportGraph graph) {
    if (vecP.size() == 0) { 
        cout << "1.Pipe\n2. KS" << endl;
        if (proverka(1, 2) == 1) {
            vecP = MakeVec(p);
        }
        else { vecK = MakeVec(k); }
    }
    cout << "1.Pipe\n2. KS" << endl;
    cout << "1. Delete\n2. Edit" << endl;
    clog << "Pack: Pipe, Ks; Delete, Edit: " << endl;
    int ch = proverka(1, 2);
    switch (ch) {
    case 1: {
        switch (proverka(1, 2)) {
        case 1: DeletePack(p, vecP, graph); break;
        case 2: EditPackPipe(p, vecP, graph); break;
        }
        break;
    }
    case 2: {
        switch (proverka(1, 2)) {
        case 1: DeletePack(k, vecK, graph); break;
        case 2: EditPackKS(k, vecK); break;
        }
        break;
    }
    }
}

void LoadFromFile(unordered_map<int, Pipe>& p, unordered_map<int, KS>& k) {
    
    cout << "Enter File name" << endl;
    string Fname = InputString();
    clog << "Load from file: " << Fname << endl;
    fstream file(Fname);
    if (!file.is_open()) {
        clog << "File wasn't open" << endl;
        cout << "Wrong name of file" << endl;
        return;
    }
    int countP, countKS;
    file >> countP;
    file >> countKS;
    if (countP > 0) 
        p = File2Map<Pipe>(countP, file);
     
    if (countKS>0) 
        k= File2Map<KS>(countKS, file);
    if (!file)
    {
        cout << "Everything lost!!!" << endl;
        p = {};
        k = {};
    }
}
void SaveToFile(const unordered_map<int, Pipe>& p, const  unordered_map<int, KS>& k) {
    
    cout << "Enter File name" << endl;
    string Fname= InputString();
    fstream f(Fname);
    //clog << "Saving to file: " << Fname << endl;
    //f.seekg(0);
    f << p.size() << '\n';
    f << k.size()<< '\n';
    f << p;
    f << k;
    f.close();
}


void ConnectStations(GasTransportGraph& graph, unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& stations) {
    int from, to;
    double diameter;

    cout << "Доступные КС:\n";
    for (const auto& [id, station] : stations) {
        cout << "ID: " << id << ", Название: " << station.getName() << endl;
    }

    cout << "Введите ID станции отправления: ";
    from = proverka(stations);
    cout << "Введите ID станции назначения: ";
    to = proverka(stations);

    cout << "Введите диаметр трубы для соединения (500, 700, 1000, 1400): ";
    diameter = proverka(500, 1400);

    if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        cout << "Ошибка: недопустимый диаметр трубы!" << endl;
        return;
    }

    for (auto& [id, pipe] : pipes) {
        if (pipe.getDiam() == diameter && pipe.getisAvailable() && !pipe.getFix()) {
            pipe.markAsUsed();
            pipe.calculateCapacity();
            graph.addEdge(from, to, id, pipe.getCapacity(), pipe.getLen());
            cout << "Станции " << from << " и " << to << " соединены с использованием трубы ID " << id << endl;
            return;
        }
    }

    cout << "Создаем новую трубу...\n";
    Pipe new_pipe = PipeToMap(pipes);

    if (new_pipe.getDiam() == diameter && !new_pipe.getFix()) {
        int pipe_id = new_pipe.getID(); 
        pipes[pipe_id].markAsUsed();
        new_pipe.calculateCapacity();
        graph.addEdge(from, to, pipe_id, new_pipe.getCapacity(), new_pipe.getLen());
        cout << "Станции " << from << " и " << to << " соединены новой трубой ID " << pipe_id << endl;
    }
    else {
        cout << "Who are you trying to fool?" << endl;
    }
}
void DisconnectStations(GasTransportGraph& graph, unordered_map<int, Pipe>& pipes) {
    int pipeId;
    cout << "Введите ID трубы для отключения: ";
    pipeId = proverka(pipes);

    if (pipes.find(pipeId) == pipes.end()) {
        cout << "Ошибка: трубы с таким ID не существует!" << endl;
        return;
    }

    if (graph.removeEdge(pipeId)) {
        pipes[pipeId].setisAvailable(true);
        cout << "Труба ID " << pipeId << " успешно отключена." << endl;
    }
    else {
        cout << "Ошибка: труба с ID " << pipeId << " не была найдена в соединениях." << endl;
    }
}

void DisplayGraph(const GasTransportGraph& graph, const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& stations) {
    const auto& adjacencyList = graph.getsmejn();

    cout << "Текущая структура газотранспортной сети:" << endl;

    for (const auto& [stationId, edges] : adjacencyList) {
        // Вывод информации о станции
        if (stations.find(stationId) != stations.end()) {
            const KS& station = stations.at(stationId);
            cout << "KS ID: " << stationId;
        }

        // Вывод информации о трубах, подключенных к станции
        bool fl = 0;
        for (const auto& edge : edges) {
            if (pipes.find(edge.pipe_id) != pipes.end()) {
                const Pipe& pipe = pipes.at(edge.pipe_id);
                cout << " -> " << edge.to << " with pipe: " << edge.pipe_id << "(d:" << pipe.getDiam() << ")" << endl;
                fl = 1;
            }
        }
        if (!fl) { cout << "- stock" << endl; }

        cout << endl;
    }
}
int Menu()
{
    cout << "\n1. Add Pipe to map\n2. Add KS to map\n3. Change fixing status\n4. Change number of working\
KS\n5. Write to file\n6. Read from file\n7. Read data\n8. Choose some pipes or kss(Create vec)\n9. Delete vector\n10. Package edit\n\
11. Filter Pipes(Make vec)\n12. Filter Kss(Make vec)\n13 Read vector\n14. Connect kss \n15. Disconnect kss \n16. Topological sort \n\
17. Diplay graph \n18. maxFlow\n19. ShortestWay\n20. Import graph \n21. Export graph \n0. Exit" << endl;
    return proverka(0, 21);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    /*redirect_output_wrapper clog_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        clog_out.redirect(logfile);*/

    GasTransportGraph graph;
    vector<int> network;
    vector<int> vecPipe, vecKS;
    unordered_map<int, Pipe> pipeMap;
    unordered_map<int, KS> ksMap;
    //int choice;
    bool fl = 1;
    while (fl) {
        //clog << "Entered number in menu: ";
        switch (Menu()) {
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
            Pack(vecPipe, vecKS, pipeMap, ksMap, graph); break;
        case 11:
            vecPipe = FindForParam(pipeMap, vecPipe);
            break;
        case 12:
            vecKS = FindForParam(ksMap, vecPipe); break;
        case 13:
            {
            cout << "1. Cout vector of Pipes\n2. Cout vector of Kss" << endl;
                for (auto a : proverka(1, 2)==1?vecPipe: vecKS) 
                    cout << a << ", ";
                cout << endl;
                break;
            }
        case 14: 
        { ConnectStations(graph, pipeMap, ksMap); break; }
        case 15: {
            DisconnectStations(graph, pipeMap); break;
        }
        case 16: {
            if (graph.hasCycle()) {
                cout << "Cicle!" << endl;
                break;
            }
            auto sorted = graph.topologicalSort();
            for (int id : sorted) {
                cout << id << " ";
            } break;
        }
        case 17: {
            DisplayGraph(graph, pipeMap, ksMap);
            break;
        }
        case 18: {
            int st, f;
            cout << "Enter strt and finish: ";
            cin >> st;
            cin >> f;
            cout << graph.maxFlow(st,f, pipeMap);
            break;
        }
        case 19: {
            int st, f;
            cout << "Enter start and finish: ";
            cin >> st;
            cin >> f;
            vector<int> path = graph.shortestPath(st, f, pipeMap);
            for (auto a : path) {
                cout << a << " ";
            }
            cout << endl;
            break;
        }
        case 20: {
            cout << "Enter File name" << endl;
            string f = InputString();
            graph.LoadFromFile(f, pipeMap, ksMap);
            break;
        }
        case 21: {
            cout << "Enter File name" << endl;
            string f = InputString();
            graph.SaveToFile(f, pipeMap, ksMap);
            break;
        }
        case 0:
            fl = 0; break;
        default:
            cout << "Enter number from menu" << endl;
        }
    }
}

