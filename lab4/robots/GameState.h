/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 * Method isSafe() is used to keep Hero from moving stupidly.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"
#include <iostream>

class GameState {
public:
    GameState();
    GameState(const GameState& other);
    GameState(int numberOfRobots);
    ~GameState();

    GameState& operator=(const GameState& other); //would this be the proper way to put the operator?

    /*
     * Clear and redraw entire playing field
     */
    void draw(QGraphicsScene* scene) const;	// Clear and redraw entire playing field

    /*
     * Teleport hero to random location
     */
    void teleportHero();

    /*
     * Move robots one step towards hero
     */
    void moveRobots();

    /* Count colliding robots
     * Also converts robots to junk while
     * checking collisions
     */
    int countCollisions ();

    /*
     * Check if any robots are left on playing field
     */
    bool anyRobotsLeft () const;

    /*
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /*
     * Can unit safely reside here?
     */
    bool isSafe (const Unit& unit) const; // Can unit safely reside here?

    /*
     * Move hero towards dir
     */
    void moveHeroTowards (const Unit& dir);

    /*
     * Return hero
     */
    Hero getHero () const;

private:

    //void GameState::copyOther(const GameState& other); //see cpp file

    std::vector<Robot*> robots;  // the robots
    //std::vector<Junk> junks;   // robots that have turned to junk
    Hero* hero = nullptr;     // the hero

    // private helpers
    bool isEmpty(Unit *unit) const;
    //bool junkAt(const Unit& unit) const;
    int countRobotsAt(Unit *unit) const;

};

#endif // GAMESTATE_H
