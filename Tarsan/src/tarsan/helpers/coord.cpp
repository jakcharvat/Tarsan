//
//  coord.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "coord.hpp"


Coord::Coord(int x, int y):
x(x), y(y) { }


bool
Coord::operator==(const Coord &other) const {
    return x == other.x && y == other.y;
}


bool
Coord::operator!=(const Coord &other) const {
    return x != other.x || y != other.y;
}


Coord
Coord::operator+(const Coord &other) const {
    return {
        x + other.x,
        y + other.y,
    };
}


Coord
Coord::operator*(int scalar) const {
    return {
        x * scalar,
        y * scalar,
    };
}
