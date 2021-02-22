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
    Point(int x = 0, int y = 0);

    // copy constructor
    Point(const Point& other);

    void destruct()
    {
        delete this;
    }

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    bool equals(const Point& other) const;
    float distance(const Point& other) const;

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
    float perimeter() const;
};

class Polygon : public ClosedPolygonalChain
{
public:
    Polygon(unsigned n = 0, Point *p = {});
    Polygon(const Polygon& other);
    float area() const;
};

class Triangle : public Polygon
{
public:
    Triangle(unsigned int n = 0, Point *p = {});
    Triangle(const Triangle& other);
    bool isRegular() const;
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon
{
public:
    Trapezoid(unsigned int n = 0, Point *p = {});
    Trapezoid(const Trapezoid& other);
    float height() const;
};

class RegularPolygon : public Polygon
{
public:
    RegularPolygon(unsigned int n = 0, Point* p = {});
    RegularPolygon(const RegularPolygon& other);
};


#endif //HOMEWORK1_GEOMETRY_H