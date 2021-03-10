#ifndef HOMEWORK1_GEOMETRY_H
#define HOMEWORK1_GEOMETRY_H

#include <vector>
#include <math.h>

class Point
{
private:
    float x_, y_;

public:
    // default-converting constructor
    Point(int x = 0, int y = 0)
        : x_ (x)
        , y_ (y)
    {}

    // copy constructor
    Point(const Point& other)
        : x_(other.x_)
        , y_(other.y_)
    {}

    Point& operator=(const Point &other);

    float getX() const;
    float getY() const;
    void setX(int x);
    void setY(int y);
    float distance(const Point& other) const;
    bool operator==(const Point& other) const;
};

class PolygonalChain
{
protected:
    unsigned int points_number_;
    std::vector<Point> points_;
public:
    // default-converting constructor
    PolygonalChain(unsigned int n = 0, Point *p = {});

    // copy constructor
    PolygonalChain(const PolygonalChain& other);

    PolygonalChain& operator=(const PolygonalChain& other);

    bool operator==(const PolygonalChain& other) const;

    //we need default
    virtual ~PolygonalChain() = default;

    unsigned int getN() const;
    Point getPoint(unsigned int n) const;
    virtual float perimeter() const;
};

class ClosedPolygonalChain : public PolygonalChain
{
public:
    using PolygonalChain::PolygonalChain;

    virtual float perimeter() const;
};

class Polygon : public ClosedPolygonalChain
{
public:
    using ClosedPolygonalChain::ClosedPolygonalChain;

    virtual float area() const;
};

class Triangle : public Polygon
{
public:
    using Polygon::Polygon;

    //bool isRegular() const;
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon
{
public:
	//using Polygon::Polygon
    using Polygon::Polygon;

    float height() const;
};

class RegularPolygon : public Polygon
{
public:
    using Polygon::Polygon;
    float perimeter() const;
    float area() const;
};


#endif //HOMEWORK1_GEOMETRY_H