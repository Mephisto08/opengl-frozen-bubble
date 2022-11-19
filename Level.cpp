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

void Level::insertNode(char row, int column) {
    string name = "";
    graph.addNode(name);
}

void Level::setColors(const vector<string> &colors) {
    Level::colors = colors;
}


