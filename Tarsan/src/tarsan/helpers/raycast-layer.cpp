//
//  raycast-layer.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "raycast-layer.hpp"


bool
raycastMaskMatches(int mask, RaycastLayer layer) {
    return (mask & raycastMask(layer)) != 0;
}


int
dangerRaycastMask(RaycastLayer until) {
    int untilInt = raycastMask(until);
    return untilInt | untilInt - 1;
}


int
safeRaycastMask(RaycastLayer until) {
    return (LAYER_MASK_RANGE ^ dangerRaycastMask(until)) | raycastMask(until);
}
