//
//  coord.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <climits>
#include <functional>


///
/// A structure representing a 2D coordinate
///
struct Coord {
    ///
    /// The x position
    ///
    int x;

    ///
    /// The y position
    ///
    int y;

    /// Create a coordinate
    /// @param x the x coordinate
    /// @param y the y coordinate
    Coord(int x, int y);

    /// Compare two coordinates for equality
    /// @param other the other coordinate
    /// @returns true if the two coordinates are equal
    bool operator == (const Coord & other) const;

    /// Compare two coordinates for inequality
    /// @param other the other coordinate
    /// @returns true if the two coordinates are not equal
    bool operator != (const Coord & other) const;

    /// Add two coords together
    /// @param other the other coordinate to add
    /// @returns the sum of the two vectors
    Coord operator + (const Coord & other) const;

    /// Multiply by scalar
    /// @param scalar the scalar to multiply by
    /// @returns the product of the vector with the scalar
    Coord operator * (int scalar) const;
};


namespace std {
template<>
struct hash<Coord> {
    /// Hash a coordinate
    ///
    /// Since my coordinates are ints, on most systems this hasing function will work, as it will simply map the two coordinates behind each other in an integer type that is at least twice larger than int. This requires a system where `size_t` truly is at least twice larger than int
    size_t operator () (const Coord & coord) const {
        const int bits = CHAR_BIT * sizeof(int);
        return static_cast<size_t>(coord.x) << bits | coord.y;
    }
};
}
