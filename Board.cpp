#include "Board.h"

Board::Board() {
    generate();
}

void Board::generate() {
    for (unsigned int i = 0; i < currentHeight-1; ++i){
        for (unsigned int j = 0; j < WIDTH-1; ++j) {
            board[i][j].setRandomColor();
        }
        if (i % 2 == 0){
            board[i][HEIGHT-1].setRandomColor();
        }
    }
}

void Board::print() {
    for (unsigned int i = 0; i < currentHeight; ++i){
        if (i % 2 != 0){
            cout << " ";
        }
        for (unsigned int j = 0; j < WIDTH; ++j) {
            if (board[i][j].isVisible()) {
                cout << board[i][j].getColor() << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool Board::isGameOver() {
    for (unsigned int i = 0; i < WIDTH; ++i) {
        if (board[currentHeight-1][i].isVisible()) {
            return true;
        }
    }
    return false;
}

int Board::getCurrentHeight() const {
    return currentHeight;
}

void Board::setCurrentHeight(int currentHeight) {
    Board::currentHeight = currentHeight;
}

void Board::setBubble(int row, int column, Bubble b) {
    board[row][column] = b;
    updateBoardNeighbors(row, column, 0);
}

void Board::updateBoardNeighbors(int row, int column, int depth) {
    /*
     * vector route = {...}
    if(NEIGHBOR_COLOR == board[row][column].getColor()) {
        if(depth > 2) {
            // FINISH
        } else {
            updateBoardNeighbors(NEIGHBOR_ROW, NEIGHBOR_COLUMN, depth+1);
        }
    }
     */
}
