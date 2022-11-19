#ifndef HMI_GRAPH_H
#define HMI_GRAPH_H
#include <iostream>
#include <map>
#include <set>
#include "Node.h"
using namespace std;

class Graph {
private:
    string lvlName;
    map<string, Node> nodes;
    set<pair<string, string>> edges;
    bool checkPathNode(const string& a, const string& b, set<string>& visited);
public:
    Graph();
    explicit Graph(string lvlName);

    void clear();
    void print();
    Node* getNode(const string& n);
    Node* addNode(const string& n);
    void removeNode(const string& n);
    void clearEdges(const string& n);
    set<string> getNeighbors(const string& n);
    void addEdge(const string& a, const string& b);
    bool checkEdge(const string& a, const string& b);
    bool checkPath(const string& a, const string& b);
};

#endif //HMI_GRAPH_H