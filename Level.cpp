#include "Level.h"

Level::Level(string n, Graph g): name(move(n)), graph(move(g)) {}

Level::Level(const string &name) : name(name), graph(name){
}

const string &Level::getName() const {
    return name;
}

void Level::print() {
    graph.print();
}

void Level::insertNode(char row, int column, Color color) {
    string nodeName = to_string(row)+to_string(column);
    graph.addNode(nodeName, color);

    vector<string> possibleNeighbors = {
            to_string(row-1)+to_string(column),
            to_string(row-1)+to_string(column+1),
            to_string(row)+to_string(column+1),
            to_string(row+1)+to_string(column+1),
            to_string(row+1)+to_string(column),
            to_string(row)+to_string(column-1)
    };
    for(const string& pn : possibleNeighbors) {
        if (graph.getNode(pn)) {
            graph.addEdge(nodeName, pn);
        }
    }
}

void Level::setColors(const vector<string> &colors) {
    Level::colors = colors;
}
