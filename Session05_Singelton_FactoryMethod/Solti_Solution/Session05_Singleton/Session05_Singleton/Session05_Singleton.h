#ifndef SESSION05_SINGLETON_H
#define SESSION05_SINGLETON_H

#include <iostream>

static int resource = 1;

class Singleton {
public:
    static Singleton* retrieveInstance(){
        if (!pSingleton){
            Singleton::pSingleton = new Singleton;
        }
        return Singleton::pSingleton;
    }

    int accessFiniteResource(int id = -1) {
        if (id < 0)
            return resource;
        else {
            resource = id;
            return resource;
        }
    }

private:
    Singleton(){
        std::cout << "  Singleton Construction happens on every call to ctor.\n";
    };
    ~Singleton(){
        std::cout << "  Singleton Deletion happened\n";
    };

    static Singleton* pSingleton;
};
Singleton* Singleton::pSingleton = NULL;





#endif