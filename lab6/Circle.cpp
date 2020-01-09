#include "Circle.h"
#include <iostream>
#include <cmath>
#include "easygl.h"
using namespace std;

// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius) 
              : Shape (_name, _colour, _xcen, _ycen) {
    radius=_radius;
}


Circle::~Circle () {
   // No dynamic memory to delete
}


void Circle::print () const {
   Shape::print();
   cout << "circle radius: " << radius << endl;
}


void Circle::scale (float scaleFac) {
    radius=radius*scaleFac;
}
   

float Circle::computeArea () const {
   float area;
   area=PI*radius*radius;
   return area;
}


float Circle::computePerimeter () const {
   float perimeter = 0;
   perimeter=2*PI*radius;
   return perimeter;
}


void Circle::draw (easygl* window) const {
   float xtemp = getXcen();
   float ytemp = getYcen();
   window->gl_setcolor(getColour());
   window->gl_fillarc(xtemp, ytemp, radius, 0, 360);
}


bool Circle::pointInside (float x, float y) const {
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   if (click.x <= radius && click.y<=radius) return true;
   else return false;
}


