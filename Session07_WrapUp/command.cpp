#include "sideBySide.h"

namespace side_by_side {

class Receiver1 { public: void comply() { cout << "receiver 1\n"; } };
class Receiver2 { public: void comply() { cout << "receiver 2\n"; } };
class Receiver3 { public: void comply() { cout << "receiver 3\n"; } };



class Command {			// If the requests are varying...


public: virtual ~Command() {}
public:
	virtual void execute() {}




};





class Request1 : public Command {
	Receiver1*	rec;
public:
	void execute() { cout << "  Request action 1 on ";
	rec->comply(); }
public:
	Request1(Receiver1* rec) : rec(rec) {}
};
class Request2 : public Command {
	Receiver2*	rec;
public:
	void execute() { cout << "  Request action 2 on ";
	rec->comply(); }
public:
	Request2(Receiver2* rec) : rec(rec) {}
};
class Request3 : public Command {
	Receiver3*	rec;
public:
	void execute() { cout << "  Request action 3 on ";
	rec->comply(); }
public:
	Request3(Receiver3* rec) : rec(rec) {}
};









void clientCommand() {
	Command* commands[] = { new Request1(new Receiver1), new Request2(new Receiver2), new Request3(new Receiver3)};
	for(size_t i=0; i<COUNT(commands); i++) {
		commands[i]->execute();



	}
	cout << endl;
}

}
