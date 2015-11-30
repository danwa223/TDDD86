#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <map>
#include "Point.h"

// Constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {

	for(const auto& point : points) {
		point.draw(scene);
	}
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {

	p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	// Open file, input files can be found in /res
	string filename = "input100.txt";
	ifstream input;
	input.open(filename);

	// The point vector
	vector<Point> points;

	// Read points from input file, where N is the amount of points in the file
	int N;
	int x;
	int y;

	input >> N;

	for (int i = 0; i < N; ++i) {
		input >> x >> y;
		points.push_back(Point(x, y));
	}
	input.close();

	// Setup graphical window
	QGraphicsView *view = new QGraphicsView();
	QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
	view->setScene(scene);

	// Draw points to screen all at once
	render_points(scene, points);
	view->scale(1, -1); //screen y-axis is inverted
	view->resize(view->sizeHint());
	view->setWindowTitle("'Smart' Pattern Recognition");
	view->show();

	// Sort points by natural order
	// Makes finding endpoints of line segments easy
	sort(points.begin(), points.end());

	// Start the timer
	auto begin = chrono::high_resolution_clock::now();

	// For each each point
	for (int point = 0; point < points.size(); ++point) {

		// Create a map with the slope as key
		map<double, vector<Point>> pointMap;

		// Check the slope of point in relation to point + i until the end of the points vector
		for (int i = point + 1; i < points.size(); ++i) {

			// Then add the point to the map to get them sorted depending on slope
			double slope = points.at(point).slopeTo(points.at(i));
			pointMap[slope].push_back(points.at(i));
		}

		// Go through every key (slope) in the map and check if any contain 3 or more
		map<double, vector<Point>>::iterator it;
		for(it = pointMap.begin(); it != pointMap.end(); ++it) {
			if(it->second.size() >= 3) {

				// Draw a line from the starting point to the
				render_line(scene, points.at(point), *(it->second.end() - 1));

				// Show rendered line (according to brute.cpp)
				a.processEvents();
			}
		}
	}

	// Stop and print the timer
	auto end = chrono::high_resolution_clock::now();
	cout << "Computing line segments took "
		 << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
		 << " milliseconds." << endl;

	return a.exec(); // start Qt event loop
}
