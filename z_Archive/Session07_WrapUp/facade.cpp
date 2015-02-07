#include "sideBySide.h"

namespace side_by_side {

class LegacyClass1 {};
class LegacyClass2 {};
class LegacyClass3 {};



class Facade {			// If the API's are varying...
protected:
	LegacyClass1	legacyClass1;
	LegacyClass2	legacyClass2;
	LegacyClass3	legacyClass3;





};





class API1 : public Facade {

public:
	void simpleAPI1() { cout << "  simpleAPI1\n"; }
};



class API2 : public Facade {

public:
	void simpleAPI2() { cout << "  simpleAPI2\n"; }
};



class API3 : public Facade {

public:
	void simpleAPI3() { cout << "  simpleAPI3\n"; }
};












void clientFacade() {
	API1 facade1;	facade1.simpleAPI1();
	API2 facade2;	facade2.simpleAPI2();
	API3 facade3;	facade3.simpleAPI3();




	cout << endl;
}

}
