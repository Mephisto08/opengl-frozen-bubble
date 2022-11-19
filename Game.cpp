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
    l.insertNode('A', 5, Color());
    // Do something...
}

void Game::importLevels() {
    for (const string& levelName : LEVEL_ORDER) {
        string filename = LEVEL_PATH + "/" + levelName + ".txt";
        Level level = Level(levelName);
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            bool firstLine = true;


            while (getline(file, line)) {
                line.erase(remove(line.begin(), line.end(), ' '), line.end()); // Remove all spaces
                if (line.back() == ';') {
                    line.pop_back();

                    // Wird nur bei erster Zeile aufgerufen.
                    // Splittet String bei , und fügt einzelne Elemente in vector
                    if (firstLine){
                        vector<string> levelColors;
                        firstLine = false;
                        stringstream lineS = stringstream(line);
                        string segment;

                        while(getline(lineS, segment, ','))
                        {
                            levelColors.push_back(segment);
                        }
                        level.setColors(levelColors);
                    }
                    // Nodes
                    else{
                        string nodePosition = line.substr(0, line.find('_'));
                        char nodeRow = nodePosition[0];
                        int nodeCol = nodePosition[1] - 48;

                        string nodeColor = line.substr(line.find('_') + 1);
                        level.insertNode(nodeRow, nodeCol);
                    }
                }
            }
            file.close();
        } else {
            throw invalid_argument("Cannot import level: Level '"+levelName+"' wasn't found!");
        }
    }
}

