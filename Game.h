#ifndef HMI_GAME_H
#define HMI_GAME_H

#include "Graph.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Game {
private:
    string levels [2] = {"1", "2"};
    string path =  R"(C:\Users\werne\OneDrive\_Studium\_Master\3_Semester\ES_HMI\Praktika\opengl-frozen-bubble\level\)";
    map<string, Graph> graphes;

public:
    Game();
    void readInLevel();

};


#endif //HMI_GAME_H
