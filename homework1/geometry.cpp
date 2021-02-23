#include "geometry.h"
#include <math.h>
#include <iostream>

bool equalsf(float a, float b)
{
    float eps = 0.000001;
    if (a - b < eps)
        return true;
    return false;
}


Point::Point(int x, int y)
{
    x_ = x;
    y_ = y;
}

Point::Point(const Point &other)
{
    setX(other.getX());
    setY(other.getY());
}

float Point::getX() const
{
    return x_;
}

float Point::getY() const
{
    return y_;
}

void Point::setX(float x)
{
    x_ = x;
}

void Point::setY(float y)
{
    y_ = y;
}

bool Point::equals(const Point &other) const
{
    return (getX() == other.getX() && getY() == other.getY());
}

float Point::distance(const Point &other) const
{
    return (sqrt(pow(getX() - other.getX(), 2) + pow(getY() - other.getY(), 2)));
}



PolygonalChain::PolygonalChain(unsigned int n, Point *p)
{
    points_number_ = n;
    for (int i = 0; i < n; i++)
    {
        points_.push_back(p[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain& other)
{
    points_number_ = other.getN();
    for (int i = 0; i < getN(); i++)
    {
        points_.push_back(other.getPoint(i));
    }
}

unsigned int PolygonalChain::getN() const
{
    return points_number_;
}

Point PolygonalChain::getPoint(unsigned int n) const
{
    return points_.at(n);
}

bool PolygonalChain::equals(const PolygonalChain &other) const
{
    if (getN() == other.getN())
    {
        for (int i = 0; i < getN(); i++)
        {
            if (!getPoint(i).equals(other.getPoint(i)))
                return false;
        }
        return true;
    }
    return false;
}

float PolygonalChain::perimeter() const
{
    float perimeter = 0;
    for (int i = 0; i < getN() - 1; i++)
    {
        perimeter += getPoint(i).distance(getPoint(i + 1));
    }
    return perimeter;
}



ClosedPolygonalChain::ClosedPolygonalChain(unsigned int n, Point *p) : PolygonalChain(n, p)
{

}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other) : PolygonalChain(other) {}

float ClosedPolygonalChain::perimeter() const
{
    float perimeter = 0;
    for (int i = 0; i < getN() - 1; i++)
    {
        perimeter += getPoint(i).distance(getPoint(i + 1));
    }
    perimeter += getPoint(getN() - 1).distance(getPoint(0));
    return perimeter;
}



Polygon::Polygon(unsigned int n, Point *p) : ClosedPolygonalChain(n, p)
{

}

Polygon::Polygon(const Polygon& other) : ClosedPolygonalChain(other)
{

}

float Polygon::area() const
{
    float area = 0;

    for (int i = 0; i < getN() - 1; i++)
    {
        area += (getPoint(i).getX() * getPoint(i + 1).getY() - getPoint(i + 1).getX() *
                                                                  getPoint(i).getY());
    }
    area += (getPoint(getN() - 1).getX() * getPoint(0).getY() - getPoint(0).getX() *
                                                                   getPoint(getN() - 1).getY());
    area = ((float)abs(area))/2.0;

    return area;
}



Triangle::Triangle(unsigned int n, Point *p) : Polygon(n, p)
{}

Triangle::Triangle(const Triangle& other) : Polygon(other)
{}

bool Triangle::isRegular() const
{
    float eps = 0.000001;
    float a, b, c;
    a = getPoint(0).distance(getPoint(1));
    b = getPoint(1).distance(getPoint(2));
    c = getPoint(2).distance(getPoint(0));

    if (abs(a - b) < eps && abs(b - c) < eps && abs(c - a) < eps)
        return true;
    return false;
}

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


    if (abs(hyp - sqrtf( pow(leg_1, 2) + pow(leg_2, 2) ) ) < eps)
        return true;
    return false;
}



Trapezoid::Trapezoid(unsigned int n, Point *p) : Polygon(n, p) {}

Trapezoid::Trapezoid(const Trapezoid &other) : Polygon(other) {}

float Trapezoid::height() const
{
    float base_1 = getPoint(1).distance(getPoint(2));
    float base_2 = getPoint(0).distance(getPoint(3));

    return 2*area()/(base_1 + base_2);
}



RegularPolygon::RegularPolygon(unsigned int n, Point *p) : Polygon(n, p)
{}

RegularPolygon::RegularPolygon(const RegularPolygon &other) : Polygon(other) {}