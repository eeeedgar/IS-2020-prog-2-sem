#include "geometry.h"
#include <math.h>



Point& Point::operator=(const Point &other)
{
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}
bool Point::operator==(const Point &other) const
{
    return (x_ == other.x_ && y_ == other.y_);
}

float Point::getX() const
{
    return x_;
}

float Point::getY() const
{
    return y_;
}

void Point::setX(int x)
{
    x_ = x;
}

void Point::setY(int y)
{
    y_ = y;
}

float Point::distance(const Point &other) const
{
    return (sqrt(pow(getX() - other.getX(), 2) + pow(getY() - other.getY(), 2)));
}




PolygonalChain::PolygonalChain(unsigned int n, Point *p)
{
    points_number_ = n;

    for (unsigned int i = 0; i < n; i++)
    {
        points_.push_back(p[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain& other)
{
    points_number_ = other.getN();
    points_.clear();
    //vector has copy constructor

    points_ = other.points_;
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain &other)
{
    //vector has =
    points_number_ = other.points_number_;

    points_ = other.points_;

    return *this;
}

unsigned int PolygonalChain::getN() const
{
    return points_number_;
}

Point PolygonalChain::getPoint(unsigned int n) const
{
    return points_.at(n);
}

//==???
//its not java
bool PolygonalChain::operator==(const PolygonalChain &other) const
{
    if (getN() == other.getN())
    {
        for (unsigned int i = 0; i < getN(); i++)
        {
            if (!(getPoint(i)==other.getPoint(i)))
                return false;
        }
        return true;
    }
    return false;
}

float PolygonalChain::perimeter() const
{
    float perimeter = 0;
    for (unsigned int i = 0; i < getN() - 1; i++)
    {
        perimeter += getPoint(i).distance(getPoint(i + 1));
    }
    return perimeter;
}





float ClosedPolygonalChain::perimeter() const
{
	//copy-paste
    float perimeter = 0;

    perimeter = PolygonalChain::perimeter() + getPoint(getN() - 1).distance(getPoint(0));
    return perimeter;
}

float Polygon::area() const
{
    float area = 0;

    for (unsigned int i = 0; i < getN() - 1; i++)
    {
        area += (getPoint(i).getX() * getPoint(i + 1).getY() - getPoint(i + 1).getX() *
                                                                  getPoint(i).getY());
    }
    area += (getPoint(getN() - 1).getX() * getPoint(0).getY() - getPoint(0).getX() *
                                                                   getPoint(getN() - 1).getY());
    area = ((float)abs(area))/2.0;

    return area;
}




/*
bool Triangle::isRegular() const
{
	//definetelty not here
	//eps const static private
    float eps = 0.000001;
    float a, b, c;
    a = getPoint(0).distance(getPoint(1));
    b = getPoint(1).distance(getPoint(2));
    c = getPoint(2).distance(getPoint(0));

    if (abs(a - b) < eps && abs(b - c) < eps && abs(c - a) < eps)
        return true;
    return false;
}
 */

bool Triangle::hasRightAngle() const
{
    float eps = 0.000001;
    float a, b, c, hyp, leg_1, leg_2;
    a = getPoint(0).distance(getPoint(1));
    b = getPoint(1).distance(getPoint(2));
    c = getPoint(2).distance(getPoint(0));

    if (a > b)
    {
        if (a > c)
        {
            // a - hyp
            hyp = a;
            leg_1 = b;
            leg_2 = c;
        } else {
            // c - hyp
            hyp = c;
            leg_1 = a;
            leg_2 = b;
        }
    }
    else
    {
        if (b > c)
        {
            // b - hyp
            hyp = b;
            leg_1 = a;
            leg_2 = c;
        }
        else
        {
            // c - hyp
            hyp = c;
            leg_1 = b;
            leg_2 = a;
        }
    }

	//in dist u have sqrt, and here u pow it at 2
    if (abs(hyp - sqrtf( pow(leg_1, 2) + pow(leg_2, 2) ) ) < eps)
        return true;
    return false;
}





float Trapezoid::height() const
{
    float base_1 = getPoint(1).distance(getPoint(2));
    float base_2 = getPoint(0).distance(getPoint(3));

    return 2*area()/(base_1 + base_2);
}


//area and perimeter faster


float RegularPolygon::area() const
{
    if (points_number_ > 1) {
        float side = getPoint(0).distance(getPoint(1));

        return (points_number_ * side * side) / (4 * tan(M_PI/points_number_));
    }
    return 0;
}


float RegularPolygon::perimeter() const
{
    if (points_number_ > 1)
    {
        float side = getPoint(0).distance(getPoint(1));
        return points_number_ * side;
    }
    return 0;
}