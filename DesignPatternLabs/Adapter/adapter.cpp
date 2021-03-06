/*
 * adapter.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: aldgoff
 */

#include <iostream>
using namespace std;

#define COUNT(x) (sizeof(x)/sizeof(*x))

namespace skeleton {

class LegacyClass1 {
public:
	void func1(...) { std::cout << "Func 1.\n"; }
	void func2(...) { std::cout << "Func 2.\n"; }
	// ...
	void funcX(...) { std::cout << "Func X.\n"; }
};
class LegacyClass2 {
public:
	void routine1(...) { std::cout << "Routine 1.\n"; }
	void routine2(...) { std::cout << "Routine 2.\n"; }
	// ...
	void routineY(...) { std::cout << "Routine Y.\n"; }
};
class LegacyClass3 {
public:
	void sub1(...) { std::cout << "Sub 1.\n"; }
	void sub2(...) { std::cout << "Sub 2.\n"; }
	// ...
	void subZ(...) { std::cout << "Sub Z.\n"; }
};

class Adapter {			// If the interfaces are varying...
public:	virtual ~Adapter() {}
public:
	virtual void method1() {}
	virtual void method2() {}
	// ...
	virtual void methodN() {}
};

class Interface1 : public Adapter {
	LegacyClass1	legacyClass1;
public:
	void method1() { std::cout << "  Interface1::method1() - "; legacyClass1.func1(); }
	void method2() { std::cout << "  Interface1::method2() - "; legacyClass1.func2(); }
	// ...
	void methodN() { std::cout << "  Interface1::methodN() - "; legacyClass1.funcX(); }
};
class Interface2 : public Adapter {
	LegacyClass2	legacyClass2;
public:
	void method1() { std::cout << "  Interface2::method1() - "; legacyClass2.routine1(); }
	void method2() { std::cout << "  Interface2::method2() - "; legacyClass2.routine2(); }
	// ...
	void methodN() { std::cout << "  Interface2::methodN() - "; legacyClass2.routineY(); }
};
class Interface3 : public Adapter {
	LegacyClass3	legacyClass3;
public:
	void method1() { std::cout << "  Interface3::method1() - "; legacyClass3.sub1(); }
	void method2() { std::cout << "  Interface3::method2() - "; legacyClass3.sub2(); }
	// ...
	void methodN() { std::cout << "  Interface3::methodN() - "; legacyClass3.subZ(); }
};

void clientAdapter() {
	std::cout << "Adapter\n";
	Adapter* interfaces[] = { new Interface1, new Interface2, new Interface3 };
	for(size_t i=0; i<COUNT(interfaces); i++) {
		interfaces[i]->method1();
		interfaces[i]->method2();
		// ...
		interfaces[i]->methodN();
	}
	std::cout << std::endl;
}

}
