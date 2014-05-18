#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

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

    class Eatee;
    class Eater;

    class Eater {
    public:
        Eater(const char* givenName):name(givenName){};
        virtual void mate(Eater* other) = 0;
        virtual void hunt() = 0;
        virtual void eat(Eatee* eatee) = 0;
        std::string getName() { return name; }
    protected:
        std::string name;
    };

    class Eatee {
    public:
        Eatee(const char* givenName):name(givenName){};
        virtual void mate(Eatee* other) = 0;
        virtual void graze() = 0;
        virtual void evade(Eater* eater) = 0;
        std::string getName() { return name; }
    protected:
        std::string name;
    };
    // North American animals.
    class Bison;
    class Wolf;

    class Bison : public Eatee {
    public:
        Bison() : Eatee("Bison") {}
        virtual void mate(Eatee* other) { std::cout << "More " << name << "\n"; }
        virtual void graze() { std::cout << "Bigger " << name << "\n"; }
        virtual void evade(Eater* wolf);
    };
    class Wolf : public Eater {
    public:
        Wolf() : Eater("Wolf") {}
        virtual void mate(Eater* other) { std::cout << "More " << name << "\n"; }
        virtual void hunt() { std::cout << "Smaller " << name << "\n"; }
        virtual void eat(Eatee* bison);
    };

    void Bison::evade(Eater* wolf) { std::cout << name << " evades " << wolf->getName() << "\n"; }
    void Wolf::eat(Eatee* bison) { std::cout << name << " eats " << bison->getName() << "\n"; }

    // African animals.
    class Wildebeest;
    class Lion;

    class Wildebeest : public Eatee {
    public:
        Wildebeest() : Eatee("Wildebeest") {}
        virtual void mate(Eatee* other) { std::cout << "More " << name << "\n"; }
        virtual void graze() { std::cout << "Bigger " << name << "\n"; }
        virtual void evade(Eater* lion);
    };
    class Lion : public Eater {
    public:
        Lion() : Eater("Lion") {}
        virtual void mate(Eater* other) { std::cout << "More " << name << "\n"; }
        virtual void hunt() { std::cout << "Smaller " << name << "\n"; }
        virtual void eat(Eatee* wildebeest);
    };

    void Wildebeest::evade(Eater* lion) { std::cout << name << " evades " << lion->getName() << "\n"; }
    void Lion::eat(Eatee* wildebeest) { std::cout << name << " eats " << wildebeest->getName() << "\n"; }

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
        std::cout << "<< Hello Abstract Factory Problem >>\n";

        runFoodChain(NorthAmerica);  std::cout << std::endl;
        runFoodChain(Africa);        std::cout << std::endl;
    }

    // ------------------------------------------------------------------------------------------


    class animal_factory{
    public:
        Eater* instantiate_eater(Continents continent);
        Eatee* instantiate_eatee(Continents continent);
    private:
    };
    Eater* animal_factory::instantiate_eater(Continents continent){
        Eater* pEater = NULL;
        switch(continent) {
        case NorthAmerica:
            pEater = new Wolf;
            break;
        case Africa:
            pEater = new Lion;
            break;
        }
        return pEater;
    };
    Eatee* animal_factory::instantiate_eatee(Continents continent){
        Eatee* pEatee = NULL;
        switch(continent) {
        case NorthAmerica:
            pEatee = new Bison;
            break;
        case Africa:
            pEatee = new Wildebeest;
            break;
        }
        return pEatee;
    };

    class wild_life_simulator_Abstract_Factory{
    public:
        wild_life_simulator_Abstract_Factory();
        ~wild_life_simulator_Abstract_Factory();
        void runFoodChain(Continents continent);
        
    private:
        Eater* pEater;
        Eatee* pEatee;
        animal_factory factory;

        bool instantiate_animal(Continents continent);  //use the factory to generate the animals
    };

    wild_life_simulator_Abstract_Factory::wild_life_simulator_Abstract_Factory():pEater(NULL), pEatee(NULL){};
    wild_life_simulator_Abstract_Factory::~wild_life_simulator_Abstract_Factory(){
        if(this->pEatee){
            delete this->pEatee;
            this->pEatee = NULL;
        }
        if(this->pEater){
            delete this->pEater;
            this->pEater = NULL;
        }
    };
    bool wild_life_simulator_Abstract_Factory::instantiate_animal(Continents continent){
        if(this->pEatee){
            delete this->pEatee;
            this->pEatee = NULL;
        }
        if(this->pEater){
            delete this->pEater;
            this->pEater = NULL;
        }
        this->pEatee = this->factory.instantiate_eatee(continent);
        this->pEater = this->factory.instantiate_eater(continent);
        if((pEatee == NULL) || (pEater == NULL)){
            // failed to create one of the parties 
            return false;
        }
        return true;
    };
    void wild_life_simulator_Abstract_Factory::runFoodChain(Continents continent){
        if(!this->instantiate_animal(continent)){
            std::cout << "something wrong when instantiate animals" << std::endl;
            return;
        }
        this->pEatee->graze();
        this->pEatee->mate(this->pEatee);
        this->pEatee->evade(this->pEater);

        this->pEater->eat(this->pEatee);
        this->pEater->mate(this->pEater);
        this->pEater->hunt();
    };


}

using namespace complicated_relationships;
int main(){
    std::cout << "-------- Simulation from procedural code --------" << std::endl;
    runFoodChain(NorthAmerica);
    runFoodChain(Africa);
    std::cout << std::endl << std::endl << "-------- Simulation from Abstract Factory --------" << std::endl;
    wild_life_simulator_Abstract_Factory simulator;
    simulator.runFoodChain(NorthAmerica);
    simulator.runFoodChain(Africa);
    return 0;
}