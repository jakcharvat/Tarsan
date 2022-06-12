//
//  direction.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "coord.hpp"


///
/// A direction on the canvas
///
enum class Direction {
    LEFT, RIGHT, UP, DOWN
};


/// Get the step coordinate needed to move one block in the given direction
/// @param direction the direction in which to step
/// @returns a unit vector directed along `direction`
Coord directionStep(Direction direction);

