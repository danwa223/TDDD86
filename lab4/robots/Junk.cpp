/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Junk.h"
#include "constants.h"

Junk::Junk() : Robot() {}
Junk::Junk(Robot c) : Robot(c) {}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Unit &u) {
    //do nothing
}

bool Junk::attacks(const Unit &u) const{
    return false; //junk cannot attack
}

bool Junk::isJunk(const Unit &u) const{
    return true; //junk is always junk, but when is isJunk supposed to be called? Should probably return true if Robot stopped moving?
}
