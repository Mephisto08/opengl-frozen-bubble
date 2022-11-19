#include "Game.h"


Game::Game() {

}

void Game::readInLevel() {
    for (string lvl : levels) {
        string filename = path + lvl + ".txt";
        Graph tmpGraph = Graph(lvl);
        ifstream input(filename);

        if (input.is_open()) {
            string line;
            while (std::getline(input, line)) {
                if (line == "graph G {" || line == "}") {
                    continue;
                }
                line.pop_back();

                // Prüft, ob es sich um Nodes oder Edges handelt und fügt diese zu Graph hinzu
                if (line.find("--") == std::string::npos) {
                    // Nodes

                    // ab 2, da vorher 2 Leerzeichen sind
                    line = line.substr(2);
                    tmpGraph.addNode(line);
                } else {
                    // Edges

                    // ab 2, da vorher 2 Leerzeichen sind
                    string before = line.substr(2, line.find("--") - 2);
                    string after = line.substr(line.find("--") + 2);

                    tmpGraph.addEdge(before, after);
                }

            }
            input.close();
        }
        auto res = graphes.insert(make_pair(lvl, tmpGraph));
        if (!res.second) {
            throw invalid_argument("Cannot add graph: Graph "+ lvl + " already exists!");
        }
    }
}

