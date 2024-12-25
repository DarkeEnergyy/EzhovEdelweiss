#pragma once
#include <cmath>
#include <limits>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include "Pipe.h"
using namespace std;

struct Edge {
    int pipe_id; 
    int to;
    int from;
    double capacity;
    double flow;
    double weight;
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

    // Расчет производительности трубы
    double calculateFlow(double diameter, double length, int fix) {
        if (fix || length <= 0) return 0; // Если труба в ремонте, производительность = 0
        return CORRECTION_FACTOR * sqrt(pow(diameter, 5) / length);
    }

    // Расчет веса ребра
    double calculateWeight(double length, int fix) {
        if (fix) return INF; // Если труба в ремонте, вес = бесконечность
        return length;
    }

    // Расчет максимального потока в сети с использованием алгоритма Эдмондса-Карпа
    double maxFlow(int source, int sink) {
        unordered_map<int, vector<Edge>> residual = smejn;
        double maxFlow = 0;

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
    vector<int> shortestPath(int start, int end) {
        unordered_map<int, double> distances;
        unordered_map<int, int> previous;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

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