#include "Level.h"

Level::Level(string n, Graph g): name(move(n)), graph(move(g)) {}

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