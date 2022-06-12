//
//  color.hpp
//  Quizzy
//
//  Created by Jakub Charvát on 05.06.2022.
//

#pragma once

#include <array>

#include <ncurses.h>

#define COLOR_DEFAULT -1


/// A class managing Ncurses colour pairs
///
/// Implemented as a singleton as it best matches the ncurses model of defining colour pair statically for the full ncurses instance
class Color {
private:
    ///
    /// Only using the original reduced terminal colour set, therefore only 8 available foreground and background colours, giving 8^2 = 64 different combinations, reasonable enough to be stored in an uncompressed state vector
    ///
    constexpr static int AVAILABLE_COLORS = 8;

    
    ///
    /// Add one for -1 representing the default colour
    ///
    constexpr static int VALID_COLORS = AVAILABLE_COLORS + 1;

    ///
    /// The total number of colour pairs available to be used in the reduced terminal colour set
    ///
    constexpr static int AVAILABLE_PAIRS = AVAILABLE_COLORS * AVAILABLE_COLORS;

    ///
    /// The total number of assignable colour pairs, adding options for -1 representing the default terminal colour
    ///
    constexpr static int VALID_PAIRS = VALID_COLORS * VALID_COLORS;

    ///
    /// A type for the internal representation and storage of assigned colour pairs
    ///
    using ColorPairs = std::array<short, VALID_PAIRS>;

    ///
    /// The actual uncompressed state vector storing the ncurses pair indices assigned to the different colour pairs
    ///
    ColorPairs _pairs;

    ///
    /// The next index to assign. Cannot be taken from the storage array as it will not be populated linearly
    ///
    short _nextIndex = 1;

    ///
    /// A static instance that all operations are handled on
    ///
    static Color _instance;

    ///
    /// Create an empty colour container, filling all possible pairs with -1, indicating that they are not assigned
    ///
    Color ();

    /// Get the ncurses colour pair index assigned to the provided foreground-background combination
    ///
    /// If such a combination is already registered, then that index is returned, otherwise a new pair is registered for this combination and its index is returned
    ///
    /// @param foreground the foreground colour, as a value between -1 and 7 inclusive
    /// @param background the background colour, as a value between -1 and 7 inclusive
    ///
    /// @returns the index of the colour pair assigned to the provided combination
    short _get (short foreground, short background);

    /// Get the ncurses colour pair attribute assigned to the provided foreground-background combination
    ///
    /// If such a combination is already registered, then that attribute is returned, otherwise a new pair is registered for this combination and its attribute is returned
    ///
    /// @param foreground the foreground colour, as a value between -1 and 7 inclusive
    /// @param background the background colour, as a value between -1 and 7 inclusive
    ///
    /// @returns the attribute of the colour pair assigned to the provided combination
    int _pair (short foreground, short background);

public:
    /// Get the ncurses colour pair index assigned to the provided foreground-background combination
    ///
    /// If such a combination is already registered, then that index is returned, otherwise a new pair is registered for this combination and its index is returned
    ///
    /// @param foreground the foreground colour, as a value between -1 and 7 inclusive
    /// @param background the background colour, as a value between -1 and 7 inclusive
    ///
    /// @returns the index of the colour pair assigned to the provided combination
    static short get (short foreground, short background);

    /// Get the ncurses colour pair attribute assigned to the provided foreground-background combination
    ///
    /// If such a combination is already registered, then that attribute is returned, otherwise a new pair is registered for this combination and its attribute is returned
    ///
    /// @param foreground the foreground colour, as a value between -1 and 7 inclusive
    /// @param background the background colour, as a value between -1 and 7 inclusive
    ///
    /// @returns the attribute of the colour pair assigned to the provided combination
    static int pair (short foreground, short background);
};
