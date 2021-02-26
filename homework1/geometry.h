#ifndef HOMEWORK1_GEOMETRY_H
#define HOMEWORK1_GEOMETRY_H

#include <vector>

bool equalsf(float a, float b);

class Point
{
private:
    float x_, y_;

public:
    // default-converting constructor
    Point(int x = 0, int y = 0)
        : x_ (x)
        , y_ (y)
    {
    }

    // copy constructor
    Point(const Point& other)
        : x_(other.x_)
        , y_(other.y_)
    {
    }

    Point& operator=(const Point &other);

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    bool equals(const Point& other) const;
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

    virtual ~PolygonalChain()
    {
        points_.clear();
    }

    unsigned int getN() const;
    Point getPoint(unsigned int n) const;
    bool equals(const PolygonalChain& other) const;
    virtual float perimeter() const;
};

class ClosedPolygonalChain : public PolygonalChain
{
public:
    ClosedPolygonalChain(unsigned int n = 0, Point *p = {});
    ClosedPolygonalChain(const ClosedPolygonalChain& other);
    ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);
    float perimeter() const;
    virtual ~ClosedPolygonalChain()
    {
        points_.clear();
    }
};

class Polygon : public ClosedPolygonalChain
{
public:
    Polygon(unsigned n = 0, Point *p = {});
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    float area() const;
    virtual ~Polygon()
    {
        points_.clear();
    }
};

class Triangle : public Polygon
{
public:
    Triangle(unsigned int n = 0, Point *p = {});
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);
    bool isRegular() const;
    bool hasRightAngle() const;
    virtual ~Triangle(){
        points_.clear();
    }
};

class Trapezoid : public Polygon
{
public:
    Trapezoid(unsigned int n = 0, Point *p = {});
    Trapezoid(const Trapezoid& other);
    Trapezoid& operator=(const Trapezoid& other);
    float height() const;
    virtual ~Trapezoid()
    {
        points_.clear();
    }
};

class RegularPolygon : public Polygon
{
public:
    RegularPolygon(unsigned int n = 0, Point* p = {});
    RegularPolygon(const RegularPolygon& other);
    RegularPolygon& operator=(const RegularPolygon& other);
    virtual ~RegularPolygon()
    {
        points_.clear();
    }
};


#endif //HOMEWORK1_GEOMETRY_H