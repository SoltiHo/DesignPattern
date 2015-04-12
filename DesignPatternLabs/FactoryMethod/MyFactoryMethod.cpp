#include "lab3_problem_factoryMethod.h"
#include <vector>
#include <memory>
namespace factory_method {

    // orthogonal??
    // instantiation in child?
    enum Crypto {
        PVP = 0,
        ID1,
        RSA,
        // Seam point 1 - insert another crypto protocol.
    };
    const char* crypto_names[] = {
        "PVP",
        "ID1",
        "RSA",
        // Seam point 2 - insert another crypto protocol.
    };

    enum Display {
        DISPLAY_PORT,
        HDMI,
        MIPI,
        WIDI,
        // Seam point A - insert another display type.
    };
    const char* display_names[] = {
        "DisplayPort",
        "HDMI",
        "MIPI",
        "Widi",
        // Seam point B - insert another display type.
    };


    // Crypto
    class EncryptionProtocol {
    public:
        static std::unique_ptr<EncryptionProtocol> EncryptionProtocolFactory(Crypto c);
        virtual std::string encrypt() = 0;
        virtual ~EncryptionProtocol(){
            std::cout << "        delete EncryptionProtocol" << std::endl;
        }
    };

    class Pvp : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[PVP];
        }

    public:
        virtual ~Pvp(){
            std::cout << "    delete Pvp" << std::endl;
        }

    };
    class Id1 : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[ID1];
        }

    public:
        virtual ~Id1(){
            std::cout << "    delete Id1" << std::endl;
        }
    };
    class Rsa : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[RSA];
        }

    public:
        virtual ~Rsa(){
            std::cout << "    delete Rsa" << std::endl;
        }
    };
    std::unique_ptr<EncryptionProtocol> EncryptionProtocol::EncryptionProtocolFactory(Crypto c){
        std::unique_ptr<EncryptionProtocol> pObject = NULL;
        switch (c) {
        case PVP:
            pObject = std::unique_ptr<EncryptionProtocol>(new Pvp);
            break;
        case ID1:
            pObject = std::unique_ptr<EncryptionProtocol>(new Id1);
            break;
        case RSA:
            pObject = std::unique_ptr<EncryptionProtocol>(new Rsa);
            break;
        default:
            break;
        }
        return pObject;
    }


    // Display
    class DisplayInterface {
    public:
        static std::unique_ptr<DisplayInterface> DisplayInterfaceFactory(Display d, Crypto c);
        virtual std::string GenerateVideo() = 0;
        void SendVideo(const std::pair<int, int> res, const int framerate){
            std::cout << "  Send " 
                << GenerateVideo() // virtual
                << "[" << res.first << ", " << res.second << "] via "
                << pCrypto->encrypt().c_str() // virtual
                << " at " << framerate << " fps." << std::endl;
        }

        virtual ~DisplayInterface(){
            std::cout << "    delete DisplayInterface" << std::endl;
        }
    protected:
        std::unique_ptr<EncryptionProtocol> pCrypto;
        DisplayInterface(){}

    };

    class DisplayPort : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[DISPLAY_PORT];
        }

        virtual ~DisplayPort(){
            std::cout << "delete Display" << std::endl;
        }
    };
    class Hdmi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[HDMI];
        }

        virtual ~Hdmi(){
            std::cout << "delete Hdmi" << std::endl;
        }
    };
    class Mipi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[MIPI];
        }

        virtual ~Mipi(){
            std::cout << "delete Mipi" << std::endl;
        }
    };
    class Widi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[WIDI];
        }

        virtual ~Widi(){
            std::cout << "delete Widi" << std::endl;
        }
    };
    // Seam point C - add another display type - SOLID.

    std::unique_ptr<DisplayInterface> DisplayInterface::DisplayInterfaceFactory(Display d, Crypto c){
        std::unique_ptr<DisplayInterface> pObject;
        switch (d) {
        case DISPLAY_PORT:
            pObject = std::unique_ptr<DisplayInterface>(new DisplayPort);
            break;
        case HDMI:
            pObject = std::unique_ptr<DisplayInterface>(new Hdmi);
            break;
        case MIPI:
            pObject = std::unique_ptr<DisplayInterface>(new Mipi);
            break;
        case WIDI:
            pObject = std::unique_ptr<DisplayInterface>(new Widi);
            break;
        }

        if (pObject){
            pObject->pCrypto = EncryptionProtocol::EncryptionProtocolFactory(c);
        }

        return pObject;
    }


    // client
    void demo() {
        std::pair<int, int> res = { 1920, 1080 };
        int framerate = 60;
        Display displays[] = { DISPLAY_PORT, HDMI, MIPI, WIDI };
        Crypto cryptos[] = { PVP, ID1, RSA };

        // generate the objects
        std::vector<std::unique_ptr<DisplayInterface>> d;
        for (size_t i = 0; i < sizeof(displays) / sizeof(*displays); i++) {
            for (size_t j = 0; j < sizeof(cryptos) / sizeof(*cryptos); j++) {
                d.push_back(std::unique_ptr<DisplayInterface>(
                    DisplayInterface::DisplayInterfaceFactory(displays[i], cryptos[j])));
            }
        }

        // send video
        int count = 0;
        for (auto& p : d){
            p->SendVideo(res, framerate);
            if (++count == 3){
                std::cout << std::endl;
                count = 0;
            }
        }

        // deletion done by smart pointers

    }
}

namespace factory_method2_ {

