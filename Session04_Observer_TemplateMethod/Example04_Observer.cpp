#include <list>
using namespace std;

/* Consider the Dr. Seuss children's story, "The Cat in the Hat."
* Whenever the cat in the hat does something, the things, children & fish should respond.
* In the below procedural approach, the Subject class (the cat in the hat) has to know
* about all the other classes. When they get changed, Subject has to be recompiled.
* In addition, Subject is managing multiple objects, of multiple classes, with multiple
* interfaces, which leads to long, hard to follow code.
* Use the Observer pattern to decouple the Subject class from the others.
*
* P.S. The “delete” in event 2 and 3 are not the results of “notify”.   They are just something happened in between “events” affecting # of observers and therefore notification list.
* 
* Bonus question: The order of observers' action could be required to be in exact order of the procedural code, be random, or be the order of registration.  
*                 Implement some variation of the pattern to have the flexibility.
*/

namespace ripples {

class Thing {
                string name;
public:
                Thing(string name) : name(name) {}
                ~Thing() { cout << "  Thing" << name << " leaves.\n"; }
public:
                void makesMischief() {
                                cout << "  Thing" << name << " makes mischief.\n";
                }
};

class Fish {
                string color;
public:
                Fish(string color) : color(color) {}
                ~Fish() { cout << "  ~Fish(" << color << ").\n"; }
public:
                void complains() {
                                cout << "  " << color << " fish complains.\n";
                }
};

class Child {
                string gender;
public:
                Child(string gender) : gender(gender) {}
                ~Child() { cout << "  ~Child(" << gender << ").\n"; }
public:
                void hasFun() {
                                cout << "  " << gender << " has fun.\n";
                }
};

class Subject {
                Thing*  thing1;
                Thing*  thing2;
                Fish*     redFish;
                Fish*     blueFish;
                Child*   boy;
                Child*   girl;
                // Dependency: Subject must know about all kinds of objects.
public:
                Subject() :
                                thing1(new Thing("1")), thing2(new Thing("2")),
                                redFish(new Fish("Red")), blueFish(new Fish("Blue")),
                                boy(new Child("Boy")), girl(new Child("Girl")) { // Dependency: ditto.
                }
                ~Subject() {
                                cout << "  Cat in the hat left: ~Subject.\n";
                                cout << endl;
                }
public:
                void runSim() {
                                // Event 1.
                                thing1->makesMischief();
                                thing2->makesMischief();
                                boy->hasFun();
                                girl->hasFun();

                                // Event 2.
                                delete thing2;
                                thing1->makesMischief();
                                boy->hasFun();
                                girl->hasFun();

                                // Event 3.
                                thing1->makesMischief();
                                boy->hasFun();
                                girl->hasFun();
                                redFish->complains();
                                blueFish->complains();
                                delete thing1;

                                // Cleanup.
                                delete blueFish;
                                delete redFish;
                                delete girl;
                                delete boy;
                }
};

void demo() {
                cout << "<< Observer ripples >>\n";

                Subject catInTheHat;

                catInTheHat.runSim();
}

}
