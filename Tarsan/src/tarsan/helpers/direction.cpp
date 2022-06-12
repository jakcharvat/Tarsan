//
//  direction.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "direction.hpp"


Coord directionStep(Direction direction) {
    switch (direction) {
        case Direction::LEFT: return { -1, 0 };
        case Direction::RIGHT: return { 1, 0 };
        case Direction::UP: return { 0, -1 };
        case Direction::DOWN: return { 0, 1 };
    }
}
