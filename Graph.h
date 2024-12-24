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
    int from;
};

class GasTransportGraph {
private:
    unordered_map<int, vector<Edge>> smejn;

public:
    void addEdge(int from, int to, int pipe_id) {
        smejn[from].push_back({ pipe_id, to, from});
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
};