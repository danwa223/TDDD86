/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h" //old
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(Robot c);

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
};

#endif // JUNK_H
