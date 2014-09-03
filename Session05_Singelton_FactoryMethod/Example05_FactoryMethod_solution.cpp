namespace factory_method {

    class Crypto {
    public:
        static Crypto* makeObject(int selection);
        virtual const char* action() { return "Not a valid selection.\n"; }
        enum { count = 3 };
    public:
        virtual ~Crypto() {}
    };
    class PVP : public Crypto {
    public:
        const char* action() { return "PVP"; }
    };
    class ID1 : public Crypto {
    public:
        const char* action() { return "ID1"; }
    };
    class RSA : public Crypto {
    public:
        const char* action() { return "RSA"; }
    };

    Crypto* Crypto::makeObject(int selection) {
        switch (selection) {
        case 1:  return new PVP;
        case 2:  return new ID1;
        case 3:  return new RSA;
        default:
            cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
            return new Crypto;
        }
    }

    class Display {
    public:
        static Display* makeObject(int selection);
        virtual const char* action() { return "Not a valid selection.\n"; }
        enum { count = 4 };
    public:
        virtual ~Display() {}
    };
    class DisplayPort : public Display {
    public:
        const char* action() { return "DisplayPort"; }
    };
    class HDMI : public Display {
    public:
        const char* action() { return "HDMI"; }
    };
    class MIPI : public Display {
    public:
        const char* action() { return "MIPI"; }
    };
    class Widi : public Display {
    public:
        const char* action() { return "Widi"; }
    };

    Display* Display::makeObject(int selection) {
        switch (selection) {
        case 1:  return new DisplayPort;
        case 2:  return new HDMI;
        case 3:  return new MIPI;
        case 4:  return new Widi;
        default:
            cout << " OOPs, " << selection << " not a valid selection.\n" << endl;
            return new Display;
        }
    }

    void demo() {
        cout << "<< Factory Method solution >>\n";

        int           res[] = { 1920, 1080 };
        int           frameRate = 60;

        vector<Display*>             displays;
        vector<Crypto*>                             protocols;

        for (size_t i = 1; i <= Display::count; i++)
            displays.push_back(Display::makeObject(i));
        for (size_t j = 1; j <= Crypto::count; j++)
            protocols.push_back(Crypto::makeObject(j));

        for (size_t i = 0; i < Display::count; i++) {
            char stream[64];
            sprintf(stream, "  %s[%d, %d]", displays[i]->action(), res[0], res[1]);
            for (size_t j = 0; j < Crypto::count; j++) {
                cout << stream << " via " << protocols[j]->action() << " at " << frameRate << " fps.\n";
            }
            cout << endl;
        }

        for (size_t i = 0; i < Display::count; i++)
            delete displays[i];
        for (size_t j = 0; j < Crypto::count; j++)
            delete protocols[j];

    }

}
