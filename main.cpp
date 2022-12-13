#include "Game.h"
#include "Graphics.h"
using namespace std;

int main() {
    Game game;
    Graphics graphics;

    game.start();
    //game.shoot('C', 5, game.stringToColor("BLUE"));
    //game.shoot('A', 3, game.stringToColor("ORANGE"));
    //game.shoot('A', 6, game.stringToColor("ORANGE"));
    //game.shoot('I', 3, game.stringToColor("ORANGE"));
    //game.shoot('J', 3, game.stringToColor("ORANGE"));
    //game.shoot('K', 3, game.stringToColor("GREEN"));
    //game.shoot('L', 3, game.stringToColor("ORANGE"));

    while (true) {
        //we usually run our own event loop in OpenGL ES2
        graphics.handleXEvents();
        graphics.draw(game.getCurrentLevel().getGraph().getNodes());
    }
}