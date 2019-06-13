/****************************************************************
* File      :   Point.c
* Date      :   February 8th, 2016
* Author    :   Steven Poulin (spoulin15@ubishops.ca)
 *****************************************************************/

#include "Point.h"
#include <cstdlib>
using namespace std;
class Point {
    protected:
        double x;
        double y;
        double z;
        Point(Point&);

    public:
        Point();
        Point(double x, double y, double z){
        this.x = x;
        this.y = y;
        this.z = z;
        };
        ~Point (){};

        Point &operator[](int i){
        if( i > maxSize ){
            maxSize = maxSize * 2;
            Point temp[maxSize];
            for (int j=0; j < amount; j++ ){
                temp[i] = p[i];
            }
            p = temp;
          }
          return p[i];
      }

        friend std::istream& operator >> (std::istream& in, Point& p){ // getting the point from the clusters
            char i;
                in >> i;
                in >> x;
                in >> i;
                in >> y;
                in >> i;
                in >> z;
                in >> i;
                return in;
        };
        friend std::ostream& operator << (std::ostream& out, const Point& p)[];
        double distance(Point& otherPt){
            double dist;
            dist = sqrt( (pow((this.x - otherPt.x),2)) + (pow((this.y - otherPt.y),2)) + (pow((this.z - otherPt.z),2)))
            return dist;
        };


};
