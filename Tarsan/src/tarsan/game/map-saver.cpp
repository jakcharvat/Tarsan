//
//  map-saver.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map-saver.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../logging/menu-error.hpp"



// Taken from
// https://stackoverflow.com/a/17223443/9020201
std::string currentDateAndTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    std::string format = std::string { "%Y-%m-%d-" } + std::to_string(now.time_since_epoch().count());
    ss << std::put_time(std::localtime(&in_time_t), format.c_str());
    return ss.str();
}


void
MapSaver::save(const Savable & savable) {
    std::string filename = "Savegame-" + currentDateAndTime() + ".tarsan";
    std::ofstream file(filename);
    savable.save(file);

    MenuError error ("Couldn't write to file" + filename);
    if (!file) throw error;
    file.close();
    if (!file) throw error;
}
