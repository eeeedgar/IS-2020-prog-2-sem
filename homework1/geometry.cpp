#include "geometry.h"
#include <math.h>

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

PolygonalChain::PolygonalChain(const PolygonalChain &other)
{
    points_number_ = other.getPointsNumber();
    for (int i = 0; i < getPointsNumber(); i++)
    {
        points_.push_back(other.getPointByNumber(i));
    }
}

unsigned int PolygonalChain::getPointsNumber() const
{
    return points_number_;
}

Point PolygonalChain::getPointByNumber(unsigned int n) const
{
    return points_.at(n);
}

bool PolygonalChain::equals(const PolygonalChain &other) const
{
    if (getPointsNumber() == other.getPointsNumber())
    {
        for (int i = 0; i < getPointsNumber(); i++)
        {
            if (!getPointByNumber(i).equals(other.getPointByNumber(i)))
                return false;
        }
        return true;
    }
    return false;
}

float PolygonalChain::perimeter() const
{
    float perimeter = 0;
    for (int i = 0; i < getPointsNumber() - 1; i++)
    {
        perimeter += getPointByNumber(i).distance(getPointByNumber(i + 1));
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
    for (int i = 0; i < getPointsNumber() - 1; i++)
    {
        perimeter += getPointByNumber(i).distance(getPointByNumber(i + 1));
    }
    perimeter += getPointByNumber(getPointsNumber() - 1).distance(getPointByNumber(0));
    return perimeter;
}



Polygon::Polygon(unsigned int n, Point *p) : ClosedPolygonalChain(n, p)
{

}

Polygon::Polygon(const Polygon &other) : ClosedPolygonalChain(other)
{

}

float Polygon::area() const
{
    float area = 0;
    for (int i = 0; i < getPointsNumber() - 1; i++)
    {
        area += abs(getPointByNumber(i).getX() * getPointByNumber(i + 1).getY() - getPointByNumber(i + 1).getX() * getPointByNumber(i).getY());
    }
    area += abs(getPointByNumber(getPointsNumber() - 1).getX() * getPointByNumber(0).getY() - getPointByNumber(0).getX() * getPointByNumber(getPointsNumber()).getY());
    area /= 2;
    return area;
}



Triangle::Triangle(unsigned int n, Point *p) : Polygon(n, p)
{
}

Triangle::Triangle(const Triangle &other) : Polygon(other) {}

bool Triangle::isRegular() const
{
    float eps = 0.000001;
    float a, b, c;
    a = getPointByNumber(0).distance(getPointByNumber(1));
    b = getPointByNumber(1).distance(getPointByNumber(2));
    c = getPointByNumber(2).distance(getPointByNumber(0));

    if (abs(a - b) < eps && abs(b - c) < eps && abs(c - a) < eps)
        return true;
    return false;
}

bool Triangle::hasRightAngle() const
{
    float eps = 0.000001;
    float a, b, c, hyp, leg_1, leg_2;
    a = getPointByNumber(0).distance(getPointByNumber(1));
    b = getPointByNumber(1).distance(getPointByNumber(2));
    c = getPointByNumber(2).distance(getPointByNumber(0));

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