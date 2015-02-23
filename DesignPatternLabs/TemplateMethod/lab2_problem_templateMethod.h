/*
 * templateMethod.h
 *
 * Desc: Define the skeleton of an algorithm.
 *
 * Category: Behavioral
 *
 *  Created on: May 10, 2014
 *      Author: aldgoff
 *
 *  URLs:
 *  	http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method
 *  	http://www.dofactory.com/net/template-method-design-pattern
 *  	http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter19
 *  	http://sourcemaking.com/design_patterns/template_method
 */

#ifndef TEMPLATEMETHOD_H_
#define TEMPLATEMETHOD_H_
#include <iostream>


namespace home_work {

    /* Consider a 6 step process as implied by the legacy namespace below.
     * Optimization is the only difference between the processes.
     * Consider new specs (ala problem namespace below):
     * 	 Two more processes with different optimizations, critical and npc.
     *   For both of these the cleanup step must be better and different.
     * Refactor using the Template Method design pattern.
     */

    namespace template_method_common {

        bool morning() { return true; }

        void fast() {
            std::cout << "  setup\n";
            std::cout << "  schedule\n";
            if (morning())
                std::cout << "  highHeat\n";
            else
                std::cout << "  lowHeat\n";
            std::cout << "  Fast optimized\n";
            std::cout << "  usual cleanup\n";
            std::cout << "  putaway\n";
            std::cout << std::endl;
        }

        void economic() {
            std::cout << "  setup\n";
            std::cout << "  schedule\n";
            if (morning())
                std::cout << "  highHeat\n";
            else
                std::cout << "  lowHeat\n";
            std::cout << "  Economic optimized\n";
            std::cout << "  usual cleanup\n";
            std::cout << "  putaway\n";
            std::cout << std::endl;
        }

    }

    namespace template_method_new_specs {

        using namespace template_method_common;

        void critical() {
            std::cout << "  setup\n";
            std::cout << "  schedule\n";
            if (morning())
                std::cout << "  highHeat\n";
            else
                std::cout << "  lowHeat\n";
            std::cout << "  Critical optimized\n";
            std::cout << "  meticulous cleanup\n";
            std::cout << "  putaway\n";
            std::cout << std::endl;
        }

        void npc() {
            std::cout << "  setup\n";
            std::cout << "  schedule\n";
            if (morning())
                std::cout << "  highHeat\n";
            else
                std::cout << "  lowHeat\n";
            std::cout << "  NPC optimized\n";
            std::cout << "  meticulous cleanup\n";
            std::cout << "  putaway\n";
            std::cout << std::endl;
        }

    }

    namespace template_method_legacy {

        using namespace template_method_common;

        void demo() {
            fast();
            economic();
        }

    }

    namespace template_method_problem {

        using namespace template_method_common;
        using namespace template_method_new_specs;

        void demo() {
            fast();
            economic();
            critical();
            npc();
        }

    }

}

#endif /* TEMPLATEMETHOD_H_ */
