//
// Created by Niklas Werner on 17.11.2022.
//

#include "Bubble.h"

Bubble::Bubble() {}

Bubble::Bubble(int color) : color(color) {}

int Bubble::getColor() const {
    return color;
}

void Bubble::setColor(int color) {
    Bubble::color = color;
}

void Bubble::setRandomColor() {
    int color = rand() % 5;
    this->color = color;
}

bool Bubble::isVisible() {
    return color > 0;
}


