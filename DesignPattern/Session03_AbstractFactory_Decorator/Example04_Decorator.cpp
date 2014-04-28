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
        string str;
public:
        Car(string str="Undefined car") : str(str) {}
        virtual string getDesc() {
                return str;
        }
        virtual double getCost()=0;
        virtual ~Car() {
                cout << "~Car " << str << "\n";
        }
};



class RunAbout : public Car {
public:
                RunAbout() : Car("RunAbout") {}
                string getDesc() {
                                string desc = str + " with 4 wheels"
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
                string getDesc() {
                                string desc = str + " with 4 wheels"
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
                string getDesc() {
                                string desc = str + " with 4 wheels"
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
                string getDesc() {
                                string desc = str + " with 4 wheels"
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
                cout << "<< Hello Decorator Problem >>\n";

                Car* mine  = new RunAbout;
                Car* yours = new SUV;
                Car* hers  = new Status;
                Car* boss  = new Performance;

                Car* ours[] = {mine, yours, hers, boss};

                for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
                                cout << ours[i]->getDesc() << " costs $" << ours[i]->getCost() << ".\n";
                }
                cout << endl;

                for(size_t i=0; i<sizeof(ours)/sizeof(Car*); i++) {
                                delete ours[i];
                }
                cout << endl;
}

}
