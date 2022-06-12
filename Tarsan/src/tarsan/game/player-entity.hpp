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
public:
    static constexpr int MAX_HP = 100;

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
    PlayerDirection _direction { PlayerDirection::RIGHT };

    ///
    /// The current vertical velocity of the player
    ///
    int _vertVelocity = 0;

    ///
    /// Current player hp
    ///
    int _hp = MAX_HP;

    ///
    /// Whether the player is currently jumping
    ///
    bool _jumping = false;

    ///
    /// Whether the player just took damage
    /// 
    bool _tookDamage = false;

    /// Perform a fall on the entity
    /// @param distance the distance from the ground
    void _performFall(int distance);

    /// Move in the specified direction if the position is free
    /// @param direction the direction to move in
    /// @param map the map to move in
    void _move(Direction direction, Map &map);

    /// Jump up
    /// @param map the map to jump in
    void _jump(Map &map);

    /// Check whether the player is currently on a liana
    /// @param map the map to check in
    bool _isOnLiana(Map &map);

    Coord _keyToCoord(int key) const;

    /// Break a block at the position specified by the key
    /// @param key the event raising this action
    /// @param map the map to delete in
    void _destroy(int key, Map &map);

    /// Build a block at the position specified by the key
    /// @param key the event raising this action
    /// @param map the map to delete in
    void _build(int key, Map &map);

    /// Shoot a liana upwards towards the nearest stone block
    /// @param map the map to shoot in
    void _shootLiana(Map &map);

    /// Deal damage to the player
    /// @param hp the amount of hp to take
    void _damage(int hp);

    char _getChar(WINDOW * window) const override;

public:
    /// Construct a player entity at the given position
    /// @param position the position to construct at
    PlayerEntity(Coord position);

    /// Handle a key event
    /// @param key the key that was registered
    /// @param map the containing map
    void handleEvent(int key, Map &map);

    /// Get this player's remaining HP
    /// @returns the remaining HP of this player
    int getHp() const;

    void update(Map &map) override;
};
