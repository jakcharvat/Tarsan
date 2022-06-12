//
//  coord.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once


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
};
