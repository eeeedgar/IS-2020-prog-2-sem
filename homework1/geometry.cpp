#include "geometry.h"
#include <math.h>

//fixed eps const static private
const double EPS = 1e-9;


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

int Point::getX() const
{
    return x_;
}

int Point::getY() const
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

double Point::distance(const Point &other) const
{
    return (sqrt(distance2(other)));
}

int Point::distance2(const Point &other) const
{
    return pow(getX() - other.getX(), 2) + pow(getY() - other.getY(), 2);
}



PolygonalChain::PolygonalChain(unsigned int n, Point *p)
{
    for (unsigned int i = 0; i < n; i++)
    {
        points_.push_back(p[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain& other)
{
    //fixed vector has =
    points_ = other.points_;
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain &other)
{
    points_ = other.points_;

    return *this;
}

unsigned int PolygonalChain::getN() const
{
    return points_.size();
}

Point PolygonalChain::getPoint(unsigned int n) const
{
    return points_.at(n);
}

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

double PolygonalChain::perimeter() const
{
    double perimeter = 0;
    for (unsigned int i = 0; i < getN() - 1; i++)
    {
        perimeter += getPoint(i).distance(getPoint(i + 1));
    }
    return perimeter;
}



double ClosedPolygonalChain::perimeter() const
{
    return PolygonalChain::perimeter() + getPoint(getN() - 1).distance(getPoint(0));
}



double Polygon::area() const
{
    int area = 0;

    for (unsigned int i = 0; i < getN() - 1; i++)
    {
        area += (getPoint(i).getX() * getPoint(i + 1).getY() - getPoint(i + 1).getX() *
                                                               getPoint(i).getY());
    }
    area += (getPoint(getN() - 1).getX() * getPoint(0).getY() - getPoint(0).getX() *
                                                                getPoint(getN() - 1).getY());

    return (abs(area))/2.0;
}



bool Triangle::hasRightAngle() const
{
    int a_x = getPoint(1).getX() - getPoint(0).getX();
    int a_y = getPoint(1).getY() - getPoint(0).getY();

    int b_x = getPoint(2).getX() - getPoint(1).getX();
    int b_y = getPoint(2).getY() - getPoint(1).getY();

    int c_x = getPoint(0).getX() - getPoint(2).getX();
    int c_y = getPoint(0).getY() - getPoint(2).getY();
	//fixed return expression
    //fixed where are fixed?
    return (a_x * b_y + a_y * b_y == 0 || b_x * c_y + b_y * c_y == 0 || c_x * a_y + c_y * a_y == 0);
}



double Trapezoid::height() const
{
    double base_1 = getPoint(1).distance(getPoint(2));
    double base_2 = getPoint(0).distance(getPoint(3));

    return 2 * area()/(base_1 + base_2);
}


//fixed area and perimeter faster
double RegularPolygon::area() const
{
    if (points_.size() > 2)
    {
        //fixed in dist u have sqrt, and here u pow it at 2
        int side2 = getPoint(0).distance2(getPoint(1));

        return (points_.size() * side2) / (4 * tan(M_PI/points_.size()));
    }
    return 0;
}

double RegularPolygon::perimeter() const
{
    if (points_.size() > 1)
    {
        double side = getPoint(0).distance(getPoint(1));
        return points_.size() * side;
    }
    return 0;
}