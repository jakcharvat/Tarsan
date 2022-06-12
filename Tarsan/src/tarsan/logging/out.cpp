//
//  out.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 10.06.2022.
//

#include "out.hpp"


std::ofstream & out () {
    static std::ofstream out ("console.log");
    return out;
}
