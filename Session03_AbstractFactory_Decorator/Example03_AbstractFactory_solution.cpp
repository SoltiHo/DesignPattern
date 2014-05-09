namespace abstract_factory_3 {

class Herbivore;
class Carnivore;

class Herbivore {
                string name;
public:
                Herbivore(string name) : name(name) {}
                virtual ~Herbivore() {}
                string getName() { return name; }
                void mate(Herbivore* other) { cout << "More " << name << "\n"; }
                void graze() { cout << "Bigger " << name << "\n"; }
                void evade(Carnivore* carnivore);
};
class Bison : public Herbivore {
public:
                Bison() : Herbivore("Bison") {}
};
class Wildebeest : public Herbivore {
public:
                Wildebeest() : Herbivore("Wildebeest") {}
};

class Carnivore {
                string name;
public:
                Carnivore(string name) : name(name) {}
                virtual ~Carnivore() {}
                string getName() { return name; }
                void mate(Carnivore* other) { cout << "More " << name << "\n"; }
                void hunt() { cout << "Smaller " << name << "\n"; }
                void eat(Herbivore* herbivore);
};
class Wolf : public Carnivore {
public:
                Wolf() : Carnivore("Wolf") {}
};
class Lion : public Carnivore {
public:
                Lion() : Carnivore("Lion") {}
};

void Herbivore::evade(Carnivore* carnivore) { cout << name << " evades " << carnivore->getName() << "\n"; }
void Carnivore::eat(Herbivore* herbivore) { cout << name << " eats " << herbivore->getName() << "\n"; }

class ContinentFactory {
public:
                enum Continents {
                                NorthAmericaID,
                                AfricaID,
                };
public:
                static ContinentFactory* newContinent(Continents continentID);
                virtual ~ContinentFactory() {}
                virtual Herbivore* createHerbivore()=0;
                virtual Carnivore* createCarnivore()=0;
};
class NorthAmerica : public ContinentFactory {
public:
                Herbivore* createHerbivore() { return new Bison; }
                Carnivore* createCarnivore() { return new Wolf; }
};
class Africa : public ContinentFactory {
public:
                Herbivore* createHerbivore() { return new Wildebeest; }
                Carnivore* createCarnivore() { return new Lion; }
};

ContinentFactory* ContinentFactory::newContinent(Continents continentID) {
                switch(continentID) {
                case NorthAmericaID: return new NorthAmerica;
                case AfricaID:                     return new Africa;
                };
                throw "oops";
}

class AnimalWorld {
                Herbivore* herbivore;
                Carnivore* carnivore;
public:
                AnimalWorld(ContinentFactory::Continents continentID) {
                                ContinentFactory* continent = ContinentFactory::newContinent(continentID);
                                herbivore = continent->createHerbivore();
                                carnivore = continent->createCarnivore();
                }
                void runFoodChain() {
                                herbivore->graze();
                                herbivore->mate(herbivore);
                                herbivore->evade(carnivore);
                                carnivore->eat(herbivore);
                                carnivore->mate(carnivore);
                                carnivore->hunt();
                }
};

void demo() {
                cout << "<< Hello Abstract Factory Solution >>\n";

                AnimalWorld(ContinentFactory::NorthAmericaID).runFoodChain();         cout << endl;
                AnimalWorld(ContinentFactory::AfricaID).runFoodChain();                                          cout << endl;
}

}
