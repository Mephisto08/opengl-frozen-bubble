#ifndef HMI_GRAPH_H
#define HMI_GRAPH_H
#include <iostream>
#include <map>
#include <set>
#include "Node.h"
using namespace std;

class Graph {
private:
    map<string, Node> nodes;
    set<pair<string, string>> edges;
public:
    Graph();
    void print();
    Node* getNode(const string& n);
    Node* addNode(const string& n);
    void removeNode(const string& n);
    void clearEdges(const string& n);
    set<string> getEdges(const string& n);
    void addEdge(const string& a, const string& b);
    bool checkEdge(const string& a, const string& b);
};

#endif //HMI_GRAPH_H