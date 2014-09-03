/* Consider how to model decision making in a military chain of command.
* Simple decisions get made by the junior officers, harder ones by the senior officers.
*/

namespace decisions {

    class Lieutenant {
    public:
        bool handleRequest(unsigned request) {
            if (request < 10) {
                cout << "Lieutenant - I've got this one(" << request << ").\n";
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
                cout << "Captain - I've got this one(" << request << ").\n";
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
                cout << "Major - I've got this one(" << request << ").\n";
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
                cout << "Colonel - I've got this one(" << request << ").\n";
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
                cout << "General - I've got this one(" << request << ").\n";
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
                cout << "CommanderInChief - I've got this one(" << request << ").\n";
                return true;
            }
            else {
                return false;
            }
        }
    };

    void demo() {
        cout << "<< Chain of Responsibility problem >>\n";

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
                cout << "Request not handled(" << request << ").\n";
            }
        }

        cout << endl;
    }

}
