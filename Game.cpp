#include "Game.h"

Game::Game() {
    cout << "Preparing levels..." << endl;
    importLevels();
}

void Game::start() {
    cout << "Starting new game..." << endl;
    for(const Level& level : levels) {
        playLevel(level);
    }
}

void Game::playLevel(Level l) {
    cout << "Loading level "+l.getName()+"..." << endl;
    l.print();
    // Do something...
}

void Game::importLevels() {
    for (const string& levelName : LEVEL_ORDER) {
        string filename = LEVEL_PATH + "/" + levelName + ".txt";
        Graph graph = Graph(levelName);
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                line.erase(remove(line.begin(), line.end(), ' '), line.end()); // Remove all spaces
                if (line.back() == ';') {
                    line.pop_back();

                    // Checks if they are nodes or edges and adds them to Graph
                    if (line.find("--") == string::npos) {
                        // Node
                        graph.addNode(line);
                    } else {
                        // Edge
                        string start = line.substr(0, line.find("--"));
                        string end = line.substr(line.find("--") + 2);
                        graph.addEdge(start, end);
                    }
                }
            }
            file.close();
        } else {
            throw invalid_argument("Cannot import level: Level '"+levelName+"' wasn't found!");
        }
        levels.emplace_back(levelName, graph);
    }
}

