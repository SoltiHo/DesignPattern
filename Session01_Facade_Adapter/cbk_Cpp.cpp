//============================================================================
// Name        : cbk_Cpp.cpp
// Author      : Allan Goff
// Version     :
// Copyright   : Your copyright notice
// Description : DPSG: Facade and Adapter patterns.
//============================================================================

#include <iostream>
using namespace std;

#include "facade.h"
using namespace legacy;
using namespace facade;

#include "adapter.h"
using namespace corpShapes;
using namespace adapter;

int main() {
	cout << "Hello dpsg.\n" << endl;

	// Facade.
	Facade house;
	house.goToWork(); cout << endl;
	house.comeHome(); cout << endl;

	// Adapter.
	Point   point;	point.draw();
	Line    line;	line.draw();
	Rect    rect;	rect.draw();	cout << endl;

	Polygon poly;	poly.draw();
	Torus   torus;	torus.draw();
	Bezel   bezel;	bezel.draw();	cout << endl;

	ExistingShapesInterface* shapes[6];
	int i = 0;
	shapes[i++] = new Point;
	shapes[i++] = new Line;
	shapes[i++] = new Rect;
	shapes[i++] = new Polygon;
	shapes[i++] = new Torus;
	shapes[i++] = new Bezel;

	for(int i=0; i<6; i++) {
		shapes[i]->draw();
	}
	cout << endl;

	cout << "Aloha, dpsg." << endl;
	return 0;
}
