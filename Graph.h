#pragma once
#include <cmath>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
#include "Pipe.h"
#include "KS.h"
using namespace std;

struct Edge {
    int pipe_id; 
    int to;
    int from;
    double capacity;
    double flow;
    double weight;
public:
    double getCapacity()  { return capacity; }
    void setCapacity(double new_capacity) { capacity = new_capacity; }
};

constexpr double INF = numeric_limits<double>::infinity();
constexpr double CORRECTION_FACTOR = 1.0; // Поправочный коэффициент




class GasTransportGraph {
private:
    unordered_map<int, vector<Edge>> smejn;
    unordered_set<int> all_nodes;

public:
    void addEdge(int from, int to, int pipe_id, double capacity, double weight) {
        smejn[from].push_back({ pipe_id, to, from, capacity, 0, weight});
        all_nodes.insert(from);
        all_nodes.insert(to);
    }

    const unordered_map<int, vector<Edge>>& getsmejn() const {
        return smejn;
    }

    //unordered_map<int, vector<Edge>>& getsmejn() {
    //    return smejn;
    //}

    bool removeEdge(int pipeId) {
        for (auto& [stationId, edges] : smejn) {
            auto it = std::remove_if(edges.begin(), edges.end(),
                [pipeId](const Edge& edge) {
                    return edge.pipe_id == pipeId;
                });

            if (it != edges.end()) {
                edges.erase(it, edges.end());
                return true;
            }
        }
        return false;
    }

    int countEdges() const {
        int edge_count = 0;
        for (const auto& [node, edges] : smejn) {
            edge_count += edges.size();
        }
        return edge_count;
    }

    void SaveToFile(const string& filename, const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& ks) {
        fstream file(filename, ios::out);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for saving." << endl;
            return;
        }

        // Сохраняем количество труб и КС
        file << pipes.size() << '\n' << ks.size() << '\n';

        // Сохраняем трубы
        for (const auto& [id, pipe] : pipes) {
            file << pipe;
        }

        // Сохраняем КС
        for (const auto& [id, station] : ks) {
            file << station;
        }

        // Сохраняем рёбра графа
        file << all_nodes.size() << '\n';
        for (const auto& [from, edges] : smejn) {
            for (const auto& edge : edges) {
                file << edge.from << " " << edge.to << " " << edge.pipe_id << " " << edge.capacity << " " << edge.weight << '\n';
            }
        }

