/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   The main player ship
///
/// The player's ship flies around the centre of the screen in a circle of fixed
/// radius, shooting at enemies.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const sf::Vector2i resolution,
                       float distanceFromCentre,
                       float angle,
                       float scale,
                       const TextureHolder &textureHolder) : Entity{resolution,
                                                                    distanceFromCentre,
                                                                    angle,
                                                                    scale,
                                                                    textureHolder}
{
    _lives = 3;
    _invulnerabilityTimeAmount = 1.2f;

    _buffer.loadFromFile("resources/thrust.ogg");
    _soundMove.setBuffer(_buffer);
    _soundMove.setLoop(1);
    _soundMove.play();

    _rectArea = {0, 0, 366, 382}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(textures::PlayerShip));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    _isInvulnerable = true;
    _isShooting = false;
    _isMoving = false;
    reset(); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::setMove(float angle)
{
    _isMoving = true;
    _futureAngleValue = angle;
}

void PlayerShip::reset()
{
    _angle = 0;
    _futureAngleValue = 0;
    _isShooting = false;
    _isMoving = false;

    _invulnerabilityTimer.restart();
    _isInvulnerable = true;
    setMove(0);
}

void PlayerShip::update()
{
    if (_isMoving)
    {
        _rectArea.left += _spriteOffset;
        if (_rectArea.left > (3660 - 366)) // Sprite tileset width - individual tile
        {
            _rectArea.left = 0;
        }
        _sprite.setTextureRect(_rectArea);
        move();
    }
    if (_isShooting)
    {
        shoot();
    }
    if (_invulnerabilityTimer.getElapsedTime().asSeconds() > _invulnerabilityTimeAmount)
    {
        _isInvulnerable = false;
    }
    _isMoving = false;
    _futureAngleValue = 0;
    _isShooting = false;
}

const float PlayerShip::getRadius()
{
    return getDistanceFromCentre();
}

const float PlayerShip::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const sf::Vector2f PlayerShip::getPosition()
{
    return _sprite.getPosition();
}


const sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}

const sf::Vector2f PlayerShip::getScale()
{
    return _sprite.getScale();
}

const void PlayerShip::die()
{
    _lives--;
    reset();
}

const int PlayerShip::getLives()
{
    return _lives;
}

void PlayerShip::setShoot()
{
    _isShooting = true;
}

const bool PlayerShip::isShooting()
{
    return _isShooting;
}

const bool PlayerShip::isMoving()
{
    return _isMoving;
}

const bool PlayerShip::isInvulnerable()
{
    return _isInvulnerable;
}

float PlayerShip::getAngle()
{
    return _angle;
}

float PlayerShip::getFutureAngle()
{
    return _futureAngleValue;
}

void PlayerShip::move()
{
    _soundMove.setPitch(fabs(_futureAngleValue/4)); // Engine pitch rises when moving
    _soundMove.setPosition(_sprite.getPosition().x,_sprite.getPosition().y,-5);
    _angle += _futureAngleValue;
    _angle = common::angleFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

void PlayerShip::shoot()
{
    _isShooting = false;
}



