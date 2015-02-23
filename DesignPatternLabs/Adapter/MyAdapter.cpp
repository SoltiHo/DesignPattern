#include "lab1_problem_adapter.h"

namespace adapter_adapter1{
    // added code
    //    - simple wrapper implementation
    class ShapeDisplayWrapper : public ShapeInterfaceDraw {
    public:
        ShapeDisplayWrapper(commercial::ShapeInterfaceDisplay* pObj) : pDisplayObj(pObj) {};
        ~ShapeDisplayWrapper() { delete pDisplayObj; }
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        virtual void draw() { this->pDisplayObj->display(); }
    };

    // how clients use
    //     - need to handle native shapes and commercial shapes differently
    void demo() {
        std::vector<ShapeInterfaceDraw*> shapes;
        shapes.push_back(new Point);
        shapes.push_back(new Line);
        shapes.push_back(new Rect);
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Polygon));
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Torus));
        shapes.push_back(new ShapeDisplayWrapper(new commercial::Bezel));

        for (size_t i = 0; i < shapes.size(); i++) {	// Polymorphic client code.
            shapes[i]->draw();
        }

        std::cout << std::endl;
    }
}

namespace adapter_adapter2 {
    // added code
    //     - need to have an implementation of each shape reused from commercial
    class Polygon : public ShapeInterfaceDraw{
    public:
        Polygon() : pDisplayObj(new commercial::Polygon){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };

    class Torus : public ShapeInterfaceDraw{
    public:
        Torus() : pDisplayObj(new commercial::Torus){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };

    class Bezel : public ShapeInterfaceDraw{
    public:
        Bezel() : pDisplayObj(new commercial::Bezel){};
        commercial::ShapeInterfaceDisplay* pDisplayObj;
        void draw() { this->pDisplayObj->display(); }
    };


    // how clients use
    //   - uniform interface
    //   - unaware of what's being imported
    void demo() {
        std::vector<ShapeInterfaceDraw*> shapes;
        shapes.push_back(new Point);
        shapes.push_back(new Line);
        shapes.push_back(new Rect);
        shapes.push_back(new Polygon);
        shapes.push_back(new Torus);
        shapes.push_back(new Bezel);

        for (size_t i = 0; i < shapes.size(); i++) {	// Polymorphic client code.
            shapes[i]->draw();
        }

        std::cout << std::endl;
    }

}

namespace adapter_adapter3 {
    // added code
    //     - need to have an implementation of each shape reused from commercial
    class Polygon : public ShapeInterfaceDraw{
    public:
        Polygon() {};
        commercial::Polygon myPolygon;
        void draw() { this->myPolygon.display(); }
    };

    class Torus : public ShapeInterfaceDraw{
    public:
        Torus() {};
        commercial::Torus myTorus;
        void draw() { this->myTorus.display(); }
    };

    class Bezel : public ShapeInterfaceDraw{
    public:
        Bezel() {};
        commercial::Bezel myBezel;
        void draw() { this->myBezel.display(); }
    };


    // how clients use
    //   - uniform interface
    //   - unaware of what's being imported
    //   - no extra layer of pointer
    void demo() {
        std::vector<ShapeInterfaceDraw*> shapes;
        shapes.push_back(new Point);
        shapes.push_back(new Line);
        shapes.push_back(new Rect);
        shapes.push_back(new Polygon);
        shapes.push_back(new Torus);
        shapes.push_back(new Bezel);

        for (size_t i = 0; i < shapes.size(); i++) {	// Polymorphic client code.
            shapes[i]->draw();
        }

        std::cout << std::endl;
    }

}

void main(){
    std::cout << "------ adapter_problem demo ------" << std::endl;
    adapter_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ adapter_adapter1 demo ------" << std::endl;
    adapter_adapter1::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ adapter_adapter2 demo ------" << std::endl;
    adapter_adapter2::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ adapter_adapter3 demo ------" << std::endl;
    adapter_adapter3::demo();
    std::cout << std::endl << std::endl;
}