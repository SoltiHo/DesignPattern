/*
 * facade.h
 *
 * Desc: Define a simpler interface to a set of interfaces making them easier to use.
 *
 * Category: Structural
 *
 *  Created on: Mar 8, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Facade
 *  	http://www.dofactory.com/net/facade-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter6
 *  	http://sourcemaking.com/design_patterns/facade
 */

#ifndef FACADE_H_
#define FACADE_H_
#include <iostream>

namespace homework {

    /* Consider a smart house.
     * The interface starts simple but it's a hit in the market place,
     * so new features are added, and new clients.
     * However, most clients only utilize a couple of use cases.
     * Refactor with the Facade pattern to simplify the clients' code.
     */

    namespace facade_common {

        class Alarm {
        public:
            void on() {
                std::cout << "  Alarm on." << std::endl;
            }
            void off() {
                std::cout << "  Alarm off." << std::endl;
            }
        };
        class AC {
        public:
            void on() {
                std::cout << "  AC on." << std::endl;
            }
            void off() {
                std::cout << "  AC off." << std::endl;
            }
        };

    }

    namespace facade_new_specs {

        class TV {
        public:
            void on() {
                std::cout << "  TV on." << std::endl;
            }
            void off() {
                std::cout << "  TV off." << std::endl;
            }
        };
        class Lights {
        public:
            void on() {
                std::cout << "  Lights on." << std::endl;
            }
            void off() {
                std::cout << "  Lights off." << std::endl;
            }
        };
        // ... ad infinitum

    }

    namespace facade_legacy {	// Smart house with large, complicated interface.

        using namespace facade_common;

        void client() {
            Alarm	alarm;
            AC		ac;
            // Seam point 1 - insert new device, violates open/closed principle.

            std::cout << " Leaving...\n";
            alarm.on();
            ac.off();
            // Seam point 2 - insert call to new device, violates open/closed principle.

            std::cout << " Returning...\n";
            alarm.off();
            ac.on();
            // Seam point 3 - insert call to new device, violates open/closed principle.
        }

        void demo() {
            client();

            std::cout << std::endl;
        }

    }

    namespace facade_problem {	// Have to change client code in multiple places.

        using namespace facade_common;
        using namespace facade_new_specs;

        void client1() {
            Alarm	alarm;
            AC		ac;
            TV		tv;
            Lights	lights;
            // Seam point 1 - insert new device, violates open/closed principle.

            std::cout << " Leaving...\n";
            alarm.on();
            ac.off();
            tv.off();
            lights.off();
            // Seam point 2 - insert call to new device, violates open/closed principle.

            std::cout << " Returning...\n";
            alarm.off();
            ac.on();
            tv.on();
            lights.on();
            // Seam point 3 - insert call to new device, violates open/closed principle.
        }

        void client2() {
            Alarm	alarm;
            AC		ac;
            TV		tv;
            Lights	lights;
            // Seam point 1 - insert new device, violates open/closed principle.

            std::cout << " Leaving...\n";
            alarm.on();
            ac.off();
            tv.off();
            lights.off();
            // Seam point 2 - insert call to new device, violates open/closed principle.

            std::cout << " Returning...\n";
            alarm.off();
            ac.on();
            tv.on();
            lights.on();
            // Seam point 3 - insert call to new device, violates open/closed principle.
        }

        void client3() {
            Alarm	alarm;
            AC		ac;
            TV		tv;
            Lights	lights;
            // Seam point 1 - insert new device, violates open/closed principle.

            std::cout << " Leaving...\n";
            alarm.on();
            ac.off();
            tv.off();
            lights.off();
            // Seam point 2 - insert call to new device, violates open/closed principle.

            std::cout << " Returning...\n";
            alarm.off();
            ac.on();
            tv.on();
            lights.on();
            // Seam point 3 - insert call to new device, violates open/closed principle.
        }

        void demo() {
            client1();	std::cout << std::endl;
            client2();	std::cout << std::endl;
            client3();	std::cout << std::endl;
        }

    }

}

#endif /* FACADE_H_ */
