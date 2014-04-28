#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

namespace problem_scenario {

    /* Each of 3 graphics platforms supplies two 2D drawing primitives, lines and arcs, implemented as functions.
    They can be used to create a variety of shapes, such as rectangles, circles, rounded rectangles, etc.

    Use the bridge pattern to write code that avoids the combinatorial explosion of classes
    and methods which a procedural approach to the problem would entail.
    Show how adding another shape or another platform requires only a linear amount of additional code.

    For extra credit, abstract the coordinate system to cover both Cartesian and polar coordinates <math.h>.

    Below are the 3 pairs of function primitives available for the platforms and
    the equations showing how to use them to draw rectangles and circles.
    It is straight forward to use the primitives to draw
    other shapes such as triangles and rounded rectangles.
    Note, they just print text to the screen, this is an academic exercise.
    */

    void drawLine(double x1, double y1, double x2, double y2) {
        std::cout << "Draw vector line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
    }
    void drawArc(double x1, double y1, double x2, double y2) {
        std::cout << "Draw vector arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
    }

    void draw_line(double x1, double y1, double x2, double y2) {
        std::cout << "Draw raster line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
    }
    void draw_arc(double x1, double y1, double x2, double y2) {
        std::cout << "Draw raster arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
    }

    void draw_a_line(double x1, double y1, double x2, double y2) {
        std::cout << "Draw plotter line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
    }
    void draw_an_arc(double x1, double y1, double x2, double y2) {
        std::cout << "Draw plotter arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
    }

    // Rectangle, draw 4 lines (upper left corner is x1,y1, lower right corner is x2,y2).
    //            draw(x1,y1, x2,y1); draw(x2,y1, x2,y2); draw(x2,y2, x1,y2); draw(x1,y2, x1,y1);
    // Circle, draw 4 arcs (90 degrees, clockwise, center is x,y).
    //            draw(x,y+r, x+r,y); draw(x+r,y, x,y-r); draw(x,y-r, x-r,y); draw(x-r,y, x,y+r);

}



namespace Solti {
    // ------------------------------------------------------ Coordinate system ------------------------------------------------------
    enum COORDINATE_SYSTEM {
        CARTESIAN = 0,
        POLAR
    };



    // ------------------------------------------------------ Drawing implementations ------------------------------------------------------
    enum DRAWING_METHOD_TYPE {
        VECTOR = 0,
        RASTER,
        PLOTTER
    };
    class DrawingMethod {
        // drawing interface	
    public:
        virtual void Line(double x1, double y1, double x2, double y2) = 0;
        virtual void Arc(double x1, double y1, double x2, double y2) = 0;
    };

    class DrawingVector : public DrawingMethod {
        // drawing interface
        virtual void Line(double x1, double y1, double x2, double y2){
            drawLine(x1, y1, x2, y2);
        };
        virtual void Arc(double x1, double y1, double x2, double y2){
            drawArc(x1, y1, x2, y2);
        };

        // original functions
        void drawLine(double x1, double y1, double x2, double y2) {
            std::cout << "Draw vector line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
        }
        void drawArc(double x1, double y1, double x2, double y2) {
            std::cout << "Draw vector arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
        }
    };

    class DrawingRaster : public DrawingMethod {
        // drawing interface
        virtual void Line(double x1, double y1, double x2, double y2){
            draw_line(x1, y1, x2, y2);
        };
        virtual void Arc(double x1, double y1, double x2, double y2){
            draw_arc(x1, y1, x2, y2);
        };

        // original functions
        void draw_line(double x1, double y1, double x2, double y2) {
            std::cout << "Draw raster line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
        }
        void draw_arc(double x1, double y1, double x2, double y2) {
            std::cout << "Draw raster arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
        }
    };

    class DrawingPlotter : public DrawingMethod {
        // drawing interface
        virtual void Line(double x1, double y1, double x2, double y2){
            draw_a_line(x1, y1, x2, y2);
        };
        virtual void Arc(double x1, double y1, double x2, double y2){
            draw_an_arc(x1, y1, x2, y2);
        };

        // original functions
        void draw_a_line(double x1, double y1, double x2, double y2) {
            std::cout << "Draw plotter line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << std::endl;
        }
        void draw_an_arc(double x1, double y1, double x2, double y2) {
            std::cout << "Draw plotter arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << std::endl;
        }
    };

    // ------------------------------------------------------ Objects to draw ------------------------------------------------------
    enum SHAPE_TYPE {
        RECTANGULAR = 0,
        TRIANGLE,
        CIRCLE
    };

    struct point {
        double x;
        double y;
        point():x(0),y(0){};
    };

    class Shape {
    public:
        Shape():pDrawingMachine(NULL){};
        ~Shape(){
            if(this->pDrawingMachine){
                delete this->pDrawingMachine;
                this->pDrawingMachine = NULL;
            }
        };
        virtual void draw() = 0;

