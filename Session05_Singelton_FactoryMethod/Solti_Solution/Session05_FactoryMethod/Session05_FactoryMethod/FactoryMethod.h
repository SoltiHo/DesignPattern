#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <string>
#include <iostream>

#include <sstream>


enum DISPLAY_TECH {
    DISPLAYPORT = 1,
    HDMI,
    MIPI,
    WIDI
};



class DisplayTechnology {
public:
    static DisplayTechnology* instantiateDisplay(DISPLAY_TECH displayType);

    virtual std::string prepareStream(int* res) = 0;

protected:
    DisplayTechnology(){};
    ~DisplayTechnology(){};
};

class Displayport : public DisplayTechnology {
    virtual std::string prepareStream(int* res);
};
class Hdmi : public DisplayTechnology {
    virtual std::string prepareStream(int* res);
};
class Mipi : public DisplayTechnology {
    virtual std::string prepareStream(int* res);
};
class Widi : public DisplayTechnology {
    virtual std::string prepareStream(int* res);
};


enum ENCRYPTION_PROTOCOL {
    PVP = 1,
    ID1,
    RSA
};

class EncryptionProtocol {
public:
    static EncryptionProtocol* instantiateEncryptionProtocol(ENCRYPTION_PROTOCOL protocol);

    virtual std::string prepareEncryption() = 0;

protected:
    EncryptionProtocol(){};
    ~EncryptionProtocol(){};
};

class Pvp : public EncryptionProtocol {
    virtual std::string prepareEncryption();
};
class Id1 : public EncryptionProtocol {
    virtual std::string prepareEncryption();
};
class Rsa : public EncryptionProtocol {
    virtual std::string prepareEncryption();
};



class EncryptedDisplayFactory {
public:
    static void send_video(int* res, int frameRate, int display, int protocol);
};



#endif