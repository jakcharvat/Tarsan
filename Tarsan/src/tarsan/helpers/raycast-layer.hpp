//
//  raycast-layer.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <initializer_list>


enum class RaycastLayer: int {
    STONE = 1,
    LAVA = 2,
    LIANA = 4,
    EMPTY = 8,
};


/// Convert the given layers into a single bitmask
///
/// @tparam Args the arguments. Must all be RaycastLayer
/// @param layers the layers to combine
/// @returns a combined bitmask
template <typename... Args>
constexpr
int raycastMask(Args... layers) {
    int mask = 0;
    for (RaycastLayer layer : { layers... }) {
        mask |= static_cast<int>(layer);
    }
    return mask;
}


constexpr int LEAST_DANGEROUS_LAYER = raycastMask(RaycastLayer::EMPTY);
constexpr int LAYER_MASK_RANGE = LEAST_DANGEROUS_LAYER | LEAST_DANGEROUS_LAYER - 1;


/// Check whether the bitmask contains the specified layer
/// @param mask the mask to check
/// @param layer the layer to look for
/// @returns true if the mask contains the layer
bool raycastMaskMatches(int mask, RaycastLayer layer);

/// Make a mask with the layers greater than and equal to the one specified
/// @param until the least dangerous layer to include
/// @returns a combined bitmask
int dangerRaycastMask(RaycastLayer until);

/// Make a mask with the layers less than and equal to the one specified
/// @param until the most dangerous layer to include
/// @returns a combined bitmask
int safeRaycastMask(RaycastLayer until);
