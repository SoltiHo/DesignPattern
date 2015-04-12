#include "lab5_problem_abstractFactory.h"
// http://stackoverflow.com/questions/5739611/differences-between-abstract-factory-pattern-and-factory-method
#include <vector>
#include <memory>

namespace abstract_factory {
    class Animal {
    public:
        ~Animal(){
            cout << "~Animal" << endl;
        }
        Animal(string n) : name(n) {};
        string Name() { return name; };
    protected:
        string name;
    };

    class Carnivore;
    class Herbivore : public Animal{
    public:
        virtual ~Herbivore(){
            cout << "  ~Herbivore" << endl;
        }
        Herbivore(string n) : Animal(n){};
        virtual void graze() = 0;
        virtual void mate(Herbivore* h) = 0;
        virtual void evade(Carnivore* c) = 0;
    };
    class Carnivore : public Animal{
    public:
        virtual ~Carnivore(){
            cout << "  ~Carnivore" << endl;
        }
        Carnivore(string n) : Animal(n){};
        virtual void eat(Herbivore* h) = 0;
        virtual void mate(Carnivore* c) = 0;
        virtual void hunt() = 0;
    };

    enum Continent {
        NorthAmerica,
        Africa,
        // Seam point - insert another continent, violates open/closed principle.
    };
    string ids[] = {
        "North America",
        "Africa",
        // Seam point - insert another continent, violates open/closed principle.
    };

    // Abstract Factory
    class AbstractFactory {
    public:
        virtual ~AbstractFactory(){
            cout << "~AbstractFactory" << endl;
        }
        virtual Herbivore* createHerbivore() = 0;
        virtual Carnivore* createCarnivore() = 0;
    };

    class AnimalWorld {
    public:
        virtual ~AnimalWorld(){
            cout << "~AnimalWorld" << endl;
        }
        void init(){
            // Factory Method --> buildFactory
            unique_ptr<AbstractFactory> factory = buildFactory();
            pEatee = unique_ptr<Herbivore>(factory->createHerbivore());
            pEater = unique_ptr<Carnivore>(factory->createCarnivore());
        }
        virtual unique_ptr<AbstractFactory> buildFactory() = 0;
        unique_ptr<AbstractFactory> factory;
        unique_ptr<Herbivore> pEatee;
        unique_ptr<Carnivore> pEater;

        virtual void printSlogan() = 0;
        void runFoodChain(){
            printSlogan();
            init();
            this->pEatee->graze();
            this->pEatee->mate(this->pEatee.get());
            this->pEatee->evade(this->pEater.get());
            this->pEater->eat(this->pEatee.get());
            this->pEater->mate(this->pEater.get());
            this->pEater->hunt();
        }
    };



    // -------------- North America -------------- 
    class Bison : public Herbivore{
    public:
        Bison(string n) : Herbivore(n){};
        virtual ~Bison(){
            cout << "    ~Bison" << endl;
        }
        virtual void graze(){
            cout << "  " << name << " eats grass.\n";
        };
        virtual void mate(Herbivore* h){
            cout << "  Mate with " << h->Name() << " herd.\n";
        };
        virtual void evade(Carnivore* c){
            cout << "  Flee from pack of " << c->Name() << "s.\n";
        };
    };
    class Wolf : public Carnivore{
    public:
        Wolf(string n) : Carnivore(n){};
        virtual ~Wolf(){
            cout << "    ~Wolf" << endl;
        }
        virtual void eat(Herbivore* h){
            cout << "  " << name << " eats a " << h->Name() << ".\n";
        };
        virtual void mate(Carnivore* c){
            cout << "  Mate for life with another " << c->Name() << ".\n";
        };
        virtual void hunt(){
            cout << "  Hunt in packs.\n";
        }
    };
    class NorthAmericaFactory : public AbstractFactory {
    public:
        virtual ~NorthAmericaFactory(){
            cout << "  ~NorthAmericaFactory" << endl;
        }
        virtual Herbivore* createHerbivore(){ return new Bison("Bison"); };
        virtual Carnivore* createCarnivore(){ return new Wolf("Wolf"); };
    };
    class NorthAmericaWorld : public AnimalWorld{
    public:
        virtual ~NorthAmericaWorld(){
            cout << "  ~NorthAmericaWorld" << endl;
        }
        virtual unique_ptr<AbstractFactory> buildFactory(){
            return unique_ptr<AbstractFactory>(new NorthAmericaFactory);
        };
        virtual void printSlogan(){
            cout << " " << ids[NorthAmerica] << " Continent:\n";
        }
    };
    // -------------------------------------


