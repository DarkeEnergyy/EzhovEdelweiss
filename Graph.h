#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int pipe_id; 
    int to;      
};

class GasTransportGraph {
private:
    unordered_map<int, vector<Edge>> smejn;

public:
    void addEdge(int from, int to, int pipe_id) {
        smejn[from].push_back({ pipe_id, to });
    }

    const unordered_map<int, vector<Edge>>& getsmejn() const {
        return smejn;
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

        if (result.size() != smejn.size()) {
            throw runtime_error("Граф содержит цикл, топологическая сортировка невозможна.");
        }

        return result;
    }
};