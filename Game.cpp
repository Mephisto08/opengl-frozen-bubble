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

                    if (firstLine){
                        map<string, Color> levelColors;
                        firstLine = false;
                        stringstream lineS = stringstream(line);
                        string segment;

                        while(getline(lineS, segment, ','))
                        {
                            levelColors.insert(make_pair(segment, stringToColor(segment)));
                        }

                        level.setColors(levelColors);
                    }

                    // Nodes
                    else{
                        string nodePosition = line.substr(0, line.find('_'));
                        char nodeRow = nodePosition[0];
                        int nodeColumn = nodePosition[1] - 48;

                        string nodeColor = line.substr(line.find('_') + 1);

                        level.insertNode(nodeRow, nodeColumn, stringToColor(nodeColor));

                    }
                }
            }
            file.close();
        } else {
            throw invalid_argument("Cannot import level: Level '"+levelName+"' wasn't found!");
        }
    }
}

Color Game::stringToColor(const string& color) {
            if (color == "ORANGE") {
                return {255, 0, 0};
            }
            if (color == "BLUE"){
                return {0, 0, 255};
            }
            if (color == "GREEN"){
                return {0, 255, 0};
            }
            if (color == "PURPLE"){
                return {166, 32, 240};
            }
            if (color == "BLACK"){
                return {0, 0, 0};
            }
            if (color == "YELLOW") {
                return {255, 255, 0};
            }
            return {255,255, 255};
}

