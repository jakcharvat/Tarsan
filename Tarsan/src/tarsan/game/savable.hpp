//
//  savable.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <iostream>

///
/// An abstract class that can save itself to a stream
///
class Savable {
public:
    /// Save this class to the given stream
    /// @param stream the stream to save to
    virtual void save (std::ostream & stream) const = 0;

    ///
    /// Virtual destructor needed for base class
    /// 
    virtual ~Savable() = default;
};
