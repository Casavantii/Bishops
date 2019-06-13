/****************************************************************
* File      :   Point.h
* Date      :   February 8th, 2016
* Author    :   Steven Poulin (spoulin15@ubishops.ca)
 *****************************************************************/
#include <iostream>
#include <cstdlib>
using namespace std;
class Point {
    protected:
        double x;
        double y;
        double z;
        Point(Point& p);

    public:
        Point();
        Point(double x, double y, double z);
        ~Point ();

        Point &operator[](int i);
        friend std::istream& a operator >> (std::istream& in, Point& p);
        friend std::ostream& operator << (std::ostream& out, const Point& p);
        double distance(Point& otherPt);
};