    // orthogonal??
    // instantiation in child?
    enum Crypto {
        PVP = 0,
        ID1,
        RSA,
        // Seam point 1 - insert another crypto protocol.
    };
    const char* crypto_names[] = {
        "PVP",
        "ID1",
        "RSA",
        // Seam point 2 - insert another crypto protocol.
    };

    enum Display {
        DISPLAY_PORT,
        HDMI,
        MIPI,
        WIDI,
        // Seam point A - insert another display type.
    };
    const char* display_names[] = {
        "DisplayPort",
        "HDMI",
        "MIPI",
        "Widi",
        // Seam point B - insert another display type.
    };


    // Crypto
    class EncryptionProtocol {
    public:
        static std::unique_ptr<EncryptionProtocol> EncryptionProtocolFactory(Crypto c);
        virtual std::string encrypt() = 0;
        virtual ~EncryptionProtocol(){
            std::cout << "        delete EncryptionProtocol" << std::endl;
        }
    };

    class Pvp : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[PVP];
        }

    public:
        virtual ~Pvp(){
            std::cout << "    delete Pvp" << std::endl;
        }

    };
    class Id1 : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[ID1];
        }

    public:
        virtual ~Id1(){
            std::cout << "    delete Id1" << std::endl;
        }
    };
    class Rsa : public EncryptionProtocol {
        virtual std::string encrypt(){
            return crypto_names[RSA];
        }

    public:
        virtual ~Rsa(){
            std::cout << "    delete Rsa" << std::endl;
        }
    };
    std::unique_ptr<EncryptionProtocol> EncryptionProtocol::EncryptionProtocolFactory(Crypto c){
        std::unique_ptr<EncryptionProtocol> pObject = NULL;
        switch (c) {
        case PVP:
            pObject = std::unique_ptr<EncryptionProtocol>(new Pvp);
            break;
        case ID1:
            pObject = std::unique_ptr<EncryptionProtocol>(new Id1);
            break;
        case RSA:
            pObject = std::unique_ptr<EncryptionProtocol>(new Rsa);
            break;
        default:
            break;
        }
        return pObject;
    }


    // Display
    class DisplayInterface {
    public:
        static std::unique_ptr<DisplayInterface> DisplayInterfaceFactory(Display d, Crypto c);
        virtual std::string GenerateVideo() = 0;
        void SendVideo(const std::pair<int, int> res, const int framerate){
            std::cout << "  Send "
                << GenerateVideo() // virtual
                << "[" << res.first << ", " << res.second << "] via "
                << pCrypto->encrypt().c_str() // virtual
                << " at " << framerate << " fps." << std::endl;
        }

        virtual ~DisplayInterface(){
            std::cout << "    delete DisplayInterface" << std::endl;
        }
    protected:
        std::unique_ptr<EncryptionProtocol> pCrypto;
        DisplayInterface(){}

    };

    class DisplayPort : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[DISPLAY_PORT];
        }

        virtual ~DisplayPort(){
            std::cout << "delete Display" << std::endl;
        }
    };
    class Hdmi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[HDMI];
        }

        virtual ~Hdmi(){
            std::cout << "delete Hdmi" << std::endl;
        }
    };
    class Mipi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[MIPI];
        }

        virtual ~Mipi(){
            std::cout << "delete Mipi" << std::endl;
        }
    };
    class Widi : public DisplayInterface {
        virtual std::string GenerateVideo(){
            return display_names[WIDI];
        }

        virtual ~Widi(){
            std::cout << "delete Widi" << std::endl;
        }
    };
    // Seam point C - add another display type - SOLID.

    std::unique_ptr<DisplayInterface> DisplayInterface::DisplayInterfaceFactory(Display d, Crypto c){
        std::unique_ptr<DisplayInterface> pObject;
        switch (d) {
        case DISPLAY_PORT:
            pObject = std::unique_ptr<DisplayInterface>(new DisplayPort);
            break;
        case HDMI:
            pObject = std::unique_ptr<DisplayInterface>(new Hdmi);
            break;
        case MIPI:
            pObject = std::unique_ptr<DisplayInterface>(new Mipi);
            break;
        case WIDI:
            pObject = std::unique_ptr<DisplayInterface>(new Widi);
            break;
        }

        if (pObject){
            pObject->pCrypto = EncryptionProtocol::EncryptionProtocolFactory(c);
        }

        std::vector<int> testV;
        auto it = testV.begin();
        return pObject;
    }


    // client
    void demo() {
        std::pair<int, int> res = { 1920, 1080 };
        int framerate = 60;
        Display displays[] = { DISPLAY_PORT, HDMI, MIPI, WIDI };
        Crypto cryptos[] = { PVP, ID1, RSA };

        // generate the objects
        std::vector<std::unique_ptr<DisplayInterface>> d;
        for (size_t i = 0; i < sizeof(displays) / sizeof(*displays); i++) {
            for (size_t j = 0; j < sizeof(cryptos) / sizeof(*cryptos); j++) {
                d.push_back(std::unique_ptr<DisplayInterface>(
                    DisplayInterface::DisplayInterfaceFactory(displays[i], cryptos[j])));
            }
        }

        // send video
        int count = 0;
        for (auto& p : d){
            p->SendVideo(res, framerate);
            if (++count == 3){
                std::cout << std::endl;
                count = 0;
            }
        }

        // deletion done by smart pointers

    }
}

int main(){
    std::cout << "------ factory_method_problem demo ------" << std::endl;
    homework::factory_method_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ factory_method demo ------" << std::endl;
    factory_method::demo();
    std::cout << std::endl << std::endl;
}