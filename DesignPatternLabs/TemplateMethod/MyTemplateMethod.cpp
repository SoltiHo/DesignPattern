#include "lab2_problem_templateMethod.h"
namespace template_method{
    class StandardFastProcedure {
    public:
        bool morning() { return true; }
        virtual void process(){
            setup();
            schedule();
            setup();
            heat();
            optimize();
            cleanup();
            putaway();
        }
        virtual void setup(){
            std::cout << "  setup\n";
        }
        virtual void schedule(){
            std::cout << "  schedule\n";
        }
        virtual void heat(){
            if (morning())
                std::cout << "  highHeat\n";
            else
                std::cout << "  lowHeat\n";
        }
        virtual void optimize(){
            std::cout << "  Fast optimized\n";
        }
        virtual void cleanup(){
            std::cout << "  usual cleanup\n";
        }
        virtual void putaway(){
            std::cout << "  putaway\n";
            std::cout << std::endl;
        }
    };

    class EconomicProcedure : public StandardFastProcedure{
        virtual void optimize(){
            std::cout << "  Economic optimized\n";
        }
    };

    class CriticalProcedure : public StandardFastProcedure{

        virtual void optimize(){
            std::cout << "  Critical optimized\n";
        }
        virtual void cleanup(){
            std::cout << "  meticulous cleanup\n";
        }
    };

    class NpcProcedure : public CriticalProcedure{
        virtual void optimize(){
            std::cout << "  NPC optimized\n";
        }
    };

    void demo() {
        StandardFastProcedure fast;
        EconomicProcedure eco;
        CriticalProcedure critical;
        NpcProcedure npc;
        fast.process();
        eco.process();
        critical.process();
        npc.process();
    }
}

void main(){
    std::cout << "------ template_method_problem demo ------" << std::endl;
    home_work::template_method_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ template_method demo ------" << std::endl;
    template_method::demo();
    std::cout << std::endl << std::endl;

}