    // -------------- Africa -------------- 
    class Wildebeest : public Herbivore{
    public:
        Wildebeest(string n) : Herbivore(n){};
        virtual ~Wildebeest(){
            cout << "    ~Wildebeest" << endl;
        }
        virtual void graze(){
            cout << "  " << name << " eats thrash.\n";
        };
        virtual void mate(Herbivore* h){
            cout << "  Breed with " << h->Name() << ".\n";
        };
        virtual void evade(Carnivore* c){
            cout << "  Flee from " << c->Name() << ".\n";
        };
    };
    class Lion : public Carnivore{
    public:
        Lion(string n) : Carnivore(n){};
        virtual ~Lion(){
            cout << "    ~Lion" << endl;
        }
        virtual void eat(Herbivore* h){
            cout << "  " << name << " eats a " << h->Name() << ".\n";
        };
        virtual void mate(Carnivore* c){
            cout << "  Mate with another " << c->Name() << ".\n";
        };
        virtual void hunt(){
            cout << "  Stalk prey.\n";
        };
    };
    class AfricaFactory : public AbstractFactory {
    public:
        virtual ~AfricaFactory(){
            cout << "  ~AfricaFactory" << endl;
        }
        virtual Herbivore* createHerbivore(){ return new Wildebeest("Wildebeest"); };
        virtual Carnivore* createCarnivore(){ return new Lion("Lion"); };
    };
    class AfricaWorld : public AnimalWorld{
    public:
        virtual ~AfricaWorld(){
            cout << "  ~AfricaWorld" << endl;
        }
        virtual unique_ptr<AbstractFactory> buildFactory(){
            return unique_ptr<AbstractFactory>(new AfricaFactory);
        };
        virtual void printSlogan(){
            cout << " " << ids[Africa] << " Continent:\n";
        }
    };
    // -------------------------------------

    void demo(){
        vector<unique_ptr<AnimalWorld>> worlds;
        worlds.push_back(unique_ptr<AnimalWorld>(new NorthAmericaWorld));
        worlds.push_back(unique_ptr<AnimalWorld>(new AfricaWorld));
        for (auto& w : worlds){
            w->runFoodChain();
            cout << endl;
        }
    }
}

namespace factory_method {
    enum Continent {
        NorthAmerica,
        Africa,
        // Seam point - insert another continent, violates open/closed principle.
    };
    string ids[] = {
        "North America",
        "Africa",
        // Seam point - insert another continent, violates open/closed principle.
    };


    class Animal {
    public:
        ~Animal(){
            cout << "~Animal" << endl;
        }
        Animal(string n) : name(n) {};
        string Name() { return name; };
    protected:
        string name;
    };

    class Carnivore;
    class Herbivore : public Animal{
    public:
        virtual ~Herbivore(){
            cout << "  ~Herbivore" << endl;
        }
        Herbivore(string n) : Animal(n){};
        virtual void graze() = 0;
        virtual void mate(Herbivore* h) = 0;
        virtual void evade(Carnivore* c) = 0;
    };
    class Carnivore : public Animal{
    public:
        virtual ~Carnivore(){
            cout << "  ~Carnivore" << endl;
        }
        Carnivore(string n) : Animal(n){};
        virtual void eat(Herbivore* h) = 0;
        virtual void mate(Carnivore* c) = 0;
        virtual void hunt() = 0;
    };

