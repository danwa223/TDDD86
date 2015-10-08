/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Hero.h"
#include "constants.h"

Hero::Hero() : Unit() {}

void Hero::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addRect(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                          UNIT_WIDTH, UNIT_HEIGHT), Qt::NoPen, QBrush(HERO_COLOR));
}

void Hero::moveTowards(const Point& p) {
	Point heroPos = asPoint();
    //does this compare hero position with a move we already made and adjusts hero position thereafter???
	if (heroPos.x > p.x) heroPos.x--;
	if (heroPos.x < p.x) heroPos.x++;
	if (heroPos.y > p.y) heroPos.y--;
	if (heroPos.y < p.y) heroPos.y++;
	//checkBounds(); //dis is private
}
