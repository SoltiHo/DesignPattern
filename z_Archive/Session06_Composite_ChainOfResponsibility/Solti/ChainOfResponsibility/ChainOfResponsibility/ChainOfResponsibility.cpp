/* Consider how to model decision making in a military chain of command.
* Simple decisions get made by the junior officers, harder ones by the senior officers.
*/

#include <iostream>
namespace decisions {

    class Lieutenant {
    public:
        bool handleRequest(unsigned request) {
            if (request < 10) {
                std::cout << "Lieutenant - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    class Captain {
    public:
        bool handleRequest(unsigned request) {
            if (request < 20) {
                std::cout << "Captain - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    class Major {
    public:
        bool handleRequest(unsigned request) {
            if (request < 30) {
                std::cout << "Major - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    // Seam point: Lieutenant Colonel.

    class Colonel {
    public:
        bool handleRequest(unsigned request) {
            if (request < 50) {
                std::cout << "Colonel - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    class General {
    public:
        bool handleRequest(unsigned request) {
            if (request < 60) {
                std::cout << "General - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    class CommanderInChief {
    public:
        bool handleRequest(unsigned request) {
            if (60 <= request) {
                std::cout << "CommanderInChief - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    void demo() {
        std::cout << "<< Chain of Responsibility problem >>\n";

        Lieutenant    lieutenant;
        Captain              captain;
        Major         major;
        // Seam point: Lieutenant Colonel.
        Colonel              colonel;
        General              general;
        CommanderInChief pres;

        unsigned requests[] = { 1, 15, 25, 55, 99 };

        for (size_t i = 0; i < sizeof(requests) / sizeof(*requests); i++) {
            unsigned request = requests[i];
            if (lieutenant.handleRequest(request))
                ;
            else if (captain.handleRequest(request))
                ;
            else if (major.handleRequest(request))
                ;
            // Seam point: Lieutenant Colonel.
            else if (colonel.handleRequest(request))
                ;
            else if (general.handleRequest(request))
                ;
            else if (pres.handleRequest(request))
                ;
            else {
                std::cout << "Request not handled(" << request << ").\n";
            }
        }

        std::cout << std::endl;
    }

}



namespace ChainOfResponsibility {
    // base class
    class officer {
    public:
        officer* nextInChain;

        virtual void handleRequest(unsigned request){
            if (this->nextInChain){
                this->nextInChain->handleRequest(request);
            }
            else{
                std::cout << "Request not handled(" << request << ").\n";
            }
        }
        void isDirectReportOf(officer* nextLevelCommander){ this->nextInChain = nextLevelCommander; }
        officer() : nextInChain(NULL){};
    };

    // drived class, the handlers
    class Lieutenant : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 10) {
                std::cout << "Lieutenant - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    class Captain : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 20) {
                std::cout << "Captain - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    class Major : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 30) {
                std::cout << "Major - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    // Seam point: Lieutenant Colonel.
    class LieutenantColonel : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 40) {
                std::cout << "Lieutenant Colonel - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    class Colonel : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 50) {
                std::cout << "Colonel - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    class General : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (request < 60) {
                std::cout << "General - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    class CommanderInChief : public officer {
    public:
        virtual void handleRequest(unsigned request) {
            if (60 <= request) {
                std::cout << "CommanderInChief - I've got this one(" << request << ").\n";
            }
            else {
                officer::handleRequest(request);
            }
        }
    };

    void demo() {
        std::cout << "<< Chain of Responsibility solution >>\n";

        Lieutenant        lieutenant;
        Captain           captain;
        Major             major;
        LieutenantColonel lieutenantColonel;
        Colonel           colonel;
        General           general;
        CommanderInChief  pres;

        // establish commanding chain 
        lieutenant.isDirectReportOf(&major);
        //captain.isDirectReportOf(&major);
        major.isDirectReportOf(&lieutenantColonel);
        lieutenantColonel.isDirectReportOf(&colonel);
        colonel.isDirectReportOf(&general);
        general.isDirectReportOf(&pres);
        officer* commandingChainRoot = &lieutenant;

        unsigned requests[] = { 1, 15, 25, 55, 99 };

        for (size_t i = 0; i < sizeof(requests) / sizeof(*requests); i++) {
            unsigned request = requests[i];
            commandingChainRoot->handleRequest(request);
        }
        std::cout << std::endl;
    }

}



int main(){
    decisions::demo();
    ChainOfResponsibility::demo();
    return 0;
}