    class AnimalWorld {
    public:
        virtual ~AnimalWorld(){
            cout << "~AnimalWorld" << endl;
        }
        virtual void printSlogan() = 0;
        virtual Herbivore* createHerbivore() = 0;
        virtual Carnivore* createCarnivore() = 0;
        void runFoodChain(){
            printSlogan();
            unique_ptr<Herbivore> eatee = unique_ptr<Herbivore>(createHerbivore());
            unique_ptr<Carnivore> eater = unique_ptr<Carnivore>(createCarnivore());

            eatee->graze();
            eatee->mate(eatee.get());
            eatee->evade(eater.get());
            eater->eat(eatee.get());
            eater->mate(eater.get());
            eater->hunt();
        }
    };

    // -------------- North America -------------- 
    class Bison : public Herbivore{
    public:
        Bison(string n) : Herbivore(n){};
        virtual ~Bison(){
            cout << "    ~Bison" << endl;
        }
        virtual void graze(){
            cout << "  " << name << " eats grass.\n";
        };
        virtual void mate(Herbivore* h){
            cout << "  Mate with " << h->Name() << " herd.\n";
        };
        virtual void evade(Carnivore* c){
            cout << "  Flee from pack of " << c->Name() << "s.\n";
        };
    };
    class Wolf : public Carnivore{
    public:
        Wolf(string n) : Carnivore(n){};
        virtual ~Wolf(){
            cout << "    ~Wolf" << endl;
        }
        virtual void eat(Herbivore* h){
            cout << "  " << name << " eats a " << h->Name() << ".\n";
        };
        virtual void mate(Carnivore* c){
            cout << "  Mate for life with another " << c->Name() << ".\n";
        };
        virtual void hunt(){
            cout << "  Hunt in packs.\n";
        }
    };
    class NorthAmericaWorld : public AnimalWorld{
    public:
        virtual ~NorthAmericaWorld(){
            cout << "  ~NorthAmericaWorld" << endl;
        }
        virtual void printSlogan(){
            cout << " " << ids[NorthAmerica] << " Continent:\n";
        }
        virtual Herbivore* createHerbivore(){
            return new Bison("Bison");
        }
        virtual Carnivore* createCarnivore(){
            return new Wolf("Wolf");
        }
    };
    // -------------------------------------


    // -------------- Africa -------------- 
    class Wildebeest : public Herbivore{
    public:
        Wildebeest(string n) : Herbivore(n){};
        virtual ~Wildebeest(){
            cout << "    ~Wildebeest" << endl;
        }
        virtual void graze(){
            cout << "  " << name << " eats thrash.\n";
        };
        virtual void mate(Herbivore* h){
            cout << "  Breed with " << h->Name() << ".\n";
        };
        virtual void evade(Carnivore* c){
            cout << "  Flee from " << c->Name() << ".\n";
        };
    };
    class Lion : public Carnivore{
    public:
        Lion(string n) : Carnivore(n){};
        virtual ~Lion(){
            cout << "    ~Lion" << endl;
        }
        virtual void eat(Herbivore* h){
            cout << "  " << name << " eats a " << h->Name() << ".\n";
        };
        virtual void mate(Carnivore* c){
            cout << "  Mate with another " << c->Name() << ".\n";
        };
        virtual void hunt(){
            cout << "  Stalk prey.\n";
        };
    };

    class AfricaWorld : public AnimalWorld{
    public:
        virtual ~AfricaWorld(){
            cout << "  ~AfricaWorld" << endl;
        }
        virtual void printSlogan(){
            cout << " " << ids[Africa] << " Continent:\n";
        }
        virtual Herbivore* createHerbivore(){
            return new Wildebeest("Wildebeest");
        }
        virtual Carnivore* createCarnivore(){
            return new Lion("Lion");
        }

    };
    // -------------------------------------

    void demo(){
        vector<unique_ptr<AnimalWorld>> worlds;
        worlds.push_back(unique_ptr<AnimalWorld>(new NorthAmericaWorld));
        worlds.push_back(unique_ptr<AnimalWorld>(new AfricaWorld));
        for (auto& w : worlds){
            w->runFoodChain();
            cout << endl;
        }
    }
}

void main(){
    std::cout << "------ abstract_factory_problem demo ------" << std::endl;
    homework::abstract_factory_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ abstrac factory demo ------" << std::endl;
    abstract_factory::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ factory method demo ------" << std::endl;
    factory_method::demo();
    std::cout << std::endl << std::endl;
    
}



