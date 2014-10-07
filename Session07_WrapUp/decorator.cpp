#include "sideBySide.h"

namespace side_by_side {







class Decorator {		// If the options are varying...









};





class Option1 : public Decorator {

public:
	Option1(Decorator* decorator) { cout << "  Option1\n"; }



};
class Option2 : public Decorator {

public:
	Option2(Decorator* decorator) { cout << "  Option2\n"; }



};
class Option3 : public Decorator {

public:
	Option3(Decorator* decorator) { cout << "  Option3\n"; }



};









void clientDecorator() {
	Decorator *decorator = new Decorator;
	decorator = new Option1(decorator);
	decorator = new Option2(decorator);
	decorator = new Option3(decorator);



	cout << endl;
}

}
