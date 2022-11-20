#include "Game.h"
using namespace std;

int main() {
    Game g;
    g.start();
    //g.shoot('C', 5, g.stringToColor("BLUE"));
    //g.shoot('A', 3, g.stringToColor("ORANGE"));
    //g.shoot('A', 6, g.stringToColor("ORANGE"));
    g.shoot('I', 3, g.stringToColor("ORANGE"));
    g.shoot('J', 3, g.stringToColor("ORANGE"));
    g.shoot('K', 3, g.stringToColor("GREEN"));
    g.shoot('L', 3, g.stringToColor("ORANGE"));

}