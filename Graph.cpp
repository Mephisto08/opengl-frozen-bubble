#include "Graph.h"

Graph::Graph() = default;

Node* Graph::addNode(const string& name) {
    auto res = nodes.insert(make_pair(name, Node(name)));
    if (!res.second) {
        throw invalid_argument("Cannot add node: Name '"+name+"' already exists!");
    }
    return &(res.first->second);
}

void Graph::removeNode(const string& name) {
    auto res = nodes.erase(name);
    if (!res) {
        throw invalid_argument("Cannot remove node: Name '"+name+"' wasn't found!");
    }
    clearEdges(name);
}

Node* Graph::getNode(const string &name) {
    auto res = nodes.find(name);
    if (res == nodes.end()) {
        return nullptr;
    }
    return &(res->second);
}

void Graph::addEdge(const string &nameA, const string &nameB) {
    if(!getNode(nameA)) {
        throw invalid_argument("Cannot add edge: Name '"+nameA+"' wasn't found!");
    } else if(!getNode(nameB)) {
        throw invalid_argument("Cannot add edge: Name '"+nameB+"' wasn't found!");
    }
    auto res = edges.insert(make_pair(min(nameA, nameB), max(nameA, nameB)));
    if (!res.second) {
        throw invalid_argument("Cannot add edge: Edge between '"+nameA+"' and '"+nameB+"' already exists!");
    }
}

void Graph::clearEdges(const string &name) {
    set<pair<string, string>> newEdges;
    for(const pair<string, string>& edge : edges) {
        if (edge.first != name && edge.second != name) {
            newEdges.insert(edge);
        }
    }
    edges = newEdges;
}

bool Graph::checkEdge(const string &nameA, const string &nameB) {
    auto res = edges.find(make_pair(min(nameA, nameB), max(nameA, nameB)));
    return res != edges.end();
}

set<string> Graph::getEdges(const string &name) {
    set<string> foundEdges;
    for(const pair<string, string>& edge : edges) {
        if (edge.first == name) {
            foundEdges.insert(edge.second);
        } else if (edge.second == name) {
            foundEdges.insert(edge.first);
        }
    }
    return foundEdges;
}

void Graph::print() {
    cout << "graph G {" << endl;
    for(const pair<string, Node> node : nodes) {
        cout << "  " << node.first << ";" << endl;
    }
    for(const pair<string, string>& edge : edges) {
        cout << "  " << edge.first << "--" << edge.second << ";" << endl;
    }
    cout << "}" << endl;
}
