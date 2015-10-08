/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot() : Unit() {}

void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}

void Robot::moveTowards(const Unit& u) {

	Point robotPos = asPoint();

	if (robotPos.x > u.x) robotPos.x--;
	if (robotPos.x < u.x) robotPos.x++;
	if (robotPos.y > u.y) robotPos.y--;
	if (robotPos.y < u.y) robotPos.y++;
	//checkBounds();
}
