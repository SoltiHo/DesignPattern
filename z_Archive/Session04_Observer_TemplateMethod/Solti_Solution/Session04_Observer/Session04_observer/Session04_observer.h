#include <list>
#include <cstdio>
#include <iostream>
#include <string>
#include <set>

/* Consider the Dr. Seuss children's story, "The Cat in the Hat."
* Whenever the cat in the hat does something, the things, children & fish should respond.
* In the below procedural approach, the Subject class (the cat in the hat) has to know
* about all the other classes. When they get changed, Subject has to be recompiled.
* In addition, Subject is managing multiple objects, of multiple classes, with multiple
* interfaces, which leads to long, hard to follow code.
* Use the Observer pattern to decouple the Subject class from the others.
*/

namespace ripples {

    class Thing {
        std::string name;
    public:
        Thing(std::string name) : name(name) {}
        ~Thing() { std::cout << "  Thing" << name << " leaves.\n"; }
    public:
        void makesMischief() {
            std::cout << "  Thing" << name << " makes mischief.\n";
        }
    };

    class Fish {
        std::string color;
    public:
        Fish(std::string color) : color(color) {}
        ~Fish() { std::cout << "  ~Fish(" << color << ").\n"; }
    public:
        void complains() {
            std::cout << "  " << color << " fish complains.\n";
        }
    };

    class Child {
        std::string gender;
    public:
        Child(std::string gender) : gender(gender) {}
        ~Child() { std::cout << "  ~Child(" << gender << ").\n"; }
    public:
        void hasFun() {
            std::cout << "  " << gender << " has fun.\n";
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
            std::cout << "  Cat in the hat left: ~Subject.\n";
            std::cout << std::endl;
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
        std::cout << "<< Observer ripples >>\n";

        Subject catInTheHat;

        catInTheHat.runSim();
    }

}

namespace Solti {
    class Subject;
    class Observer;

    // ---------------------------------- subject abstract ----------------------------------
    class Subject {
    public:
        Subject();
        ~Subject();
        bool attach(Observer* new_subscriber);
        bool detach(Observer* unscriber);
        virtual bool notify(bool Randomly = false);
        bool getState();
        bool setState();
    private:
        std::set<Observer*> _observer_set;
    };


    // ---------------------------------- concrete subject ----------------------------------
    //    ========== Event 1 ==========
    class Event1: public Subject {
    public:
        virtual bool notify(bool Randomly = false);
    };
    bool Event1::notify(bool Randomly){
        std::cout << " *** Event 1 happened ***" << std::endl;
        return Subject::notify(Randomly);
    }
    //    ========== Event 2 ==========
    class Event2: public Subject {
    public:
        virtual bool notify(bool Randomly = false);
    };
    bool Event2::notify(bool Randomly){
        std::cout << " *** Event 2 happened ***" << std::endl;
        return Subject::notify(Randomly);
    }
    //    ========== Event 3 ==========
    class Event3: public Subject {
    public:
        virtual bool notify(bool Randomly = false);
    };
    bool Event3::notify(bool Randomly){
        std::cout << " *** Event 3 happened ***" << std::endl;
        return Subject::notify(Randomly);
    }


    // ---------------------------------- observer abstract ----------------------------------
    class Observer {
    public:
        Observer();
        Observer(Subject* subject);
        ~Observer();
        virtual bool update() = 0;
        bool subscribe(Subject* subject);
        bool unsubscribe(Subject* subject);
    private:
        std::set<Subject*> _subject_set;
    };


    // ---------------------------------- concrete observer ----------------------------------
    class Thing_observer_adapter : public Observer {
    public:
        Thing_observer_adapter(std::string name);
        Thing_observer_adapter(std::string name, Subject* subject);
        //~Thing_observer_adapter();
        bool update();
    private:
        ripples::Thing _thing;
    };


    class Fish_observer_adapter : public Observer {
    public:
        Fish_observer_adapter(std::string color);
        Fish_observer_adapter(std::string color, Subject* subject);
        //~Fish_observer_adapter();
        bool update();
    private:
        ripples::Fish _fish;
    };


    class Child_observer_adapter : public Observer {
    public:
        Child_observer_adapter(std::string gender);
        Child_observer_adapter(std::string gender, Subject* subject);
        //~Child_observer_adapter();
        bool update();
    private:
        ripples::Child _child;
    };


    // ---------------------------------- demo ----------------------------------
    void demo();
}
