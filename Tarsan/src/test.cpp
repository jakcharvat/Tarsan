//
//  test.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 05.06.2022.
//

#ifdef __TEST__

#include <iostream>

#include "tests/test-responder.hpp"
#include "tests/test-nested-responder.hpp"


int main () {
    testResponder();
    testNestedResponder();
    std::cout << "All tests passed :)" << std::endl;
    return 0;
}


#endif
