/////////////////////////////////////////////////////////////////////
/// \brief   Controller and manager for game entity objects
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_ENTITYCONTROLLER_HPP
#define PROJECT_ENTITYCONTROLLER_HPP

#include <list>
#include "common.hpp"
#include "ResourceHolder.hpp"
#include "Entity.hpp"
#include "PlayerShip.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Explosion.hpp"
#include "Meteoroid.hpp"
#include "Score.hpp"
#include "PerlinNoise.hpp"

using entityList = std::list<std::unique_ptr<Entity>>;

////////////////////////////////////////////////////////////
/// \brief EntityController Class
///
/// Responsible for spawning and destroying non-player game entities (bullets, enemies, meteoroids, explosions)
/// Responsible for the behaviour and logic of all non-player entities
/// Responsible for collision detection between these entities and playerShip
/// Responsible for updating the movement of all non-player entities
////////////////////////////////////////////////////////////
class EntityController
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the EntityController class. Called directly
    /// from game object to handle the creation, destruction and drawing of all game objects.
    ///
    /// On every game frame, respective functions are called to evaluate game entity states, such
    /// as spawning new enemies, collisions and enemy bullet shooting
    ///
    /// \param resolution The Screen resolution of the game
    /// \param playerShip The playerShip, generated from the game.cpp. needed for collision detection
    /// \param textures used to create new entities that require this class for creation
    /// \param score object to track the current game score, enemies killed and player deaths. created in game.cpp
    /// \param speedModifier defines how fast the game runs at a particular time to speed up game as time progresses
    ///
    /// \see [SFML/Vector2](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php)
    /// \see PlayerShip
    /// \see Score
    /// \see ResourceHolder
    ///////////////////////////////////////////////////////////////
    EntityController(Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures,
                     Score &score,
                     float speedModifier);

    ////////////////////////////////////////////////////////////
    /// \brief Sets up next frame' movement on all entities (in EntityController)
    ///
    /// \see setEnemyMove
    /// \see setEnemyMoveState
    /// \see setBulletMove
    /// \see setMeteoroidMove
    /// \see Enemy
    ////////////////////////////////////////////////////////////
    void setMove();

    ////////////////////////////////////////////////////////////
    /// \brief Initiates the spawn event for Enemy, Satellites and Meteoroid
    ///
    /// Defines the spawn chances based on a combination of delay between spawns,
    /// and random event chances. There is a maximum & minimum number of enemies
    /// that can be alive at one time
    ///
    /// \see Enemy
    /// \see spawnMeteoroid
    /// \see spawnSatellites
    /// \see spawnSpiral
    /// \see Enemy
    /// \see Meteorid
    ////////////////////////////////////////////////////////////
    void spawnEntities();

    ////////////////////////////////////////////////////////////
    /// \brief Spawns an enemy of a defined id and variant in a spiral direction(movementState)
    /// function is called from spawnEntities
    ///
    /// This function includes: spiral inwards, spiral outwards and wandering movement
    ///
    /// \param id defines the kind of ship spawned
    /// \param shipVariant defines the look of the ship spawned
    /// \param movementDirection enum, showing clockwise or counterclockwise ship direction
    /// \param movementState spesifies what kind of spiral the ship is doing: inwards, outwards or wandering
    ///
    /// \see Enemy
    ////////////////////////////////////////////////////////////
    void spawnBasicEnemy(entity::ID id,
                         textures::ID shipVariant,
                         MovementDirection movementDirection,
                         MovementState movementState);

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a meteoroid
    /// function is called from spawnEntities
    ///
    /// \see Meteoroid
    ////////////////////////////////////////////////////////////
    void spawnMeteoroid();

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a Satellite, a type of Enemy.
    /// function is called from spawnEntities
    ///
    /// \see Enemy
    ////////////////////////////////////////////////////////////
    void spawnSatellites();

    ////////////////////////////////////////////////////////////
    /// \brief Initiates a player shoot event based on current gun level
    /// and adds a bullet to the bulletList
    ///
    /// \see playerShoot
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    /// \brief Checks all playerShips to see if they are outside of the play range.
    /// In the event that they are, remove them from the game(reset the ships)
    ////////////////////////////////////////////////////////////
    void checkClipping();

    ////////////////////////////////////////////////////////////
    /// \brief Responsible for dealing with all collision with all game objects.
    /// PlayerBullet->Enemy, EnemyBullet->PlayerShip, PlayerBullet->EnemyBullet,
    ///
    /// In the event that there is a collision between entities,
    /// remove them from the game (reset the ships or delete bullets).
    /// This function is also responsible for generating explosion events on ship deaths
    ///
    /// \see collides
    ///
    /// \return A bool that is true if collision occurred with playerShip
    /// (false if no player collision occurred)
    ////////////////////////////////////////////////////////////
    bool checkCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Used to check for collisions between two sprites
    ///
    /// \param sprite1 first sprite that is fed in, compared to sprite2
    /// \param sprite2 second sprite that is fed in, compared to sprite1
    ///
    /// \see checkCollision
    /// \see [SFML/Sprite](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php)
    ///
    /// \return a bool, true if collision, false if not
    ////////////////////////////////////////////////////////////
    bool collides(const Sprite &sprite1,
                  const Sprite &sprite2);

    ////////////////////////////////////////////////////////////
    /// \brief Updates all game objects by calling the underlying update functions.
    /// Called on every frame, to move entities around the screen as well as other functions
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return if an explosion has occurred on the current frame.
    /// Used to deal with multiple explosions occurred in quick succession to reset
    /// the explosion object and sound generation.
    ///
    /// \see SoundController
    ///
    /// \return A bool relating to if an explosion occurred in the current frame
    ////////////////////////////////////////////////////////////
    const bool explosionOccurred();

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return if an bullet has been shot in the current frame
    ///
    /// \return A bool relating to if a bullet was fired in the current frame
    ////////////////////////////////////////////////////////////
    const bool shootingOccurred();

    ////////////////////////////////////////////////////////////
    /// \brief Adjust the game speed as time goes on to make it more challenging.
    /// Has imposed maximum, minimum and default interval values.
    ///
    /// \param amount defines the amount to increase the global speed by
    ////////////////////////////////////////////////////////////
    void changeGlobalSpeed(float amount);

    ////////////////////////////////////////////////////////////
    /// \brief Reverts the game speed to the stock default value
    ////////////////////////////////////////////////////////////
    void resetGlobalSpeed();

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return the current game speed
    ///
    /// \return Current speed of the gameplay
    ////////////////////////////////////////////////////////////
    const float getSpeed() const;

    ////////////////////////////////////////////////////////////
    /// \brief Destroys all enemies of a particular type. This is useful
    /// When a game event requires all of one type of enemy to be removed. For example,
    /// if the player dies, all satellites that are still alive should be removed.
    ///
    /// \param type defines the type of enemy to kill
    ////////////////////////////////////////////////////////////
    void killAllEnemiesOfType(entity::ID type);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a list of all current player bullets.
    ///
    /// \return List of all player bullets currently in play
    ////////////////////////////////////////////////////////////
