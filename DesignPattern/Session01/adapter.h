/*
 * adapter.h
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

namespace corpShapes {		 // Small but installed and heavily used class hierarchy.

class ExistingShapesInterface {					// Base class.
public:
	virtual void draw() = 0;
	virtual ~ExistingShapesInterface() {}
};

class Point : public ExistingShapesInterface {	// Derived classes.
public:
	void draw() {
		cout << "Draw point." << endl;
	}
};
class Line : public ExistingShapesInterface {
public:
	void draw() {
		cout << "Draw line." << endl;
	}
};
class Rect : public ExistingShapesInterface {
public:
	void draw() {
		cout << "Draw rectangle." << endl;
	}
};

}

namespace GeneralDynShapes { // A 2nd class hierarchy with needed features, but different API.

class ConvolutedShapes {					// Base class.
public:
	virtual void display() = 0;
	virtual ~ConvolutedShapes() {}
};

class Polygon : public ConvolutedShapes {	// Derived classes.
public:
	void display() {
		cout << "Display polygon." << endl;
	}
};
class Torus : public ConvolutedShapes {
public:
	void display() {
		cout << "Display torus." << endl;
	}
};
class Bezel : public ConvolutedShapes {
public:
	void display() {
		cout << "Display bezel." << endl;
	}
};

}

namespace adapter {			 // Create a unified API to support polymorphism.

using namespace corpShapes;

class Polygon : public ExistingShapesInterface {
	GeneralDynShapes::Polygon poly;
public:
	void draw() {
		poly.display();
	}
};

class Torus : public ExistingShapesInterface {
	GeneralDynShapes::Torus torus;
public:
	void draw() {
		torus.display();
	}
};

class Bezel : public ExistingShapesInterface {
	GeneralDynShapes::Bezel bezel;
public:
	void draw() {
		bezel.display();
	}
};

}

#endif /* ADAPTER_H_ */
