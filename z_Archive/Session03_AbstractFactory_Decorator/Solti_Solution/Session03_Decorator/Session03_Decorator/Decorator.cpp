#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <map>

namespace too_many_car_model_options {

    /* Consider options for a car.
    * One might subclass a base class, Car, for each set of options,
    * but then the options code gets duplicated leading to scaling problems,
    * and the options are statically linked.
    * For the 4 classes and 9 options implied by the following procedural code,
    * rewrite with the Decorator pattern to eliminate the combinatorial explosion,
    * reduce duplication, improve code locality, and allow for dynamic linking.
    * Pay particular attention to the problem of memory leaks with this pattern.
    */


    class Car {
    protected:
        std::string str;
    public:
        Car(std::string str="Undefined car") : str(str) {}
        virtual std::string getDesc() {
            return str;
        }
        virtual double getCost()=0;
        virtual ~Car() {
            std::cout << "~Car " << str << "\n";
        }
    };



    class RunAbout : public Car {
    public:
        RunAbout() : Car("RunAbout") {}
        std::string getDesc() {
            std::string desc = str + " with 4 wheels"
                + ", 2 doors"
                ;
            return desc;
        }
        double getCost() {
            double cost = 12000.00
                + 2000.00
                ;
            return cost;
        }
    };

    class SUV : public Car {
    public:
        SUV() : Car("SUV") {}
        std::string getDesc() {
            std::string desc = str + " with 4 wheels"
                + ", 4 doors"
                + ", AC"
                + ", automatic transmission"
                ;
            return desc;
        }
        double getCost() {
            double cost = 12000.00
                + 4000.00
                + 1500.00
                + 3000.00
                ;
            return cost;
        }
    };

    class Status : public Car {
    public:
        Status() : Car("Status") {}
        std::string getDesc() {
            std::string desc = str + " with 4 wheels"
                + ", 4 doors"
                + ", AC"
                + ", premium sound system"
                + ", navigation"
                + ", automatic transmission"
                // Seam: new options scales as the number of car models.
                ;
            return desc;
        }
        double getCost() {
            double cost = 12000.00
                + 4000.00
                + 1500.00
                + 1000.00
                + 2000.00
                + 3000.00
                ;
            return cost;
        }
    };

    class Performance : public Car {
    public:
        Performance() : Car("Performance") {}
        std::string getDesc() {
            std::string desc = str + " with 4 wheels"
                + ", 2 doors"
                + ", AC"
                + ", premium sound system"
                + ", navigation"
                + ", manual transmission"
                + ", V8"
                + ", super-charger"
                ;
            return desc;
        }
        double getCost() {
            double cost = 12000.00
                + 2000.00
                + 1500.00
                + 1000.00
                + 2000.00
                + 2500.00
                + 6000.00
                + 3000.00
                ;
            return cost;
        }
    };
    // Seam: new car models scale as the number of options.

    void demo() {
        std::cout << "<< Hello Decorator Problem >>\n";

        Car* mine  = new RunAbout;
        Car* yours = new SUV;
        Car* hers  = new Status;
        Car* boss  = new Performance;

        Car* ours[] = {mine, yours, hers, boss};

        for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
            std::cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
        }
        std::cout << std::endl;

        for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
            delete ours[i];
        }
        std::cout << std::endl;
    }

}

namespace too_many_car_model_options_withDecorator {
    enum CAR_OPTIONS {
        UNDEFINED = 0,
        RUNABOUT,
        SUV,
        STATUS,
        PERFORMANCE
    };

    enum CAR_SELECTABLES {
        BASE = 0, 
        TWO_DOORS,
        FOUR_DOORS,
        AUTOMATIC_TRANSMISSION,
        MANUAL_TRANSMISSION,
        AC,
        NAVIGATION,
        PREMIUM_SOUND_SYSTEM,
        V8,
        SUPER_CHARGER
    };


    // -------------------------- Component --------------------------
    class Car {
    protected:
        std::string str;
        double value;
        static std::map<CAR_SELECTABLES, double> cost_table;
        // std::map<CAR_SELECTABLES, double> cost_table;
    public:
        Car(CAR_OPTIONS option = UNDEFINED);
        virtual std::string getDesc() {
            return str;
        }
        void createCostTable();
        virtual double getCost() = 0;
        virtual ~Car() {
            std::cout << "~Car " << str << "\n";
        }
    };
    std::map<CAR_SELECTABLES, double> Car::cost_table;

    Car::Car(CAR_OPTIONS option) {
        this->value = 0;
        if(Car::cost_table.empty()){
            // the first car ever
            this->createCostTable();
        }
        switch (option){
        case RUNABOUT:
            this->str = "RunAbout";
            break;

        case SUV:
            this->str = "SUV";
            break;

        case STATUS:
            this->str = "Status";
            break;

        case PERFORMANCE:
            this->str = "Performance";
            break;

        default:
            this->str = "Undefined car";
            break;
        }
    }

    void Car::createCostTable(){
        Car::cost_table[BASE]                   = 12000.0;
        Car::cost_table[TWO_DOORS]              =  2000.0;
        Car::cost_table[FOUR_DOORS]             =  4000.0;
        Car::cost_table[AUTOMATIC_TRANSMISSION] =  3000.0;
        Car::cost_table[MANUAL_TRANSMISSION]    =  2500.0;
        Car::cost_table[AC]                     =  1500.0;
        Car::cost_table[NAVIGATION]             =  2000.0;
        Car::cost_table[PREMIUM_SOUND_SYSTEM]   =  1000.0;
        Car::cost_table[V8]                     =  6000.0;
        Car::cost_table[SUPER_CHARGER]          =  3000.0;
    }

