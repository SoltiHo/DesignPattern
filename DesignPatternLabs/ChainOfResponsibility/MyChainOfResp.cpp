#include "lab4_problem_chainOfResponsibility.h"
#include <memory>
namespace ChainOfResponsibility {
    class Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (pSuccessor) {
                pSuccessor->handleRequest(request);
            }
            else{
                return false;
            }
        }

        void addOfficerInChain(Officer* pO){
            if (pSuccessor){
                pSuccessor->addOfficerInChain(pO);
            }
            else{
                pSuccessor = unique_ptr<Officer>(pO);
            }
        }

        virtual ~Officer(){
            cout << "delete Officer" << endl;
        }
    protected:
        unique_ptr<Officer> pSuccessor;
    };

    class Lieutenant : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 10) {
                cout << "Lieutenant - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~Lieutenant(){
            cout << "    delete Lieutenant" << endl;
        }
    };

    class Captain : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 20) {
                cout << "Captain - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~Captain(){
            cout << "    delete Captain" << endl;
        }
    };

    class Major : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 30) {
                cout << "Major - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~Major(){
            cout << "    delete Major" << endl;
        }
    };

    class LieutenantColonel : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 40) {
                cout << "LieutenantColonel - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~LieutenantColonel(){
            cout << "    delete LieutenantColonel" << endl;
        }
    };

    class Colonel : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 50) {
                cout << "Colonel - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~Colonel(){
            cout << "    delete Colonel" << endl;
        }
    };

    class General : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (request < 60) {
                cout << "General - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~General(){
            cout << "    delete General" << endl;
        }
    };

    class CommanderInChief : public Officer {
    public:
        virtual bool handleRequest(unsigned request){
            if (60 <= request) {
                cout << "CommanderInChief - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return Officer::handleRequest(request);
            }
        }

        virtual ~CommanderInChief(){
            cout << "    delete CommanderInChief" << endl;
        }
    };

    void demo(){
        unique_ptr<Officer> pChainHead = unique_ptr<Officer>(new Lieutenant);
        pChainHead->addOfficerInChain(new Captain);
        pChainHead->addOfficerInChain(new Major);
        pChainHead->addOfficerInChain(new LieutenantColonel);
        pChainHead->addOfficerInChain(new Colonel);
        pChainHead->addOfficerInChain(new General);
        pChainHead->addOfficerInChain(new CommanderInChief);

        unsigned requests[] = { 1, 15, 25, 55, 99 };
        for (size_t i = 0; i < sizeof(requests) / sizeof(*requests); i++) {
            pChainHead->handleRequest(requests[i]);
        }

        std::cout << std::endl << std::endl;
    }
}

int main(){
    std::cout << "------ decisions demo ------" << std::endl;
    decisions::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ chain of responsibility demo ------" << std::endl;
    ChainOfResponsibility::demo();
    std::cout << std::endl << std::endl;
    
}