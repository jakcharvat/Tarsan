//
//  map-loader.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"


class MapLoader {
public:
    using EntityPtr = std::unique_ptr<Entity>;
    using EntityRow = std::vector<EntityPtr>;
    using EntityMap = std::vector<EntityRow>;

    /// Get a map
    ///
    /// This can be either a randomly generated map or one loaded from file, but it must be valid and ready to play
    ///
    /// An exception can be thrown from this function for invalid maps
    ///
    /// @returns the loaded map
    /// @throws fatal error if loading failed
    virtual EntityMap getMap() = 0;

    ///
    /// Virtual destructor needed for base class
    ///
    virtual ~MapLoader() = default;
};