    // -------------------------- Concrete Component --------------------------
    class ConcreteCar : public Car {
    public:
        ConcreteCar(CAR_OPTIONS option = UNDEFINED) : Car(option){};
        virtual double getCost(){
            return this->value + this->cost_table[BASE];
        };
        virtual std::string getDesc(){
            std::string temp;
            temp = this->str + " with 4 wheels";
            return temp;
        };
    };

    // -------------------------- Decorator --------------------------
    class CarDecorator : public Car {
    public:
        CarDecorator() : myTrailer(NULL){};
        CarDecorator(Car* theTrailer) : myTrailer(theTrailer){};
        ~CarDecorator();
        virtual double getCost(){ return 0;};
        virtual std::string getDesc(){ return ""; };
        //virtual double getCost() = 0;
        //virtual std::string getDesc() = 0;

    protected: 
        Car* myTrailer;
    };
    CarDecorator::~CarDecorator(){
        std::cout << "deleting " << this->str << std::endl;
        if(this->myTrailer){
            delete this->myTrailer;
            this->myTrailer = NULL;
        }
    }

    // -------------------------- Concrete Decorator --------------------------
    class Decorator_TwoDoors : public CarDecorator {
    public:
        Decorator_TwoDoors(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_TwoDoors";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[TWO_DOORS];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", 2 doors";
            return temp;
        }
    };
    class Decorator_FourDoors : public CarDecorator {
    public:
        Decorator_FourDoors(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_FourDoors";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[FOUR_DOORS];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", 4 doors";
            return temp;
        }
    };
    class Decorator_AutomaticTransmission : public CarDecorator {
    public:
        Decorator_AutomaticTransmission(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_AutomaticTransmission";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[AUTOMATIC_TRANSMISSION];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", automatic transmission";
            return temp;
        }
    };
    class Decorator_ManualTransmission : public CarDecorator {
    public:
        Decorator_ManualTransmission(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_ManualTransmission";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[MANUAL_TRANSMISSION];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", manual transmission";
            return temp;
        }
    };
    class Decorator_AC : public CarDecorator {
    public:
        Decorator_AC(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_AC";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[AC];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", AC";
            return temp;
        }
    };
    class Decorator_Navigation : public CarDecorator {
    public:
        Decorator_Navigation(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_Navigation";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[NAVIGATION];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", navigation";
            return temp;
        }
    };
    class Decorator_PremiumSoundSystem : public CarDecorator {
    public:
        Decorator_PremiumSoundSystem(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_PremiumSoundSystem";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[PREMIUM_SOUND_SYSTEM];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", premium sound system";
            return temp;
        }
    };
    class Decorator_V8 : public CarDecorator {
    public:
        Decorator_V8(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_V8";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[V8];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", V8";
            return temp;
        }
    };
    class Decorator_SuperCharger : public CarDecorator {
    public:
        Decorator_SuperCharger(Car* trailer) : CarDecorator(trailer) {
            this->str = "Decorator_SuperCharger";
        };
        virtual double getCost(){
            return this->myTrailer->getCost() + this->cost_table[SUPER_CHARGER];
        }
        virtual std::string getDesc(){
            std::string temp;
            temp = this->myTrailer->getDesc() + ", super-charger";
            return temp;
        }
    };
    // -------------------------- Factory --------------------------
    class CarFactory {
    public:
        CarFactory(){};
        ~CarFactory(){
            std::cout << "deleting Car Factory" << std::endl;
        };
        Car* assembleTheCar(CAR_OPTIONS option){
            Car* product = NULL;
            switch (option){
            case RUNABOUT:
                product = new ConcreteCar(RUNABOUT);
                product = new Decorator_TwoDoors(product);
                break;

            case SUV:
                product = new ConcreteCar(SUV);
                product = new Decorator_FourDoors(product);
                product = new Decorator_AC(product);
                product = new Decorator_AutomaticTransmission(product);
                break;

            case STATUS:
                product = new ConcreteCar(STATUS);
                product = new Decorator_FourDoors(product);
                product = new Decorator_AC(product);
                product = new Decorator_PremiumSoundSystem(product);
                product = new Decorator_Navigation(product);
                product = new Decorator_AutomaticTransmission(product);
                break;

            case PERFORMANCE:
                product = new ConcreteCar(PERFORMANCE);
                product = new Decorator_TwoDoors(product);
                product = new Decorator_AC(product);
                product = new Decorator_PremiumSoundSystem(product);
                product = new Decorator_Navigation(product);
                product = new Decorator_ManualTransmission(product);
                product = new Decorator_V8(product);
                product = new Decorator_SuperCharger(product);
                break;

            default:
                break;
            }
            return product;
        }
    };

    void demo(){
        std::cout << "<< Hello Decorator Problem with Decorator >>\n";

        CarFactory factory;
        Car* mine  = factory.assembleTheCar(CAR_OPTIONS::RUNABOUT); // new RunAbout;
        Car* yours = factory.assembleTheCar(CAR_OPTIONS::SUV); // new SUV;
        Car* hers  = factory.assembleTheCar(CAR_OPTIONS::STATUS); // new Status;
        Car* boss  = factory.assembleTheCar(CAR_OPTIONS::PERFORMANCE); // new Performance;

        Car* ours[] = {mine, yours, hers, boss};

        for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
            std::cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
        }
        std::cout << std::endl;

        for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
            delete ours[i];
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

int main(){
    std::cout << "-------- procedural code --------" << std::endl;
    too_many_car_model_options::demo();

    std::cout << "-------- Decorator --------" << std::endl;
    too_many_car_model_options_withDecorator::demo();
    return 0;
}
