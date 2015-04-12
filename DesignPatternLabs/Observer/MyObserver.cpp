#include "lab4_problem_observer.h"
#include <set>
#include <vector>

namespace observer {
    // ---------------------------------------------
    class Observer {
    public:
        virtual void udpate() = 0;
    };

    class ThingAdapter : public Observer {
    public:
        ThingAdapter(string name) : _thing(name){};
        virtual void udpate(){ _thing.makesMischief(); }
    private:
        homework::observer_problem::Thing _thing;
    };

    class FishAdapter : public Observer {
    public:
        FishAdapter(){};
        virtual void udpate(){ _fish.complains(); }
    private:
        homework::observer_problem::Fish _fish;
    };

    class ChildAdapter : public Observer {
    public:
        ChildAdapter(string gender) : _child(gender){};
        virtual void udpate(){ _child.hasFun(); }
    private:
        homework::observer_problem::Child _child;
    };

    class MomAdapter : public Observer {
    public:
        MomAdapter(){};
        virtual void udpate(){ _mom.returns(); }
    private:
        homework::observer_problem::Mom _mom;
    };

    // ---------------------------------------------
    class Subject {
    public:
        void attach(Observer* pObj){
            subscribers.insert(pObj);
        }
        void detach(Observer* pObj){
            subscribers.erase(pObj);
        }

        
    protected:
        void notify(){
            for (auto& pObj : subscribers){
                pObj->udpate();
            }
        }
    private:
        set<Observer*> subscribers;
    };

    class CatInTheHat : public Subject{
    public:
        void say(string words){
            cout << "  Cat in the Hat says \"" << words << "\"." << endl;
            this->notify();
        }
        ~CatInTheHat() {
            cout << "  Cat in the hat left: ~Subject.\n";
            cout << endl;
        }
    };

    void demo() {
        CatInTheHat c;
        ThingAdapter* thing1 = new ThingAdapter("1");
        ThingAdapter* thing2 = new ThingAdapter("2");
        FishAdapter*  fish = new FishAdapter;
        ChildAdapter* boy = new ChildAdapter("Boy");
        ChildAdapter* girl = new ChildAdapter("Girl");
        MomAdapter*	  mom = new MomAdapter;

        // Event 1.  attach and detach can be in constructor/destructor
        c.attach(thing1);
        c.attach(thing2);
        c.attach(boy);
        c.attach(girl);
        c.say("Hello");
        cout << endl;

        // Event 2.
        c.detach(thing2);
        delete thing2;
        c.say("let's play");
        cout << endl;

        // Event 3.
        c.attach(fish);
        c.say("rock & roll");
        cout << endl;

        // Cleanup 1.
        c.detach(thing1);
        c.detach(fish);
        c.detach(girl);
        c.detach(boy);
        delete thing1;
        delete fish;
        delete girl;
        delete boy;

        // Event 4.
        c.attach(mom);
        c.say("Goodbye");
        cout << endl;

        delete mom;
    }
}
int main(){
    std::cout << "------ observer_problem demo ------" << std::endl;
    homework::observer_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ observer demo ------" << std::endl;
    observer::demo();
    std::cout << std::endl << std::endl;

}