/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Player ship
///
/// Object for the player ship model
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

class PlayerShip : public Entity
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class
    ///
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    /// \param The screen resolution (to determine the radius
    /// the playerShip circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    ///
    ////////////////////////////////////////////////////////////
    PlayerShip(const sf::Vector2i resolution,
               float distanceFromCentre,
               float angle,
               float scale,
               const entity::ID type,
               const TextureHolder &textureHolder);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the future player movement, rotating the
    /// the player ship around a circle by this angle.
    ///
    /// The actual
    /// position of the playerShip is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The delta change in angle (will be added to
    /// the current angle.
    /// \see move()
    ////////////////////////////////////////////////////////////
    void setMove(float angle) override;

    ////////////////////////////////////////////////////////////
    /// \brief Moves the player ship around a circle by this angle,
    /// based on the futureAngleValue and futureMoveValue
    ////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the player ship (intended to be called after
    /// a player death event)
    ///
    /// The playership position is reset back
    /// to the bottom of the screen, on the movement circle.
    /// Invulnerability is turned on, and the invulnerability timer restarted,
    /// The various boolean states are reset to their default values.
    /// Any upgrades are lost, and these planned moves are immediately performed
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates the movement, shooting and calls
    /// the actual movement translation
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the boolean state of the playerShip upgrade status to true.
    ///
    /// If the player performs certain actions, an upgraded state will
    /// grant a different, more powerful method of shooting.
    ////////////////////////////////////////////////////////////
    void upgrade();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (screen space)
    ////////////////////////////////////////////////////////////
    const float getRadius() const override; // As below

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (non-linear distance)
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const sf::Sprite &getSprite() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x,y position of the playership on screen
    ////////////////////////////////////////////////////////////
    const sf::Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the scale (in width/hieght) of the playerShip object
    ////////////////////////////////////////////////////////////
    const sf::Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the player
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the player lives
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip (alive/dead)
    ////////////////////////////////////////////////////////////
    const bool isAlive() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean movement state of the playerShip
    ////////////////////////////////////////////////////////////
    const bool isMoving() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean shooting state of the playerShip
    ////////////////////////////////////////////////////////////
    const bool isShooting() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip taking damage from collisions or not
    ///
    /// After respawning, the playerShip is briefly invulnerable, to avoid
    /// immediate "unfair" deaths from collisions.
    ///
    ////////////////////////////////////////////////////////////
    const bool isInvulnerable() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip upgrade status
    ///
    /// If the player performs certain actions, an upgraded state will
    /// grant a different, more powerful method of shooting.
    ////////////////////////////////////////////////////////////
    const bool isUpgraded() const;


    ////////////////////////////////////////////////////////////
    /// \brief Makes the playerShip unaffected by damage
    ///
    /// Developer (debug) mode only. Used with hotkeys in non-release mode
    /// for testing.
    ////////////////////////////////////////////////////////////
    void makeInvulnerable(bool godMode);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the _isShooting state of the playerShip
    ////////////////////////////////////////////////////////////
    void setShoot();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the playership around the movement circle
    ////////////////////////////////////////////////////////////
    float getAngle();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the future, intended angle of the playership around the movement circle,
    /// which will be updated after the "update" method has completed.
    ////////////////////////////////////////////////////////////
    float getFutureAngle();

private:

    ////////////////////////////////////////////////////////////
    /// \brief resets the isShooting status to false.
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::SoundBuffer _buffer;
    sf::Sound _soundMove;
    sf::IntRect _rectArea;
    int _spriteOffset;
    float _futureAngleValue;
    bool _isMoving;
    bool _isShooting;
    bool _isInvulnerable;
    bool _isUpgraded;
    bool _isAlive;
    sf::Clock _invulnerabilityTimer;
    float _invulnerabilityTimeAmount;
};

#endif //PROJECT_PLAYERSHIP_HPP
