/* Consider the problem of sending encrypted video streams to
* a variety of display types under different crypto protocols
* with different resolutions and at different frame rates.
* Resolutions are easily modeled as a 2D array of integers
* as are frame rates as a singular integer. However, we
* want to avoid coupling the user class with all the various
* display types and cryptographic protocols, and as usual,
* we want to avoid any combinatorial explosions.
*/

namespace factory_method_problem {

    void send_video(int* res, int frameRate, int display, int protocol);

    class DisplayPort {
    public:
        void send_video(int* res, int frameRate, int protocol) {
            char stream[64];
            sprintf(stream, "  DisplayPort[%d, %d]", res[0], res[1]);
            switch (protocol) {
            case 1:  cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: cout << "  OOPs!\n" << endl;
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
            case 1:  cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: cout << "  OOPs!\n" << endl;
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
            case 1:  cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: cout << "  OOPs!\n" << endl;
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
            case 1:  cout << stream << " via PVP at " << frameRate << " fps.\n";         break;
            case 2:  cout << stream << " via ID1 at " << frameRate << " fps.\n";           break;
            case 3:  cout << stream << " via RSA at " << frameRate << " fps.\n";         break;
                // Seam point - new protocol.
            default: cout << "  OOPs!\n" << endl;
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
        cout << "<< Factory Method problem >>\n";

        int           res[] = { 1920, 1080 };
        int           frameRate = 60;

        for (int display = 1; display <= 4; display++) {
            for (int protocol = 1; protocol <= 3; protocol++) {
                send_video(res, frameRate, display, protocol);
            }
            cout << endl;
        }
    }

}