/* Consider the problem of sending encrypted video streams to
* a variety of display types under different crypto protocols
* with different resolutions and at different frame rates.
* Resolutions are easily modeled as a 2D array of integers
* as are frame rates as a singular integer. However, we
* want to avoid coupling the user class with all the various
* display types and cryptographic protocols, and as usual,
* we want to avoid any combinatorial explosions.
*/

#include "FactoryMethod.h"
namespace factory_method_problem {

    void send_video(int* res, int frameRate, int display, int protocol);

    class DisplayPort {
    public:
        void send_video(int* res, int frameRate, int protocol) {
            char stream[64];
            sprintf(stream, "  DisplayPort[%d, %d]", res[0], res[1]);
            switch (protocol) {
            case 1:  std::cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  std::cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  std::cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: std::cout << "  OOPs!\n" << std::endl;
                break;
            }
        }
    };
    class HDMI {
    public:
        void send_video(int* res, int frameRate, int protocol) {
            char stream[64];
            sprintf(stream, "  HDMI[%d, %d]", res[0], res[1]);
            switch (protocol) {
            case 1:  std::cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  std::cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  std::cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: std::cout << "  OOPs!\n" << std::endl;
                break;
            }
        }
    };
    class MIPI {
    public:
        void send_video(int* res, int frameRate, int protocol) {
            char stream[64];
            sprintf(stream, "  MIPI[%d, %d]", res[0], res[1]);
            switch (protocol) {
            case 1:  std::cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  std::cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  std::cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: std::cout << "  OOPs!\n" << std::endl;
                break;
            }
        }
    };
    class Widi {
    public:
        void send_video(int* res, int frameRate, int protocol) {
            char stream[64];
            sprintf(stream, "  Widi[%d, %d]", res[0], res[1]);
            switch (protocol) {
            case 1:  std::cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  std::cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  std::cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: std::cout << "  OOPs!\n" << std::endl;
                break;
            }
        }
    };
    // Seam point - new display technology.

    void send_video(int* res, int frameRate, int display, int protocol)
    {
        switch (display) {
        case 1:  DisplayPort().send_video(res, frameRate, protocol);      break;
        case 2:  HDMI().send_video(res, frameRate, protocol); break;
        case 3:  MIPI().send_video(res, frameRate, protocol);   break;
        case 4:  Widi().send_video(res, frameRate, protocol);    break;
            // Seam point - new display technology.
        default:
            break;
        }
    }

    void demo() {
        std::cout << "<< Factory Method problem >>\n";

        int           res[] = { 1920, 1080 };
        int           frameRate = 60;

        for (int display = 1; display <= 4; display++) {
            for (int protocol = 1; protocol <= 3; protocol++) {
                send_video(res, frameRate, display, protocol);
            }
            std::cout << std::endl;
        }
    }

}


DisplayTechnology* DisplayTechnology::instantiateDisplay(DISPLAY_TECH displayType){
    // template?
    switch (displayType){
    case DISPLAYPORT:
        return new Displayport;
        break;
    case HDMI:
        return new Hdmi;
        break;
    case MIPI:
        return new Mipi;
        break;
    case WIDI:
        return new Widi;
        break;
    default:
        return NULL;
        break;
    }
};


EncryptionProtocol* EncryptionProtocol::instantiateEncryptionProtocol(ENCRYPTION_PROTOCOL protocol){
    switch (protocol) {
    case PVP:
        return new Pvp;
        break;
    case ID1:
        return new Id1;
        break;
    case RSA:
        return new Rsa;
        break;
    default:
        return NULL;
        break;
    }
}

void EncryptedDisplayFactory::send_video(int* res, int frameRate, int display, int protocol){
    // skip all error checking for simple codes

    EncryptionProtocol* encryptionProtocol = EncryptionProtocol::instantiateEncryptionProtocol((ENCRYPTION_PROTOCOL)protocol);
    DisplayTechnology* displayTechnology = DisplayTechnology::instantiateDisplay((DISPLAY_TECH)display);
    std::string stream = displayTechnology->prepareStream(res);
    std::string encryptionName = encryptionProtocol->prepareEncryption();
    std::cout << "  " << stream << "[" << res[0] << ", " << res[1] << "] via " << encryptionName << " at " << frameRate << " fps.\n";
}


std::string Displayport::prepareStream(int* res){
    std::string output = "DisplayPort";
    return output;
}

std::string Hdmi::prepareStream(int* res){
    std::string output = "HDMI";
    return output;
}
std::string Mipi::prepareStream(int* res){
    std::string output = "MIPI";
    return output;
}
std::string Widi::prepareStream(int* res){
    std::string output = "WIDI";
    return output;
}

std::string Pvp::prepareEncryption(){
    std::string output = "PVP";
    return output;
}

std::string Id1::prepareEncryption(){
    std::string output = "ID1";
    return output;
}

std::string Rsa::prepareEncryption(){
    std::string output = "RSA";
    return output;
}

void demoWithFactoryMethod(){
    std::cout << "<< Demot with Factory Method>>\n";

    int           res[] = { 1920, 1080 };
    int           frameRate = 60;

    for (int display = 1; display <= 4; display++) {
        for (int protocol = 1; protocol <= 3; protocol++) {
            EncryptedDisplayFactory::send_video(res, frameRate, display, protocol);
        }
        std::cout << std::endl;
    }

    //something need to be done to recycle resources, otherwise memory leak
}

int main(){
    factory_method_problem::demo();
    demoWithFactoryMethod();
    return 0;
}