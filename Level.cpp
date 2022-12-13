#include "Level.h"

Level::Level(): name("NULL"), graph(Graph("NULL")) {}

Level::Level(string n, Graph g): name(move(n)), graph(move(g)) {
    graph.addNode("ROOT");
}

Level::Level(const string &name) : name(name), graph(name){
    graph.addNode("ROOT");
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
    if(row == 'A') {
        graph.addEdge(nodeName, "ROOT");
    }

    vector<string> possibleNeighbors = {
            static_cast<char>(row)+to_string(column-1),
            static_cast<char>(row)+to_string(column+1)
    };

    if((row-'A') % 2 == 0) {
        possibleNeighbors.push_back(static_cast<char>(row-1)+to_string(column-1));
        possibleNeighbors.push_back(static_cast<char>(row-1)+to_string(column));
        possibleNeighbors.push_back(static_cast<char>(row+1)+to_string(column-1));
        possibleNeighbors.push_back(static_cast<char>(row+1)+to_string(column));

    } else {
        possibleNeighbors.push_back(static_cast<char>(row-1)+to_string(column));
        possibleNeighbors.push_back(static_cast<char>(row-1)+to_string(column+1));
        possibleNeighbors.push_back(static_cast<char>(row+1)+to_string(column));
        possibleNeighbors.push_back(static_cast<char>(row+1)+to_string(column+1));

    }

    for(const string& pn : possibleNeighbors) {
        if (graph.getNode(pn)) {
            graph.addEdge(nodeName, pn);
        }
    }
}

void Level::setColors(const map<string, Color> &colors) {
    Level::colors = colors;
}

bool Level::isWon() const {
    // Only root left --> Game is won
    return graph.getAllNodes().size() == 1;
}

bool Level::isGameOver() const {
    for(const string& n : graph.getAllNodes()) {
        if (n[0] >= deathZone && n != "ROOT") {
            return true;
        }
    }
    return false;
}

void Level::expandDeathZone() {
    if(deathZone > 'A') {
        deathZone -= 1;
    }
}

void Level::checkLineNode(const string &n, Color color, set<string> &found) {
    for(const string& neighbor : graph.getNeighbors(n)) {
        if(graph.getNode(neighbor)->getColor() == color) {
            if(found.insert(neighbor).second) {
                // If neighbor wasn't already found
                checkLineNode(neighbor, color, found);
            }
        }
    }
}

void Level::checkLine(const string &node) {
    if(!graph.getNode(node)) {
        throw invalid_argument("Cannot check line: Node '"+node+"' wasn't found!");
    }
    set<string> found = {node};
    const Color color = graph.getNode(node)->getColor();
    checkLineNode(node, color, found);

    if(found.size() >= LINE_NUM) {
        for(const string& n : found) {
            graph.removeNode(n);
        }
    }
}

char Level::getDeathZone() const {
    return deathZone;
}

void Level::removeDroppedNodes() {
    for(const string& n : graph.getAllNodes()) {
        if(!graph.checkPath(n, "ROOT")) {
            graph.removeNode(n);
        }
    }
}

const Graph &Level::getGraph() const {
    return graph;
}
