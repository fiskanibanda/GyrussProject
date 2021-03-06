/////////////////////////////////////////////////////////////////////
/// \brief   Explosion entity for destroyed screen objects
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_EXPLOSION_HPP
#define PROJECT_EXPLOSION_HPP

#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

using sf::Sprite;
using sf::Vector2f;
using sf::Color;

////////////////////////////////////////////////////////////
/// \brief Explosion class, for objects that collide
///
/// Inherits from the Entity base class.
////////////////////////////////////////////////////////////
class Explosion : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the Explosion Class. Calls the ABC constructors
    /// for the inheritance hierarchy, Entity, Moveable and Animatable.
    ///
    /// Explosion are spawned by collision events, at a specific location,
    /// where they cycle through their frame animation, and then die.
    ///
    /// \param resolution The screen resolution of the game
    /// \param distanceFromCentre The radius from centre at which the
    /// explosion should be created
    /// \param angle The argument (angle) at which the explosion should be
    /// placed upon creation
    /// \param scale The initial size of the explosion object (also influenced
    /// by the sprite texture, and scaled by distance from the origin in the move() command.
    /// \param type An enum that identifies the Entity type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The textureHolder object, passed by const ref.
    /// provides a unique_ptr to an sf::Texture for the sprite data member
    /// \param id The unique ID identifying the texture for the entity
    ///
    /// \see Entity
    /// \see EntityController
    /// \see common
    /// \see ResourceHolder
    /// ////////////////////////////////////////////////////////////
    Explosion(const Vector2i resolution,
              float distanceFromCentre,
              float angle,
              float scale,
              const entity::ID type,
              const TextureHolder &textureHolder,
              const textures::ID id);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the future movement, either by change in angle or change in distance
    ///
    /// Some entities only need a change in angle, or distance, not both.
    /// The actual position of the entity is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param value The delta change in angle or distance (will be added to
    /// the current angle/distance
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    void setMove(float value) override {}

    ////////////////////////////////////////////////////////////
    /// \brief Sets up the next frame's position for the object.
    ///
    /// The actual position of the explosion is not altered until the move()
    /// method is called, which performs the actual translation.
    /// This method is only used upon creation of the object (explosions do not move)
    ///
    /// \param angle Change in angle for the explosion should move for the next frame
    /// \param distance How far the explosion should move for the next frame
    /// (in screen space)
    ////////////////////////////////////////////////////////////
    void setMove(float angle, float distance) override;

    ////////////////////////////////////////////////////////////
    /// \brief Performs the actual move, based on _futureMoveValue and _futureAngleValue
    ///////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the explosion upon finishing the animation
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates any movement, advances the tile for the animation
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the explosion lives, which will cause it to be removed on the next frame
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \return The sf::Sprite object representing the position,
    /// dimensions and texture of the explosion
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const Sprite &getSprite() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (screen space)
    ///
    /// \return A float value of the distance from centre of the screen
    ////////////////////////////////////////////////////////////
    const float getRadius() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (non-linear distance)
    ///
    /// \return A float value, the depth from the centre in z
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the explosion
    ///
    /// \return A float value, the angle for mod/arg position
    ////////////////////////////////////////////////////////////
    const float getAngle() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x,y position of the explosion on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} position of the explosion
    /// \see [SFML/Vector2](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php)
    ////////////////////////////////////////////////////////////
    const Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the scale (in width/height) of the explosion object
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} scale of the explosion
    /// \see [SFML/Vector2](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php)
    ////////////////////////////////////////////////////////////
    const Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the explosion
    ///
    /// \return An integer value of the remaining explosion lives (usually 0 or 1)
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the entity (alive/dead)
    ///
    /// \return A boolean value of alive(1) or dead(0)
    ////////////////////////////////////////////////////////////
    const bool isAlive() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the entity type
    ///
    /// \return An enum value (defined in common.hpp) of the entity type
    /// \see common
    /// \see Entity
    ////////////////////////////////////////////////////////////
    const entity::ID getType() const override;
};

#endif //PROJECT_EXPLOSION_HPP
