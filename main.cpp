#include <iostream>
#include "Board.h"
#include <ctime>

int main() {
    srand (time(NULL));

    Board b = Board();
    b.print();
    if (b.isGameOver()) {
        cout << "FROZEN!" << endl;
    }
    b.setBubble(6, 7, Bubble(8));
    b.print();
    if (b.isGameOver()) {
        cout << "FROZEN! 2" << endl;
    }
    return 0;
}
