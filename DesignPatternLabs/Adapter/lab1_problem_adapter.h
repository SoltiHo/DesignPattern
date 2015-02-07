/*
 * adapter.h
 *
 * Desc: Adapt interfaces so classes can work together polymorphically.
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Adapter
 *  	http://www.dofactory.com/net/adapter-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter7
 *  	http://sourcemaking.com/design_patterns/adapter
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

/* Consider the case where an installed and heavily used class hierarchy
 * for simple shapes needs to be extended by incorporating a commercial
 * class hierarchy containing more complex shapes.
 * The problem is that the two class hierarchies use different API's.
 * The original one uses the function "draw()" the other the function "display()".
 * This breaks the polymorphism that kept the client code simple.
 * This cause 4 maintenance headaches:
 *   1) Client code will become more complicated.
 *   2) Changes will be required in existing client code.
 *   3) Likely become littered with if statements of the sort "what type are you"?
 *   4) Need for error detection.
 * Solve this problem by writing new classes that 'adapt' the new interface
 * to the old.
 */


#include <vector>
#include <iostream>


class ShapeInterfaceDraw {					// Interface class (home grown?).
public:
	virtual void draw()=0;
	virtual ~ShapeInterfaceDraw() {}
};
class Point : public ShapeInterfaceDraw {
public:
	void draw() { std::cout << "Draw point.\n";}
};
class Line : public ShapeInterfaceDraw {
public:
	void draw() { std::cout << "Draw line.\n"; }
};
class Rect : public ShapeInterfaceDraw {
public:
	void draw() { std::cout << "Draw rectangle.\n"; }
};

namespace commercial {

class ShapeInterfaceDisplay {				// Another interface class (commercial?).
public:
	virtual void display()=0;
	virtual ~ShapeInterfaceDisplay() {}
};
class Polygon : public ShapeInterfaceDisplay {
public:
	void display() { std::cout << "Display polygon.\n";}
};
class Torus : public ShapeInterfaceDisplay {
public:
	void display() { std::cout << "Display torus.\n";}
};
class Bezel : public ShapeInterfaceDisplay {
public:
	void display() { std::cout << "Display bezel.\n";}
};

}

namespace adapter_legacy {

void demo() {
	std::vector<ShapeInterfaceDraw*> shapes;
	shapes.push_back(new Point);
	shapes.push_back(new Line);
	shapes.push_back(new Rect);

	for(size_t i=0; i<shapes.size(); i++) {	// Polymorphic client code.
		shapes[i]->draw();
	}

	std::cout << std::endl;
}

}

namespace adapter_problem {

struct Shapes {
	ShapeInterfaceDraw*	draw;
	commercial::ShapeInterfaceDisplay*	display;
	Shapes(
		ShapeInterfaceDraw* draw=0,
		commercial::ShapeInterfaceDisplay* display=0)
		: draw(draw), display(display) {}
};

void demo() {
	std::vector<Shapes*>	shapes;					// Changes to existing code.
	shapes.push_back(new Shapes(new Point));
	shapes.push_back(new Shapes(new Line));
	shapes.push_back(new Shapes(new Rect));
	shapes.push_back(new Shapes(0, new commercial::Polygon));
	shapes.push_back(new Shapes(0, new commercial::Torus));
	shapes.push_back(new Shapes(0, new commercial::Bezel));

	for(size_t i=0; i<shapes.size(); i++) {	// Client code more complicated
		if(shapes[i]->draw)					// because API's differ
			shapes[i]->draw->draw();		// requiring if-else statements,
		else if(shapes[i]->display)			// changes to existing client code,
			shapes[i]->display->display();
		else {
			throw "unknown shape object.";	// and worse; error detection.
		}
	}

	std::cout << std::endl;
}

}

namespace adapter_adapter1{
    // added code
    //    - simple wrapper implementation
    class ShapeDisplayWrapper : public ShapeInterfaceDraw {
    public:
        ShapeDisplayWrapper(commercial::ShapeInterfaceDisplay* pObj) : pDisplayObj(pObj) {};
        ~ShapeDisplayWrapper() { delete pDisplayObj; }
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        virtual void draw() { this->pDisplayObj->display(); }
    };

    // how clients use
    //     - need to handle native shapes and commercial shapes differently
    void demo() {
        std::vector<ShapeInterfaceDraw*> shapes;
        shapes.push_back(new Point);
        shapes.push_back(new Line);
        shapes.push_back(new Rect);
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Polygon));
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Torus));
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Bezel));

        for (size_t i = 0; i<shapes.size(); i++) {	// Polymorphic client code.
            shapes[i]->draw();
        }

        std::cout << std::endl;
    }
}

namespace adapter_adapter2 {
    // added code
    //     - need to have an implementation of each shape reused from commercial
    class Polygon : public ShapeInterfaceDraw{
    public:
        Polygon() : pDisplayObj(new commercial::Polygon){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };

    class Torus : public ShapeInterfaceDraw{
    public:
        Torus() : pDisplayObj(new commercial::Torus){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };

    class Bezel : public ShapeInterfaceDraw{
    public:
        Bezel() : pDisplayObj(new commercial::Bezel){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };


    // how clients use
    //   - uniform interface
    //   - unaware of what's being imported
    void demo() {
        std::vector<ShapeInterfaceDraw*> shapes;
        shapes.push_back(new Point);
        shapes.push_back(new Line);
        shapes.push_back(new Rect);
        shapes.push_back(new Polygon);
        shapes.push_back(new Torus);
        shapes.push_back(new Bezel);

        for (size_t i = 0; i<shapes.size(); i++) {	// Polymorphic client code.
            shapes[i]->draw();
        }

        std::cout << std::endl;
    }

}
#endif /* ADAPTER_H_ */
