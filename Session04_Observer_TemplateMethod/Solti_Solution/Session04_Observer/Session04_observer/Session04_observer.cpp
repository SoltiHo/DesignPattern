#include "Session04_observer.h"
#include <algorithm>
#include <vector>
using namespace Solti;


// ---------------------------------- subject abstract ----------------------------------
Subject::Subject(){
    Subject::_observer_set.clear();
}
Solti::Subject::~Subject(){
    if(!this->_observer_set.empty()){
        std::set<Observer*>::iterator it;
        for(it = this->_observer_set.begin(); it != this->_observer_set.end(); ++it){
            (*it)->unsubscribe(this);
        }
        this->_observer_set.clear();
    }
}
bool Solti::Subject::attach(Observer* new_subscriber){
    if(new_subscriber){
        this->_observer_set.insert(new_subscriber);
        new_subscriber->subscribe(this);
        return true;
    }
    else{
        return false;
    }
}
bool Subject::detach(Observer* unscriber){
    this->_observer_set.erase(unscriber);
    //unscriber->unsubscribe(this);  // can't do this because it's changing size of the set, so that can't use iterator to loop
    return true;
}
bool Subject::notify(bool Randomly){
    if(Randomly){
        // notify observers in a random order
        std::set<Observer*>::iterator it_observer;
        std::vector<Observer*> observer_vector;
        for(it_observer = this->_observer_set.begin(); it_observer != this->_observer_set.end(); ++it_observer){
            observer_vector.insert(observer_vector.begin(),(*it_observer));
        }
        std::random_shuffle(observer_vector.begin(), observer_vector.end());

        std::vector<Observer*>::iterator it_observer_vector;
        for(it_observer_vector = observer_vector.begin(); it_observer_vector != observer_vector.end(); ++it_observer_vector){
            (*it_observer_vector)->update();
        }
    }
    else{
        // notify observers in the order of registration
        std::set<Observer*>::iterator it;
        for(it = this->_observer_set.begin(); it != this->_observer_set.end(); ++it){
            (*it)->update();
        }
    }
    return true;
}


// ---------------------------------- observer abstract ----------------------------------
Observer::Observer(){
    _subject_set.clear();
}
Observer::Observer(Subject* subject){
    _subject_set.clear();
    if(subject){
        this->_subject_set.insert(subject);
        subject->attach(this);
    }
}
Observer::~Observer(){
    if(!this->_subject_set.empty()){
        std::set<Subject*>::iterator it;
        for(it = this->_subject_set.begin(); it != this->_subject_set.end(); ++it){
            (*it)->detach(this);
        }
        this->_subject_set.clear();
    }
}
bool Observer::subscribe(Subject* subject){
    this->_subject_set.insert(subject);
    return true;
}
bool Observer::unsubscribe(Subject* subject){
    this->_subject_set.erase(subject);
    return true;
}


// ---------------------------------- concrete observer ----------------------------------
Thing_observer_adapter::Thing_observer_adapter(std::string name) : _thing(name){
}
Thing_observer_adapter::Thing_observer_adapter(std::string name, Subject* subject) : Observer(subject), _thing(name){
}
bool Thing_observer_adapter::update(){
    this->_thing.makesMischief();
    return true;
}

Fish_observer_adapter::Fish_observer_adapter(std::string color) : _fish(color){
}
Fish_observer_adapter::Fish_observer_adapter(std::string color, Subject* subject) : Observer(subject), _fish(color){
}
bool Fish_observer_adapter::update(){
    this->_fish.complains();
    return true;
}

Child_observer_adapter::Child_observer_adapter(std::string gender) : _child(gender){
}
Child_observer_adapter::Child_observer_adapter(std::string gender, Subject* subject) : Observer(subject), _child(gender){
}
bool Child_observer_adapter::update(){
    this->_child.hasFun();
    return true;
}



// ---------------------------------- demo ----------------------------------
void Solti::demo(){
    // instantiate the subject
    Event1 event1;
    Event2 event2;
    Event3 event3;

    // instantiate observers and attach to one of the subjects of interest
    //                      pThing1     pThing2     pFish_red     pFish_blue     pChild_boy     pChild_girl
    //          event1         O           O                                        O               O
    //          event2         O                                                    O               O
    //          event3         O                        O             O             O               O
    Thing_observer_adapter* pThing1 = NULL;
    Thing_observer_adapter* pThing2 = NULL;
    Fish_observer_adapter* pFish_red = NULL;
    Fish_observer_adapter* pFish_blue = NULL;
    Child_observer_adapter* pChild_boy = NULL;
    Child_observer_adapter* pChild_girl = NULL;

    pThing1 = new Thing_observer_adapter("1", &event1);
    pThing2 = new Thing_observer_adapter("2", &event1);
    pFish_red = new Fish_observer_adapter("Red", &event3);
    pFish_blue = new Fish_observer_adapter("Blue", &event3);
    pChild_boy = new Child_observer_adapter("Boy", &event1);
    pChild_girl = new Child_observer_adapter("Girl", &event1);
    
    // attach to more subjects of interest that are not attached in constructors
    event2.attach(pThing1);
    event2.attach(pChild_boy);
    event2.attach(pChild_girl);

    event3.attach(pThing1);
    event3.attach(pChild_boy);
    event3.attach(pChild_girl);

    // Subject notify event happened
    std::cout << std::endl << " =========== with everyone ===========" << std::endl;
    event1.notify();
    event2.notify();
    event3.notify();

    // if some observers quit or created??
    //      I. observers' destructor automatically detach() --> observers need to maintain list of subjects, and subject need to 
    //         be instantiated before potential observers.  (should make sense..  we have iphone and then iphone users.)
    //     II. control outside of observer and subject --> manually in main() detach the observer from all subjects associated.
    
    // someone quits
    std::cout << std::endl << std::endl << " =========== Thing1 quits ===========" << std::endl;
    delete pThing1;
    pThing1 = NULL;
    event1.notify();
    event2.notify();
    event3.notify();

    // someone new join
    std::cout << std::endl << std::endl << " =========== gold fish join ===========" << std::endl;
    Fish_observer_adapter* pFish_gold = new Fish_observer_adapter("Gold", &event3);
    event2.attach(pFish_gold);
    event1.attach(pFish_gold);
    event1.notify();
    event2.notify();
    event3.notify();

    // if observers need to have different operation for different type of events?
    //      I. different sets of subject-observer? like SportNews-SportSubscriber, EconomicsNews-EconomicsSubscriber, ...etc. ?

    // if the order of observers' action need to be random, or order of registration, or specified at runtime?
    std::cout << std::endl << std::endl << " =========== notify randomly 1 ===========" << std::endl;
    event1.notify(true);
    event2.notify(true);
    event3.notify(true);
    std::cout << std::endl << std::endl << " =========== notify randomly 2 ===========" << std::endl;
    event1.notify(true);
    event2.notify(true);
    event3.notify(true);

};

int main(){
    std::cout << "------------------------------- procedural method -------------------------------" << std::endl;
    ripples::demo();
    std::cout << std::endl << "------------------------------- observer pattern -------------------------------" << std::endl;
    Solti::demo();
    return 0;
}