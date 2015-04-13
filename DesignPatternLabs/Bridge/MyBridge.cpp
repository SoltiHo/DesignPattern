#include "lab5_problem_bridge.h"
#include <memory>
#include <vector>

namespace bridge {
    enum PLATFORM {
        VECTOR,
        RASTER,
        // Seam point - insert another enumerated type, violates open/closed.
    };

    class Platform{
    public:
        virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
        virtual void drawArc(double x1, double y1, double x2, double y2) = 0;
        string getPlatformName(){
            return name;
        };
        virtual ~Platform(){
            cout << "~Platform()" << endl;
        }
    protected:
        Platform(string s) : name(s){}
        string name;
    };
    class Vector : public Platform{
    public:
        Vector() : Platform("<vector>"){}
        virtual ~Vector(){
            cout << "~Vector()  ";
        }
        virtual void drawLine(double x1, double y1, double x2, double y2) {
            cout << "    Draw vector line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]\n";
        }
        virtual void drawArc(double x1, double y1, double x2, double y2) {
            cout << "    Draw vector arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")\n";
        }
    };
    class Raster : public Platform{
    public:
        Raster() : Platform("<raster>"){}
        virtual ~Raster(){
            cout << "~Raster()  ";
        }
        virtual void drawLine(double x1, double y1, double x2, double y2) {
            cout << "    Draw Raster line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]\n";
        }
        virtual void drawArc(double x1, double y1, double x2, double y2) {
            cout << "    Draw Raster arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")\n";
        }

    };
    class Plotter : public Platform{
    public:
        Plotter() : Platform("<plotter>"){}
        virtual ~Plotter(){
            cout << "~Plotter()  ";
        }
        virtual void drawLine(double x1, double y1, double x2, double y2) {
            cout << "    Draw Plotter line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]\n";
        }
        virtual void drawArc(double x1, double y1, double x2, double y2) {
            cout << "    Draw Plotter arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")\n";
        }
    };


    class Shape{
    public:
        Shape(Platform* p) : _platform(unique_ptr<Platform>(p)){}
        virtual void draw() = 0;
        virtual ~Shape(){
            cout << "  ~Shape()" << endl;
        }
    protected:
        unique_ptr<Platform> _platform;
    };
    class Rectangle : public Shape {
    public:
        Rectangle(double x1, double y1, double x2, double y2, Platform* p) : x1(x1), y1(y1), x2(x2), y2(y2), Shape(p){}
        virtual ~Rectangle(){
            cout << "~Rectangle()";
        }
        virtual void draw(){
            cout << "  Rectangle.draw(x1,y1, x2,y2)" << _platform->getPlatformName().c_str() << endl;
            _platform->drawLine(x1, y1, x2, y1);
            _platform->drawLine(x2, y1, x2, y2);
            _platform->drawLine(x2, y2, x1, y2);
            _platform->drawLine(x1, y2, x1, y1);
        }
    private:
        double x1;
        double y1;
        double x2;
        double y2;
    };
    class Circle : public Shape {
    public:
        Circle(double x, double y, double radius, Platform* p) : x(x), y(y), r(radius), Shape(p){}
        virtual ~Circle(){
            cout << "~Circle()";
        }
        virtual void draw(){
            cout << "  Circle.draw(x,y, radius)" << _platform->getPlatformName().c_str() << endl;
            _platform->drawLine(x, y + r, x + r, y);
            _platform->drawLine(x + r, y, x, y - r);
            _platform->drawLine(x, y - r, x - r, y);
            _platform->drawLine(x - r, y, x, y + r);
        }
    private:
        double x;
        double y;
        double r;
    };


    void demo(){
        vector<unique_ptr<Shape>> shapes;
        shapes.push_back(unique_ptr<Shape>(new Rectangle(1, 1, 2, 3, new Vector)));
        shapes.push_back(unique_ptr<Shape>(new Rectangle(1, 1, 2, 3, new Raster)));
        shapes.push_back(unique_ptr<Shape>(new Rectangle(1, 1, 2, 3, new Plotter)));
        shapes.push_back(unique_ptr<Shape>(new Circle(4, 4, 1.0, new Vector)));
        shapes.push_back(unique_ptr<Shape>(new Circle(4, 4, 1.0, new Raster)));
        shapes.push_back(unique_ptr<Shape>(new Circle(4, 4, 1.0, new Plotter)));

        for (auto& s : shapes){
            s->draw();
        }
    }
}

void main(){
    std::cout << "------ bridge_problem demo ------" << std::endl;
    homework::bridge_problem::demo();
    std::cout << std::endl << std::endl;

    std::cout << "------ bridge demo ------" << std::endl;
    bridge::demo();
    std::cout << std::endl << std::endl;
}