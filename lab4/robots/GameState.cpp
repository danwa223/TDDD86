/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

using namespace std;

GameState::GameState(){
    hero = new Hero();
}

GameState::GameState(const GameState& other){
    hero = new Hero(*other.hero);
    for (int i = 0; i < other.robots.size(); i++){
        Robot *robot = new Robot(*other.robots[i]);
        robots.push_back(robot);
    }
}

GameState::GameState(int numberOfRobots) {
    hero = new Hero();
    for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot = new Robot();
        while (!isEmpty (robot)){
            *robot = Robot();
        }
        robots.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState(){
    for (unsigned int i = 0; i < robots.size(); i++){
        delete robots[i];
    }
    delete hero;
}

GameState& GameState::operator=(const GameState& other){
    GameState temp(other);
    swap(temp.hero, hero);
    swap(temp.robots, robots);
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero->draw(scene);
}

void GameState::teleportHero() {
    do hero->teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards(*hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;

    while (i < robots.size()){
        bool collision = (countRobotsAt(robots[i]) > 1);
        if (collision){
            if (!(robots[i]->isJunk())){
                numberDestroyed++;

                Robot *tempptr = robots[i];
                robots[i] = new Junk(*tempptr);
                delete tempptr;
            }
        }
        i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (unsigned int i = 0; i < robots.size(); i++){
        if (!(robots[i]->isJunk())){
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++){
        if (robots[i]->attacks(unit)) return false;
        if ((robots[i]->isJunk()) && (robots[i]->distanceTo(unit) < 1)) return false;
    }
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero->moveTowards(dir);
}

Hero GameState::getHero() const {return *hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(Unit *unit) const {
    return (countRobotsAt(unit) == 0);
}

/*
 * Is there junk at unit?
 */
/*bool GameState::junkAt(Unit *unit) const {
    for (size_t i = 0; i < junks->size(); ++i)
        if (junks[i]->at(unit)) return true;
    return false;
}*/

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(Unit *unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
