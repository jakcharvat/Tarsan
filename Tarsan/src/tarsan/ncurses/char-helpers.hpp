//
//  char-helpers.hpp
//  Quizzy
//
//  Created by Jakub Charvát on 10.06.2022.
//

#pragma once


///
/// A simple class to aid in parsing characters and checking for meta chars
///
struct CharHelpers {
public:
    /// Check whether the specified character is valid for use in a text field
    ///
    /// Characters that are considered valid are all ASCII alphanumeric and printable punctuation characters, as well as a space.
    ///
    /// The checks correspond to a disjunction of the character sets allowed by `isalnum` and `ispunct` together with the space (\x20)
    ///
    /// @param c the character to check
    /// @returns whether `c` belongs to the set of allowed character or not
    static bool isTextfieldPrintable (int c);

    /// Check whether the given character is a backspace character
    ///
    /// The set of allowed backspace characters is { \a, \b, ASCII DEL (\x7F), ncurses KEY_BACKSPACE }
    ///
    /// @param c the character to test
    /// @returns whether or not `c` belongs to the set of known backspace characters
    static bool isBackspace (int c);

    /// Check whether the given character is an enter character
    ///
    /// An enter is considered to be either LF (`\n`) or CR (`\r`) or ncurses `KEY_ENTER`, not CRLF ("\n\r"). Sorry windows, really can't be bothered to deal with you right now :(
    ///
    /// @param c the character to test
    /// @returns whether or not `c` belongs to the set of valid enter characters
    static bool isEnter (int c);

    /// Check whether the given character is a space character
    ///
    /// An enter is considered to only ASCII space '\x20'
    ///
    /// @param c the character to test
    /// @returns whether or not `c` is a space character
    static bool isSpace (int c);

    /// Check whether the given character is a forward delete character
    ///
    /// The only allowed forward delete character is ncurses KEY_DL
    ///
    /// @param c the character to test
    /// @returns whether or not `c` belongs to the set of known forward delete characters
    static bool isDelete (int c);

    /// Check whether the given character is the physical escape character
    ///
    /// This needs some sophisticated check, cause apparently the same char code is used for alt and escape. Who on earth thaught that was a good idea? Goddamit. So yeah, thx https://stackoverflow.com/a/16248956/9020201. Good artists copy, great artists steal, right? Right?
    ///
    /// @param c the character to test
    /// @returns whether or not c is the escape key
    static bool isEscape (int c);

    /// Check whther the given character is a build character.
    ///
    /// Build characters are:
    ///     q w e
    ///     a   d
    ///     z x c
    ///
    /// And their uppercase counterparts for destruction
    ///
    /// @param c the character to test
    /// @returns true if `c` is a build character
    static bool isBuild (int c);
};
