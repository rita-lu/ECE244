#include "Polygon.h"
#include <iostream>
#include <cmath>
#include "easygl.h"
using namespace std;

Polygon::Polygon (string _name, string _colour, float _xcen, float _ycen,
            int _numsides, float xcoords[100], float ycoords[100]) 
              : Shape (_name, _colour, _xcen, _ycen) {
    
    numsides=_numsides;
   for (int i = 0; i < numsides; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}

Polygon::~Polygon () {
   // No dynamic memory to delete
}

void Polygon::print () const {
   Shape::print();
   cout << "polygon";
   for (int i = 0; i < numsides; i++) {
      cout << " (" << getXcen() + relVertex[i].x << "," << getYcen() + relVertex[i].y << ")";
   }
   cout << endl;
}

void Polygon::scale (float scaleFac) {
   for (int i = 0; i < numsides; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   

float Polygon::computeArea () const {
   float area=0;
   int j=numsides-1;
   for (int i=0; i<numsides; i++){
       area=area + (relVertex[j].x+relVertex[i].x) * (relVertex[j].y-relVertex[i].y);
       j=i;
   }
   return abs(area/2);
}


float Polygon::computePerimeter () const {
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   
   for (int i = 0; i < numsides; i++) {
      endIndex = (i + 1) % numsides;
      dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}


void Polygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[numsides];  // This data type is in easygl_constants.h
   for (int i = 0; i < numsides; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, numsides);
}


bool Polygon::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   // The test is that a horizontal line (ray) from x = -infinity to the click point
   // will cross (intersect) only one side of triangle to the left of the 
   // click point.  If the point is above or below the triangle, the ray will not
   // intersect any triangle sides. If the point is to the left of the triangle
   // the ray will also not intersect any sides to the left of the point.
   // If the point is to the right of the triangle, the ray will intersect
   // two sides of the triangle to its left. Only if the point is inside the 
   // triangle will the ray intersect exactly one side to the left of the point.
   
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;
   
   for (int istart = 0; istart < numsides; istart++) {
      endIndex = (istart + 1) % numsides; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (relVertex[istart], relVertex[endIndex]);
      yDistance = (click.y - relVertex[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }
      
      // We intersect this side if the distance (scaling) along the side vector to 
      // get to our "click" y point is between 0 and 1.  Count the first 
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later 
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = relVertex[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x ) 
             sidesToLeft++;
      }
   }
   
   return (sidesToLeft == 1);
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}