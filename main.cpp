#include "Graphics.h"
using namespace std;

int main() {

    Graphics graphics;



    //game.getCurrentLevel().getGraph().getNode("QUEUE_1");

    //game.shoot('C', 5);
    //game.shoot('A', 3, game.stringToColor("ORANGE"));
    //game.shoot('A', 6, game.stringToColor("ORANGE"));
    //game.shoot('I', 3, game.stringToColor("ORANGE"));
    //game.shoot('J', 3, game.stringToColor("ORANGE"));
    //game.shoot('K', 3, game.stringToColor("GREEN"));
    //game.shoot('L', 3, game.stringToColor("ORANGE"));

    while (true) {
        //we usually run our own event loop in OpenGL ES2
        graphics.handleXEvents();
        graphics.draw();
    }
}