//
//  player-entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "entity.hpp"

///
/// A class storing a player entity
/// 
class PlayerEntity: public Entity {
private:
    ///
    /// The two possible directions a player could face
    ///
    enum class PlayerDirection {
        LEFT, RIGHT
    };

    ///
    /// The direction the player is currently facing
    ///
    PlayerDirection _direction { PlayerDirection::LEFT };

    ///
    /// The current vertical velocity of the player
    ///
    int _vertVelocity = 0;

    ///
    /// Whether the player just took damage
    /// 
    bool _tookDamage = false;

    /// Perform a fall on the entity
    /// @param distance the distance from the ground
    void _performFall(int distance);

    char _getChar(WINDOW * window) const override;

public:
    /// Construct a player entity at the given position
    /// @param position the position to construct at
    PlayerEntity(Coord position);

    void update(Map &map) override;
};
