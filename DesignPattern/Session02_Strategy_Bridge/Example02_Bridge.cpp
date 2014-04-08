
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
                cout << "Draw vector line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void drawArc(double x1, double y1, double x2, double y2) {
                cout << "Draw vector arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

void draw_line(double x1, double y1, double x2, double y2) {
                cout << "Draw raster line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void draw_arc(double x1, double y1, double x2, double y2) {
                cout << "Draw raster arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

void draw_a_line(double x1, double y1, double x2, double y2) {
                cout << "Draw plotter line: [" << x1 << "," << y1 << "] [" << x2 << "," << y2 << "]." << endl;
}
void draw_an_arc(double x1, double y1, double x2, double y2) {
                cout << "Draw plotter arc: (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")." << endl;
}

// Rectangle, draw 4 lines (upper left corner is x1,y1, lower right corner is x2,y2).
//            draw(x1,y1, x2,y1); draw(x2,y1, x2,y2); draw(x2,y2, x1,y2); draw(x1,y2, x1,y1);
// Circle, draw 4 arcs (90 degrees, clockwise, center is x,y).
//            draw(x,y+r, x+r,y); draw(x+r,y, x,y-r); draw(x,y-r, x-r,y); draw(x-r,y, x,y+r);

}
