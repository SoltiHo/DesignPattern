<< Problem Set 1 - Jargon: Match the description to the design pattern. >>

1) _____ Facade              A) Provide an interface for creating families of related objects w / o specifying their concrete classes.

2) _____ Adapter             B) Adapt interfaces so classes can work together polymorphically.

3) _____ Strategy            C) Decouples an abstraction from its implementations so they can vary independently.

4) _____ Bridge              D) Dynamically attach additional responsibilities to an object.

5) _____ AbstractFactory     E) Define a simpler interface to a set of interfaces making them easier to use.

6) _____ Decorator           F) Instantiates a subclass object with the parent class's type.

7) _____ Observer            G) Notify observers automatically.

8) _____ TemplateMethod      H) Insure only one instance of an object exists.

9) _____ Singleton           I) Define a family of interchangeable algorithms which can vary independently from the clients.

10) _____ FactoryMethod       J) Define the skeleton of an algorithm.


<< Problem Set 2 - Taxonomy: What category(Structural, Behavioral, Creational) are these design patterns ? >>

1) ______________  Adapter

2) ______________  Strategy

3) ______________  Bridge

4) ______________  AbstractFactory

5) ______________  Decorator

6) ______________  Observer

7) ______________  TemplateMethod

8) ______________  Singleton

9) ______________  FactoryMethod


<< Problem Set 3 - Principles: Which of the SWE principles below apply specifically to design patterns ? >>

1)  4) _________  Open - closed principle

2) 13) _________  YAGNI(you ain't gonna need it)

3)  3) _________  Design from context

4) 10) _________  Coding standards

5)  7) _________  Commonality and variability analysis

6)  6) _________  Encapsulate what varies

7)  9) _________  Test driven development

8) 12) _________  Coupling and cohesion

9) 11) _________  Refactoring

10)  8) _________  A named approach for solving a design problem

11)  2) _________  Work from the outermost context

12)  5) _________  Dependency inversion principle

13)  1) _________  The form of each part derives from its context in the larger whole


<< Problem Set 4 - Recognition: Identify the design pattern in each code example. >>

4.1) ________________  DomainSpecificName

4.2) ________________  DrSeuss

4.3) ________________  DeadlySins

namespace section_4_1 {

    class DomainSpecificName {
    public:
        virtual void draw() {}
        virtual void calc() {}
        // ...
        virtual void diff() {}
    public:
        virtual ~DomainSpecificName() {}
    };
    class SomethingElse {
    public:
        virtual void display() {}
        virtual void compute() {}
        // ...
        virtual void subtract() {}
    public:
        virtual ~SomethingElse() {}
    };
    class Section_4_1 : public DomainSpecificName {
        SomethingElse dsn;
    public:
        void draw() { dsn.display(); }
        void calc() { dsn.compute(); }
        // ...
        void diff() { dsn.subtract(); }
    };

    string clientCode(DomainSpecificName* object) {
        object->draw();
        object->calc();
        // ...
        object->diff();
        return "DomainSpecificName";
    }

}

namespace section_4_2 {

    class DrSeuss {
    public:
        virtual ~DrSeuss() {}
    protected:
        virtual void sam() {}
        virtual void iam() {}
        virtual void dont() {}
        virtual void like() {}
        virtual void ham() {}
    public:
        void run() {
            sam();
            iam();
            dont();
            like();
            ham();
        }
    };
    class OneFish : public DrSeuss {
    public:
        void iam() {}
    };
    class TwoFish : public DrSeuss {
    public:
        void sam() {}
        void ham() {}
    };
    class RedFish : public DrSeuss {
    public:
        void dont() {}
        void like() {}
    };
    class BlueFish : public DrSeuss {
    public:
        void ham() {}
        void dont() {}
        void sam() {}
    };

    string clientCode(DrSeuss* wonderful) {
        wonderful->run();
        return "DrSeuss";
    }

}

namespace section_4_3 {

    class DeadlySins {
    public:
        virtual ~DeadlySins() {}
    public:
        virtual void cleverCompute() {}
    };
    class waste : public DeadlySins {
    public:
        void cleverCompute() {}
    };
    class haste : public DeadlySins {
    public:
        void cleverCompute() {}
    };
    class sloth : public DeadlySins {
    public:
        void cleverCompute() {}
    };
    class lust : public DeadlySins {
    public:
        void cleverCompute() {}
    };

    string clientCode(DeadlySins* greed) {
        greed->cleverCompute();
        return "DeadlySins";
    }

}


<< Problem Set 5 - Application: Which design pattern should be applied to correct the problematic code example below ? >>

5.1) _________________  Cool Hand Luke

namespace section_5_1 {

    enum Sym {
        orbit,
        gum,
        rubber
    };

    class Cool;
    class Hand;
    class Luke;

    class Cool {
    public:
        void comm(Hand* hand) {}
        void escape() { cout << "  Luke escapes.\n"; }
    };
    class Hand {
    public:
        void talk(Luke* luke) {}
        void chase(Luke* luke) {}
        void problem(Luke* luke, Cool* cool) {}
    };
    class Luke {
    public:
        void listen(Cool* cool, Hand* hand) {}
    };

    class One;
    class Two;
    class Ten;

    class One {
    public:
        void comm(Two* two) {}
        void escape() { cout << "  One escapes.\n"; }
    };
    class Two {
    public:
        void talk(Ten* ten) {}
        void chase(Ten* ten) {}
        void problem(Ten* ten, One* one) {}
    };
    class Ten {
    public:
        void listen(One* one, Two* two) {}
    };

    class Alpha;
    class Beta;
    class Gamma;

    class Alpha {
    public:
        void comm(Beta* beta) {}
        void escape() { cout << "  Alpha escapes.\n"; }
    };
    class Beta  {
    public:
        void talk(Gamma* gamma) {}
        void chase(Gamma* gamma) {}
        void problem(Gamma* gamma, Alpha* alpha) {}
    };
    class Gamma {
    public:
        void listen(Alpha* alpha, Beta* beta) {}
    };

    string clientCode(Sym sym) {
        Cool* cool = 0;
        Hand* hand = 0;
        Luke* luke = 0;

        One* one = 0;
        Two* two = 0;
        Ten* ten = 0;

        Alpha* alpha = 0;
        Beta*  beta = 0;
        Gamma* gamma = 0;

        switch (sym) {
        case orbit:
            cool = new Cool;
            hand = new Hand;
            luke = new Luke;
            cool->comm(hand);
            hand->talk(luke);
            luke->listen(cool, hand);
            hand->problem(luke, cool);
            cool->escape();
            hand->chase(luke);
            break;
        case gum:
            one = new One;
            two = new Two;
            ten = new Ten;
            one->comm(two);
            two->talk(ten);
            ten->listen(one, two);
            two->problem(ten, one);
            one->escape();
            two->chase(ten);
            break;
        case rubber:
            alpha = new Alpha;
            beta = new Beta;
            gamma = new Gamma;
            alpha->comm(beta);
            beta->talk(gamma);
            gamma->listen(alpha, beta);
            beta->problem(gamma, alpha);
            alpha->escape();
            beta->chase(gamma);
            break;
        }

        return "clientCode";
    }

}

