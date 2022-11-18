//
// Created by Niklas Werner on 17.11.2022.
//

#ifndef OPENGL_FROZEN_BUBBLE_BOARD_H
#include "iostream"
#include "Bubble.h"
using namespace std;
#define OPENGL_FROZEN_BUBBLE_BOARD_H

const int WIDTH = 8;
const int HEIGHT = 8;

class Board {
private:
    int currentHeight = HEIGHT;
    Bubble board [HEIGHT][WIDTH];

    void updateBoardNeighbors(int row, int column, int depth);

public:
    Board();
    void generate();
    void print();

    int getCurrentHeight() const;
    void setCurrentHeight(int currentHeight);
    bool isGameOver();
    void setBubble(int row, int column, Bubble b);
};

#endif //OPENGL_FROZEN_BUBBLE_BOARD_H
