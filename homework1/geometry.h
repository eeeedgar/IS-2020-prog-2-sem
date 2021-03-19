#ifndef HOMEWORK1_GEOMETRY_H
#define HOMEWORK1_GEOMETRY_H

#include <vector>
#include <math.h>

class Point
{
private:
    int x_, y_;

public:
    Point(int x = 0, int y = 0)
            : x_ (x)
            , y_ (y)
    {}

    Point(const Point& other)
            : x_(other.x_)
            , y_(other.y_)
    {}

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    double distance(const Point& other) const;
    int distance2(const Point& other) const;

    Point& operator=(const Point &other);
    //fixed its not java
    bool operator==(const Point& other) const;
};

class PolygonalChain
{
protected:
    std::vector<Point> points_;
public:
    PolygonalChain(unsigned int n = 0, Point *p = {});

    PolygonalChain(const PolygonalChain& other);

    //fixed we need default
    virtual ~PolygonalChain() = default;

    unsigned int getN() const;
    Point getPoint(unsigned int n) const;
    virtual double perimeter() const;

    PolygonalChain& operator=(const PolygonalChain& other);
    bool operator==(const PolygonalChain& other) const;
};

class ClosedPolygonalChain : public PolygonalChain
{
public:
    using PolygonalChain::PolygonalChain;

    virtual double perimeter() const;
};

class Polygon : public ClosedPolygonalChain
{
public:
    //fixed copy-paste
    using ClosedPolygonalChain::ClosedPolygonalChain;

    virtual double area() const;
};

class Triangle : public Polygon
{
public:
    using Polygon::Polygon;

    bool hasRightAngle() const;
};

class Trapezoid : public Polygon
{
public:
    //fixed using Polygon::Polygon
    using Polygon::Polygon;

    double height() const;
};

class RegularPolygon : public Polygon
{
public:
    using Polygon::Polygon;

    double perimeter() const;
    double area() const;
};


#endif //HOMEWORK1_GEOMETRY_H