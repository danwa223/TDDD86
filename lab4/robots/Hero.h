/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include <QGraphicsScene>

class Hero : public Unit {
public:
    Hero();

    /*
    * Draws this hero onto the given QGraphicsScene.
    */
	virtual void draw(QGraphicsScene *scene) const;

	/*
	 *
	 */
	virtual void moveTowards(const Point& p);
};

#endif // HERO_H
