namespace bridge {

class CoordSystem {
public:
                virtual ~CoordSystem() {}
                virtual double x()=0;
                virtual double y()=0;
};
class Cartesian : public CoordSystem {
                double  X;
                double  Y;
public:
                Cartesian(double x=0.0, double y=0.0) :X(x), Y(y) {}
                double x() { return X; }
                double y() { return Y; }
};
class Polar : public CoordSystem {
                double  r;
                double  theta;
public:
                Polar(double r=0.0, double theta=0.0) : r(r), theta(theta) {}
                double x() { return r*cos(theta); }
                double y() { return r*sin(theta); }
};
// Seam point, add another coordinate system.

class Platform {
public:
                virtual ~Platform() {}
                virtual void line(double x1, double y1, double x2, double y2)=0;
                virtual void arc(double x1, double y1, double x2, double y2)=0;
};
class Vector : public Platform {
public:
                void line(double x1, double y1, double x2, double y2) {
                                problem_scenario::drawLine(x1,y1, x2,y2);
                }
                void arc(double x1, double y1, double x2, double y2) {
                                problem_scenario::drawArc(x1,y1, x2,y2);
                }
};
class Rastor : public Platform {
public:
                void line(double x1, double y1, double x2, double y2) {
                                problem_scenario::draw_line(x1,y1, x2,y2);
                }
                void arc(double x1, double y1, double x2, double y2) {
                                problem_scenario::draw_arc(x1,y1, x2,y2);
                }
};
class Plotter : public Platform {
public:
                void line(double x1, double y1, double x2, double y2) {
                                problem_scenario::draw_a_line(x1,y1, x2,y2);
                }
                void arc(double x1, double y1, double x2, double y2) {
                                problem_scenario::draw_an_arc(x1,y1, x2,y2);
                }
};
// Seam point, add another platform.

class Shape {
protected:
                CoordSystem* loc;
                Platform*            platform;
public:
                Shape(CoordSystem* pos, Platform* platform) : loc(pos), platform(platform) {}
                virtual ~Shape() {}
                virtual void draw()=0;
};
class Line : public Shape {
                CoordSystem* end;
public:
                Line(CoordSystem* beg, CoordSystem* end, Platform* platform) : Shape(beg, platform), end(end) {}
                void draw() {
                                platform->line(loc->x(),loc->y(), end->x(),end->y());
                }
};
class Rect : public Shape {
                CoordSystem* end;
public:
                Rect(CoordSystem* beg, CoordSystem* end, Platform* platform) : Shape(beg, platform), end(end) {}
                void draw() {
                                // Rectangle algorithm: draw(x1,y1, x2,y1); draw(x2,y1, x2,y2); draw(x2,y2, x1,y2); draw(x1,y2, x1,y1);
                                double x1 = loc->x();
                                double y1 = loc->y();
                                double x2 = end->x();
                                double y2 = end->y();
                                platform->line(x1,y1, x2,y1);
                                platform->line(x2,y1, x2,y2);
                                platform->line(x2,y2, x1,y2);
                                platform->line(x1,y2, x1,y1);
                }
};
class Circle : public Shape {
                double r;
public:
                Circle(CoordSystem* loc, double r, Platform* platform) : Shape(loc, platform), r(r) {}
                void draw() {
                                // Circle algorithm: draw(x,y+r, x+r,y); draw(x+r,y, x,y-r); draw(x,y-r, x-r,y); draw(x-r,y, x,y+r);
                                double x = loc->x();
                                double y = loc->y();
                                platform->arc(x,y+r, x+r,y);
                                platform->arc(x+r,y, x,y-r);
                                platform->arc(x,y-r, x-r,y);
                                platform->arc(x-r,y, x,y+r);
                }
};
// Seam point, add another shape.

void demo() {
                Line        line(new Cartesian(1,2), new Cartesian(3,4), new Vector());                        line.draw();        cout << endl;
                Rect       rect(new Cartesian(1,2), new Polar(3,4),     new Rastor());                            rect.draw();        cout << endl;
                Circle     circle(new Polar(1,2), 20.0,                                                          new Plotter()); circle.draw();     cout << endl;

                cout << "-------------------------------------------------\n" << endl;

                Shape* shapes[] = {
                                new Line(new Cartesian(1,2), new Cartesian(3,4), new Vector()),
                                new Rect(new Cartesian(1,2), new Polar(3,4), new Rastor()),
                                new Circle(new Polar(1,2), 20.0, new Plotter())
                };

                for(size_t i=0; i<sizeof(shapes)/sizeof(Shape*); i++) {
                                shapes[i]->draw();
                                cout << endl;
                }
}

};
