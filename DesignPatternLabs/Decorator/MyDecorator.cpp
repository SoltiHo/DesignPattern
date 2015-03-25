#include "lab3_problem_decorator.h"
#include <sstream>
#include <memory>
namespace decorator{

    // design questions
    //  1. allow an option to reject another?
    //  2. who puts options together?
    //      customer?  need to care about mutual compatibility
    //      car company?  allow one option reject another

    // GoF
    class Car{
    protected:
        string str;
    public:
        Car(string str = "Undefined car") : str(str) {}
        virtual string getDesc() { return str; }
        virtual double getCost(){
            return pWrapee->getCost() + 12000; // base price 12000
        }
        virtual ~Car() {
            cout << "~Car " << str << "\n";
        }

        unique_ptr<Car> pWrapee;
    };

    // Decorators
    class DecoratorWheels : public Car{
        virtual double getCost() = 0;
        DecoratorWheels(int wheelCount = 4){
            stringstream s;
            // install wheels
            s << "with " << wheelCount << " wheels";
            str.append(s.str());
        }
        virtual double getCost(){
            return Car::getCost() + 0; // wheel count doesn't affect price
        }
    }

    class DecoratorDoors : public Car{
        virtual double getCost() = 0;
        DecoratorDoors(int doorCount = 4){
            stringstream s;
            // install wheels
            s << ", " << doorCount << " doors";
            str.append(s.str());
        }
        virtual double getCost(){
            return Car::getCost() + 1000; // wheel count doesn't affect price
        }
    }

    // Product Lines
    class RunAbout : public Car {
    }
    class SUV : public Car {
    }
    class Status : public Car {
    }
    class Performance : public Car {
    }

    void demo(){};
}

int main(){
    std::cout << "------ decorator_problem demo ------" << std::endl;
    homework::decorator_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ decorator demo ------" << std::endl;
    decorator::demo();
    std::cout << std::endl << std::endl;

}