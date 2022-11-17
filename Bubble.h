//
// Created by Niklas Werner on 17.11.2022.
//

#ifndef OPENGL_FROZEN_BUBBLE_BUBBLE_H
#include "iostream"
using namespace std;
#define OPENGL_FROZEN_BUBBLE_BUBBLE_H

const int RADIUS = 1;

class Bubble {
private:
    int color = 0;

public:
    Bubble();
    Bubble(int color);

    bool isVisible();

    int getColor() const;
    void setColor(int color);
    void setRandomColor();
};

#endif //OPENGL_FROZEN_BUBBLE_BUBBLE_H
