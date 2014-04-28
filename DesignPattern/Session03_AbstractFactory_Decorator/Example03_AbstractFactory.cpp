namespace complicated_relationships {

/* Consider a wild life simulation with different animals and continents.
* The major complexity is the relationships between the animals.
* Animals are grouped according to their continent, so the simulation
* runs on a continent by continent basis.
* With a procedural approach, scaling is quadratic.
* The effort to add a relationship scales as the number of continents.
* The effort add a continent scales as the number of relationships.
* Use the Abstract Factory design pattern to reduce coupling,
* enhance cohesion, and avoid quadratic scaling.
*/

enum Continents {
                NorthAmerica,
                Africa,
};

// North American animals.
class Bison;
class Wolf;

class Bison {
                string name;
public:
                Bison() : name("Bison") {}
                string getName() { return name; }
                void mate(Bison* other) { cout << "More " << name << "\n"; }
                void graze() { cout << "Bigger " << name << "\n"; }
                void evade(Wolf* wolf);
};
class Wolf {
                string name;
public:
                Wolf() : name("Wolf") {}
                string getName() { return name; }
                void mate(Wolf* other) { cout << "More " << name << "\n"; }
                void hunt() { cout << "Smaller " << name << "\n"; }
                void eat(Bison* bison);
};

void Bison::evade(Wolf* wolf) { cout << name << " evades " << wolf->getName() << "\n"; }
void Wolf::eat(Bison* bison) { cout << name << " eats " << bison->getName() << "\n"; }

// African animals.
class Wildebeest;
class Lion;

class Wildebeest {
                string name;
public:
                Wildebeest() : name("Wildebeest") {}
                string getName() { return name; }
                void mate(Wildebeest* other) { cout << "More " << name << "\n"; }
                void graze() { cout << "Bigger " << name << "\n"; }
                void evade(Lion* lion);
};
class Lion {
                string name;
public:
                Lion() : name("Lion") {}
                string getName() { return name; }
                void mate(Lion* other) { cout << "More " << name << "\n"; }
                void hunt() { cout << "Smaller " << name << "\n"; }
                void eat(Wildebeest* wildebeest);
};

void Wildebeest::evade(Lion* lion) { cout << name << " evades " << lion->getName() << "\n"; }
void Lion::eat(Wildebeest* wildebeest) { cout << name << " eats " << wildebeest->getName() << "\n"; }

void runFoodChain(Continents continent) {
                Wolf*    wolf = 0;
                Bison*  bison = 0;
                Lion*                     lion = 0;
                Wildebeest*      wildebeest = 0;

                switch(continent) {
                case NorthAmerica:
                                wolf = new Wolf;
                                bison = new Bison;
                                bison->graze();
                                bison->mate(bison);
                                bison->evade(wolf);
                                wolf->eat(bison);
                                wolf->mate(wolf);
                                wolf->hunt();
                                // Seam - new relationship, scales as number of continents.
                                break;
                case Africa:
                                lion = new Lion;
                                wildebeest = new Wildebeest;
                                wildebeest->graze();
                                wildebeest->mate(wildebeest);
                                wildebeest->evade(lion);
                                lion->eat(wildebeest);
                                lion->mate(lion);
                                lion->hunt();
                                break;
                // Seam - new continent, scales as number of relationships.
                }
}

void demo() {
                cout << "<< Hello Abstract Factory Problem >>\n";

                runFoodChain(NorthAmerica);  cout << endl;
                runFoodChain(Africa);                   cout << endl;
}

}
