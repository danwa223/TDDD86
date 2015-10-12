/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();

	/*
	* Draws this junk onto the given QGraphicsScene.
	*/
	virtual void draw(QGraphicsScene* scene) const;

	/*
	 *
	 */
	virtual void moveTowards(const Unit& u);

    /*
     *
     */
    virtual bool attacks(const Unit &u) const;

    virtual bool isJunk(const Unit &u) const; //use void? I dont even...
};

#endif // ROBOT_H
