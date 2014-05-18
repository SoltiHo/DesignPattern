namespace observer {

class Observer;
class Subject;

class Subject {
                list<Observer*>               observers;
public:
                ~Subject();
public:
                void attach(Observer* obs) { observers.push_back(obs); }
                void detach(Observer* obs) { observers.remove(obs); }
                void notify();
                void getState() {}
                void setState() {}
};

class Observer {
                Subject& subject;
public:
                Observer(Subject& subject) : subject(subject) {
                                subject.attach(this);
                }
                virtual ~Observer() {
                                subject.detach(this);
                                cout << " ~Observer.\n";
                }
public:
                virtual void update(Subject* subject=0)=0;
};
class Thing : public Observer {
                string     name;
public:
                Thing(string name, Subject& subject) : Observer(subject), name(name) {}
                ~Thing() { cout << "  Thing" << name << " leaves:"; }
public:
                void update(Subject* subject) {
                                cout << "  Thing" << name << " makes mischief.\n";
                }
};
class Fish : public Observer {
                string color;
public:
                Fish(string color, Subject& subject) : Observer(subject), color(color) {}
                ~Fish() { cout << "  ~Fish(" << color << "):"; }
public:
                void update(Subject* subject) {
                                cout << "  " << color << " fish complains.\n";
                }
};
class Child : public Observer {
                string gender;
public:
                Child(string gender, Subject& subject) : Observer(subject), gender(gender) {}
                ~Child() { cout << "  ~Child(" << gender << "):"; }
public:
                void update(Subject* subject) {
                                cout << "  " << gender << " has fun.\n";
                }
};

void Subject::notify() {
                list<Observer*>::iterator it;
                for(it=observers.begin(); it!=observers.end(); it++) {
                                (*it)->update();
                }
}
Subject::~Subject() {
                cout << "  Observers left to notify (should be zero) = " << observers.size() << ".\n";
                cout << "  Cat in the hat left: ~Subject.\n";
                cout << endl;
}

void demo_deprecated() {
                cout << "<< Observer solution >>\n";

                Subject catInTheHat;

                Thing thing1("1", catInTheHat);
                Child boy("Boy", catInTheHat);
                Child girl("Girl", catInTheHat);
                {
                                Thing thing2("2", catInTheHat);

                                catInTheHat.notify();
                }
                catInTheHat.notify();

                Fish redFish("Red", catInTheHat);
                Fish blueFish("Blue", catInTheHat);
                catInTheHat.notify();
}

void demo() {
                cout << "<< Observer solution >>\n";

                Subject catInTheHat;

                // Event 2.
                Observer* thing1 = new Thing("1", catInTheHat);
                Observer* thing2 = new Thing("2", catInTheHat);
                Child boy("Boy", catInTheHat);
                Child girl("Girl", catInTheHat);
                catInTheHat.notify();

                // Event 1.
                delete thing2;
                catInTheHat.notify();

                // Event 3.
                Fish redFish("Red", catInTheHat);
                Fish blueFish("Blue", catInTheHat);
                catInTheHat.notify();

                // Cleanup.
                delete thing1;
}

}