//    const bulletList &getBulletsPlayer() const;
    const entityList &getBulletsPlayer() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a list of all current enemy bullets.
    ///
    /// \return List of all enemy bullets
    ////////////////////////////////////////////////////////////
//    const bulletList &getBulletsEnemy() const;
    const entityList &getBulletsEnemy() const;


    ////////////////////////////////////////////////////////////
    /// \brief Returns a list of all current enemies.
    ///
    /// \return List of all enemies currently in play
    ////////////////////////////////////////////////////////////
//    const enemyList &getEnemies() const;
    const entityList &getEnemies() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a list of all current meteoroid.
    ///
    /// \return List of current meteoroids in play
    ////////////////////////////////////////////////////////////
//    const meteoroidList &getMeteoroids() const;
    const entityList &getMeteoroids() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a list of all current explosions.
    ///
    /// \return List of current explosions in play
    ////////////////////////////////////////////////////////////
//    const explosionList &getExplosions() const;
    const entityList &getExplosions() const;

private:
    ////////////////////////////////////////////////////////////
    /// \brief Changes enemy movement state based on current ship position and
    /// random chance to change flight pattern
    ///
    /// \see setEnemyMove()
    ////////////////////////////////////////////////////////////
    void setEnemyMoveState();

    ////////////////////////////////////////////////////////////
    /// \brief Executes ship movement, based on ship movement state defined in
    /// setMove function
    ///
    /// Programmatic method of moving ships around, based on movement state
    ///
    /// \param enemy enemy ship to be moved
    /// \param currentEnemyMovementState movement state that the ship should preform operation in. be it spiral in or others
    /// \param growShipScreenZone defines region where the ship should grow and not change state
    /// \param currentEnemyRadius defines the current size of the enemy ship
    ///
    /// \see setMove
    /// \see Enemy
    ////////////////////////////////////////////////////////////
    void setEnemyMove(std::unique_ptr<Entity> &enemy,
                      MovementState currentEnemyMovementState,
                      float growShipScreenZone,
                      float currentEnemyRadius);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the next frame's movement on all bullets (Player and Enemy)
    ///
    /// \see setMove
    ////////////////////////////////////////////////////////////
    void setBulletMove();

    ////////////////////////////////////////////////////////////
    /// \brief Sets the next frame's movement on all Meteoroids
    ///
    /// \see setMove
    ////////////////////////////////////////////////////////////
    void setMeteoroidMove();

    ////////////////////////////////////////////////////////////
    /// \brief Initiates a player shoot event based on current gun level
    /// and adds bullet to bullet vector
    ///
    /// \see PlayerShip
    ////////////////////////////////////////////////////////////
    void playerShoot();

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions between EnemyShips->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkEnemyToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions between EnemyBullet->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkEnemyBulletsToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions between PlayerBullet->EnemyShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkPlayerBulletsToEnemyCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions between Meteoroid->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkMeteoroidToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Checks collisions between PlayerBullet->Meteoroid,
    /// removing only the bullet if they collide (meteoroid are
    /// invulnerable but bullets must still be removed)
    ////////////////////////////////////////////////////////////
    void checkPlayerBulletsToMeteoroidCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief Used when any enemy is killed to preform additional enemy type
    /// spesific logic, such as upgrading a gun kf all satellites are killed
    ///
    /// \param type defines the type of enemy that is killed
    ////////////////////////////////////////////////////////////
    void enemyKilled(entity::ID type);

    ////////////////////////////////////////////////////////////
    /// \brief Called to upgrade the PlayerShip
    ////////////////////////////////////////////////////////////
    void upgradePlayerShip();

    ////////////////////////////////////////////////////////////
    /// \brief Vector to store the screen size
    ////////////////////////////////////////////////////////////
    Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief Texture holder, to access all game assets loaded in other context.
    /// Is a reference as is not created in the EntityController
    ////////////////////////////////////////////////////////////
    TextureHolder &_textureHolder;

    ////////////////////////////////////////////////////////////
    /// \brief PlayerShip object generated from game.cpp. Is a reference
    /// as is not created in the EntityController
    ////////////////////////////////////////////////////////////
    PlayerShip &_playerShip;


    ////////////////////////////////////////////////////////////
    /// \brief A list of unique_ptr of type <Entity> to store all Enemy Bullets
    ////////////////////////////////////////////////////////////
    entityList _bulletsEnemy;

    ////////////////////////////////////////////////////////////
    /// \brief A list of unique_ptr of type <Entity> to store all Player Bullets
    ////////////////////////////////////////////////////////////
    entityList _bulletsPlayer;

    ////////////////////////////////////////////////////////////
    /// \brief A list of unique_ptr of type <Entity> to store all Enemy ships
    ////////////////////////////////////////////////////////////
    entityList _enemies;

    ////////////////////////////////////////////////////////////
    /// \brief A list of unique_ptr of type <Entity> to store current explosion objects
    ////////////////////////////////////////////////////////////
    entityList _explosions;

    ////////////////////////////////////////////////////////////
    /// \brief A list of unique_ptr of type <Entity> to store flying meteoroids
    ////////////////////////////////////////////////////////////
    entityList _meteoroids;

    ////////////////////////////////////////////////////////////
    /// \brief A Clock to store time from last ship spawn from perimeter. Used to stagger
    /// the spawn event of a ship flying with this formation
    ////////////////////////////////////////////////////////////
    Clock _timerSpawnFromPerimeter;

    ////////////////////////////////////////////////////////////
    /// \brief A Clock to store time from last ship spawn from centre. Used to stagger
    /// the spawn event of a ship flying with this formation
    ////////////////////////////////////////////////////////////
    Clock _timerSpawnFromCentre;

    ////////////////////////////////////////////////////////////
    /// \brief A Clock to store time from last wandering ship. Used to stagger
    /// the spawn event of a ship flying with this formation
    ////////////////////////////////////////////////////////////
    Clock _timerSpawnWanderer;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to store the time from when a Satellite was las spawned
    ////////////////////////////////////////////////////////////
    sf::Clock _timerSatellite;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to store the time from when a meteoroid was las spawned
    ////////////////////////////////////////////////////////////
    sf::Clock _timerMeteoroid;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to how long the game as been running
    ////////////////////////////////////////////////////////////
    sf::Clock _totalTime;

    ////////////////////////////////////////////////////////////
    /// \brief A score object to store the current game score state. This is fed into
    /// the Entity controller on construction and is stored as a reference.
    ////////////////////////////////////////////////////////////
    Score &_score;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if an explosion has occurred on the current frame
    ///
    /// \see explosionOccurred
    ////////////////////////////////////////////////////////////
    bool _explosionHasOccurred;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if an enemy has shot a bullet in the current frame
    ///
    /// \see shootingOccurred
    ////////////////////////////////////////////////////////////
    bool _enemyShootEventHasOccurred;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if the playerShip was hit in the current frame
    ///
    /// \see collides
    ////////////////////////////////////////////////////////////
    bool _playerHasBeenHit;

    ////////////////////////////////////////////////////////////
    /// \brief Float to store the current game speed modifier
    ///
    /// \see getSpeed
    /// \see resetGlobalSpeed
    /// \see changeGlobalSpeed
    ////////////////////////////////////////////////////////////
    float _speedModifier;

    ////////////////////////////////////////////////////////////
    /// \brief Float to store the default game speed. The game speed is reset
    /// to this value when the game starts and when the player looses a life
    ///
    /// \see resetGlobalSpeed
    ////////////////////////////////////////////////////////////
    float _defaultSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief Int to count the total number of satellites that are alive at a point
    ///
    /// \see spawnSatellites
    /// \see spawnEntities
    ////////////////////////////////////////////////////////////
    int _satellitesAlive;

    ////////////////////////////////////////////////////////////
    /// \brief Float to store the speed that a player bullet should fly at
    ////////////////////////////////////////////////////////////
    float _bulletPlayerSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief Float to store the speed that an enemy should fly at
    ////////////////////////////////////////////////////////////
    float _bulletEnemySpeed;

    ////////////////////////////////////////////////////////////
    /// \brief Float to store the speed that a meteoroid should fly at
    ///
    /// \see spawnMeteoroid
    ////////////////////////////////////////////////////////////
    float _meteoroidSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief PerlinNoise object to store the perlinNoise X parameter used in wandering
    /// playerShip movement
    ////////////////////////////////////////////////////////////
    PerlinNoise _xNoise;

    ////////////////////////////////////////////////////////////
    /// \brief PerlinNoise object to store the perlinNoise Y parameter used in wandering
    /// playerShip movement
    ////////////////////////////////////////////////////////////
    PerlinNoise _yNoise;

    void enemyShoot();
};

#endif //PROJECT_ENTITYCONTROLLER_HPP