        file.close();
        cout << "Graph successfully saved to " << filename << "." << endl;
    }

    void LoadFromFile(const string& filename, unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& ks) {
        fstream file(filename, ios::in);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for loading." << endl;
            return;
        }

        // Загружаем количество труб и КС
        int pipeCount, ksCount;
        file >> pipeCount >> ksCount;
        file.ignore(); // Пропускаем символ новой строки
        // Загружаем трубы
        pipes.clear();
        for (int i = 0; i < pipeCount; ++i) {
            Pipe pipe;
            file >> pipe;
            pipes[pipe.getID()] = pipe;
        }

        // Загружаем КС
        ks.clear();
        for (int i = 0; i < ksCount; ++i) {
            KS station;
            file >> station;
            ks[station.getID()] = station;
        }

        // Загружаем рёбра графа
        smejn.clear();
        int edgeCount;
        file >> edgeCount;
        file.ignore(); // Пропускаем символ новой строки

        for (int i = 0; i < edgeCount; ++i) {
            int from, to, pipe_id;
            double capacity, weight;
            file >> from >> to >> pipe_id >> capacity >> weight;
            addEdge(from, to, pipe_id, capacity, weight);
        }

        file.close();
        cout << "Graph successfully loaded from " << filename << "." << endl;
    }

    vector<int> topologicalSort() {
        unordered_map<int, int> in_degree;
        for (const auto& [from, edges] : smejn) {
            for (const auto& edge : edges) {
                in_degree[edge.to]++;
            }
        }

        queue<int> q;
        for (const auto& [node, edges] : smejn) {
            if (in_degree[node] == 0) {
                q.push(node);
            }
        }

        vector<int> result;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);

            for (const auto& edge : smejn[current]) {
                in_degree[edge.to]--;
                if (in_degree[edge.to] == 0) {
                    q.push(edge.to);
                }
            }
        }
        return result;
    }
    bool hasCycleUtil(int node, unordered_map<int, bool>& visited, unordered_map<int, bool>& recStack) {
        visited[node] = true;
        recStack[node] = true;

        for (const auto& edge : smejn[node]) {
            int neighbor = edge.to;

            if (!visited[neighbor] && hasCycleUtil(neighbor, visited, recStack)) {
                return true;
            }
            if (recStack[neighbor]) {
                return true;
            }
        }

        recStack[node] = false; 
        return false;
    }

    bool hasCycle() {
        unordered_map<int, bool> visited;
        unordered_map<int, bool> recStack;

        for (const auto& [node, _] : smejn) {
            if (!visited[node] && hasCycleUtil(node, visited, recStack)) {
                return true;
            }
        }

        return false;
    }

    // Расчет максимального потока в сети с использованием алгоритма Эдмондса-Карпа
    double maxFlow(int source, int sink, unordered_map<int, Pipe> pipes) {
        unordered_map<int, vector<Edge>> residual = smejn;
        double maxFlow = 0;

        // Обновление capacity всех ребер в residual в соответствии с пропускной способностью труб
        for (auto& [from, edges] : residual) {
            for (auto& edge : edges) {
                if (pipes.contains(edge.pipe_id)) {
                    Pipe& pipe = pipes[edge.pipe_id];
                    if (pipe.getFix()) {
                        edge.capacity = 0;
                    }
                    else {
                        pipe.calculateCapacity();
                        edge.capacity = pipe.getCapacity();
                    }
                }
            }
        }

        while (true) {
            // Поиск пути с положительной пропускной способностью (алгоритм BFS)
            unordered_map<int, int> parent;
            queue<int> q;
            q.push(source);
            parent[source] = -1;

            while (!q.empty() && !parent.count(sink)) {
                int current = q.front();
                q.pop();

                for (auto& edge : residual[current]) {
                    if (!parent.count(edge.to) && edge.capacity > edge.flow) {
                        parent[edge.to] = current;
                        q.push(edge.to);
                    }
                }
            }

            if (!parent.count(sink)) break; // Нет пути до стока

            // Найти минимальную пропускную способность на пути
            double pathFlow = INF;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (auto& edge : residual[u]) {
                    if (edge.to == v) {
                        pathFlow = min(pathFlow, edge.capacity - edge.flow);
                        break;
                    }
                }
            }

            // Обновить резидуальную сеть
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (auto& edge : residual[u]) {
                    if (edge.to == v) {
                        edge.flow += pathFlow;
                        break;
                    }
                }
                for (auto& edge : residual[v]) {
                    if (edge.to == u) {
                        edge.flow -= pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }

    // Расчет кратчайшего пути между двумя станциями с использованием алгоритма Дейкстры
    vector<int> shortestPath(int start, int end, unordered_map<int, Pipe> pipes) {
        unordered_map<int, double> distances;
        unordered_map<int, int> previous;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

        for (auto& [from, edges] : smejn) {
            for (auto& edge : edges) {
                if (pipes.contains(edge.pipe_id)) {
                    Pipe& pipe = pipes[edge.pipe_id];
                    edge.weight = pipe.getFix() ? numeric_limits<double>::infinity() : pipe.getLen();
                }
            }
        }

        // Инициализация расстояний и предыдущих узлов
        for (int node : all_nodes) {
            distances[node] = numeric_limits<double>::infinity();
            previous[node] = -1;
        }
        distances[start] = 0;

        // Помещаем начальный узел в очередь
        pq.push({ 0.0, start });

        while (!pq.empty()) {
            pair<double, int> current = pq.top();
            pq.pop();

            double currentDistance = current.first;
            int currentNode = current.second;

            // Если это расстояние неактуально, пропускаем
            if (currentDistance > distances[currentNode]) {
                continue;
            }

            // Обходим соседей
            for (const auto& edge : smejn[currentNode]) {
                double newDistance = currentDistance + edge.weight * CORRECTION_FACTOR;

                if (newDistance < distances[edge.to]) {
                    distances[edge.to] = newDistance;
                    previous[edge.to] = currentNode;
                    pq.push({ newDistance, edge.to });
                }
            }
        }

        cout << distances[end] << endl;
        // Построение пути
        vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        // Проверяем, существует ли путь
        if (path.size() == 1 && path[0] != start) {
            return {}; // Путь не найден
        }

        return path;
    }
};