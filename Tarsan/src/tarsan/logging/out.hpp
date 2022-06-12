//
//  log.hpp
//  Quizzy
//
//  Created by Jakub Charvát on 05.06.2022.
//

#pragma once

#include <fstream>


/// Get a stream to log to
///
/// Since I can't debug log to the console due to using it for the main window, this logs to a file.
///
/// A single stream is open for the entire lifetime of the app, as a static member of this function. It is cleared on launch.
///
/// @returns A reference to the managed stream
std::ofstream & out ();
