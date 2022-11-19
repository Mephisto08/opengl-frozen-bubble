#ifndef HMI_GAME_H
#define HMI_GAME_H
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "Level.h"
using namespace std;

static const string LEVEL_PATH =  "../level";
static string LEVEL_ORDER[] = {"3"};

class Game {
private:
    vector<Level> levels;

    void importLevels();
    static void playLevel(Level l);
public:
    Game();

    void start();
};


#endif //HMI_GAME_H
