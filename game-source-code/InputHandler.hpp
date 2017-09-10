/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    InputHandler.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_INPUTHANDLER_HPP
#define PROJECT_INPUTHANDLER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Game.hpp"
#include "PlayerShip.hpp"
#include <map>

class InputHandler
{
public:
    void resolveKeyMapping(const key_map &keys_pressed,
                           PlayerShip &playerShip);
private:

};
#endif //PROJECT_INPUTHANDLER_HPP