        bool init(DRAWING_METHOD_TYPE draw){
            // init drawing type
            switch (draw){
            case VECTOR:
                this->pDrawingMachine = new DrawingVector;
                break;
            case RASTER:
                this->pDrawingMachine = new DrawingRaster;
                break;
            case PLOTTER:
                this->pDrawingMachine = new DrawingPlotter;
                break;
            default:
                std::cout << "invalid drawing type" << std::endl;
                break;
            }

            if(this->pDrawingMachine){
                return true;
            }
            else{
                std::cout << "create drawing object failed" << std::endl;
                return false;
            }
        };
        
        // Contain a drawing object
        DrawingMethod* pDrawingMachine;
    };

    class Rectangular : public Shape {
    public:
        Rectangular();
        Rectangular(point topLeft, point buttomRight):TopLeft(topLeft), BottomRight(buttomRight){
            std::cout << "creating Rectangular, TopLeft = (" << TopLeft.x << ", " << TopLeft.y << "), ButtomRight = (" << BottomRight.x << ", " << BottomRight.y << ")" << std::endl;
        };
        ~Rectangular();

        virtual void draw(){
            std::cout << "Drawing a Rectangular.........." << std::endl;
            this->pDrawingMachine->Line( this->TopLeft.x, this->TopLeft.y, this->BottomRight.x, this->TopLeft.y);
            this->pDrawingMachine->Line( this->BottomRight.x, this->TopLeft.y, this->BottomRight.x, this->BottomRight.y);
            this->pDrawingMachine->Line( this->TopLeft.x, this->BottomRight.y, this->BottomRight.x, this->BottomRight.y);
            this->pDrawingMachine->Line( this->TopLeft.x, this->TopLeft.y, this->TopLeft.x, this->BottomRight.y);
        };

    private:
        // Data to form the shape
        point TopLeft;
        point BottomRight;
    };

    class Triangle : public Shape {
    public:

        Triangle();
        Triangle(point point1, point point2, point point3):pt1(point1),pt2(point2),pt3(point3){
            std::cout << "creating Triangle, point1 = (" << pt1.x << ", " << pt1.y << "), point2 = (" << pt2.x << ", " << pt2.y << "), point3 = (" << pt3.x << ", " << pt3.y <<")" << std::endl;
        };
        ~Triangle();

        virtual void draw(){
            std::cout << "Drawing a Triangle.........." << std::endl;
            this->pDrawingMachine->Line( this->pt1.x, this->pt1.y, this->pt2.x, this->pt2.y);
            this->pDrawingMachine->Line( this->pt3.x, this->pt3.y, this->pt2.x, this->pt2.y);
            this->pDrawingMachine->Line( this->pt1.x, this->pt1.y, this->pt3.x, this->pt3.y);
        };

    private:
        // Data to form the shape
        point pt1;
        point pt2;
        point pt3;
    };

    class Circle : public Shape {
    public:
        Circle():radius(0){};
        Circle(point ctr, double r):center(ctr),radius(r){
            std::cout << "creating Circle, center = (" << center.x << ", " << center.y << "), radius = " << radius << std::endl;
        };
        ~Circle();

        virtual void draw(){
            std::cout << "Drawing a Circle.........." << std::endl;
            this->pDrawingMachine->Arc(this->center.x, this->center.y + this->radius, this->center.x + this->radius, this->center.y);
            this->pDrawingMachine->Arc(this->center.x + this->radius, this->center.y, this->center.x, this->center.y - this->radius);
            this->pDrawingMachine->Arc(this->center.x, this->center.y - this->radius, this->center.x - this->radius, this->center.y);
            this->pDrawingMachine->Arc(this->center.x - this->radius, this->center.y, this->center.x, this->center.y + this->radius);
        };

    private:
        // Data to form the shape
        point center;
        double radius;

    };
}

using namespace Solti;
#define NUM_SHAPE 20

int main(){
    std::srand (time(NULL));
    Shape** shapePointerArray = NULL;
    point pt1, pt2, pt3, pt4;

    shapePointerArray = new Shape*[NUM_SHAPE];
    if(shapePointerArray){
        for(int i = 0; i < NUM_SHAPE; i++){
            switch (SHAPE_TYPE(rand()%3)){
                case RECTANGULAR:
                    pt1.x = double(rand()%100);
                    pt1.y = double(rand()%100);
                    pt2.x = double(rand()%100);
                    pt2.y = double(rand()%100);
                    shapePointerArray[i] = new Rectangular(pt1, pt2);
                    break;
                case TRIANGLE:
                    pt1.x = double(rand()%100);
                    pt1.y = double(rand()%100);
                    pt2.x = double(rand()%100);
                    pt2.y = double(rand()%100);
                    pt3.x = double(rand()%100);
                    pt3.y = double(rand()%100);
                    shapePointerArray[i] = new Triangle(pt1, pt2, pt3);
                    break;
                case CIRCLE:
                    pt1.x = double(rand()%100);
                    pt1.y = double(rand()%100);
                    shapePointerArray[i] = new Circle(pt1, double(rand()%100));
                    break;
                default:
                    std::cout << "invalid type" << std::endl;
                    break;
            }    
        }

        for(int i = 0; i < NUM_SHAPE; i++){
            shapePointerArray[i]->init(DRAWING_METHOD_TYPE(rand()%3));
            shapePointerArray[i]->draw();
        }
    }
    return 0;
}