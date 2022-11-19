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
    string nodeName = row + to_string(column);
    graph.addNode(nodeName, color);

    vector<string> possibleNeighbors = {
            static_cast<char>(row-1)+to_string(column),
            static_cast<char>(row-1)+to_string(column+1),
            static_cast<char>(row)+to_string(column+1),
            static_cast<char>(row+1)+to_string(column),
            static_cast<char>(row+1)+to_string(column-1),
            static_cast<char>(row)+to_string(column-1)
    };
    for(const string& pn : possibleNeighbors) {
        if (graph.getNode(pn)) {
            graph.addEdge(nodeName, pn);
        }
    }
}

void Level::setColors(const map<string, Color> &colors) {
    Level::colors = colors;
}
