#include "Rectangle.h"
#include <iostream>
#include <cmath>
#include "easygl.h"
using namespace std;

// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _xlength, float _ylength) 
              : Shape (_name, _colour, _xcen, _ycen) {
    xlength=_xlength;
    ylength=_ylength;
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}

void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: " << xlength << " height: " << ylength << endl;
}


void Rectangle::scale (float scaleFac) {
    xlength=xlength*scaleFac;
    ylength=ylength*scaleFac;
}
   

float Rectangle::computeArea () const {
   float area;
   area=abs(xlength*ylength);
   return area;
}


float Rectangle::computePerimeter () const {
   float perimeter = 0;
   perimeter=2*xlength+2*ylength;
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
   float xcoordleft = getXcen()-xlength/2;
   float xcoordright = getXcen()+xlength/2;
   float ycoordtop = getYcen()+ylength/2;
   float ycoordbottom = getYcen()-ylength/2;
   
   window->gl_setcolor(getColour());
   window->gl_fillrect(xcoordleft, ycoordbottom, xcoordright, ycoordtop);
}


bool Rectangle::pointInside (float x, float y) const {
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   if (click.x >= -xlength/2 && click.x <=xlength/2 && click.y>=-ylength/2 && click.y<=ylength/2) return true;
   else return false;
}
