#include "lab2_problem_facade.h"
namespace facade_facade { 

    using namespace homework::facade_common;
    using namespace homework::facade_new_specs;

    class SmartHouse {
        Alarm   alarm;
        AC		ac;
        TV		tv;
        Lights	lights;

    public:
        void leaveHouse(){
            std::cout << " Leaving...\n";
            alarm.on();
            ac.off();
            tv.off();
            lights.off();
        }

        void returnHouse(){
            std::cout << " Returning...\n";
            alarm.off();
            ac.on();
            tv.on();
            lights.on();
        }
    };


    void client1() {
        SmartHouse house1;
        house1.leaveHouse();
        house1.returnHouse();
    }

    void client2() {
        SmartHouse house2;
        house2.leaveHouse();
        house2.returnHouse();
    }

    void client3() {
        SmartHouse house3;
        house3.leaveHouse();
        house3.returnHouse();
    }

    void demo() {
        client1();	std::cout << std::endl;
        client2();	std::cout << std::endl;
        client3();	std::cout << std::endl;
    }

}

void main(){
    std::cout << "------ facade_legacy demo ------" << std::endl;
    homework::facade_legacy::demo();
    std::cout << "------ facade_problem demo ------" << std::endl;
    homework::facade_problem::demo();
    std::cout << "------ facade_facade demo ------" << std::endl;
    facade_facade::demo();
}