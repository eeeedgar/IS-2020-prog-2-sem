#ifndef HOMEWORK2_POLYNOMIAL_H
#define HOMEWORK2_POLYNOMIAL_H

#include <iostream>
#include <sstream>
#include <math.h>

class Polynomial
{
private:
    int lowestDegree_;
    int highestDegree_;
    int* factors_;

public:
    Polynomial();

    Polynomial(int, int, int []);

    Polynomial(const Polynomial &);

    int getFactor(int) const;

    int max() const
    {
        return highestDegree_;
    }

    int min() const
    {
        return lowestDegree_;
    }

    void operator+=(const Polynomial &);

    void operator-=(const Polynomial &);

    void operator*=(int);

    void operator/=(int);

    Polynomial operator-();

    int operator[](int) const;

    int &operator[](int);

    Polynomial refactor() const;

    friend Polynomial operator+(const Polynomial &, const Polynomial &);
    friend Polynomial operator-(const Polynomial &, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, int);
    friend Polynomial operator*(int, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend Polynomial operator/(const Polynomial &, int);
    friend bool operator==(const Polynomial &, const Polynomial &);
    friend std::ostream &operator<<(std::ostream &, const Polynomial &);
};



bool operator==(const Polynomial &, const Polynomial &);

Polynomial operator+(const Polynomial &, const Polynomial &);

Polynomial operator-(const Polynomial &, const Polynomial &);

Polynomial operator*(const Polynomial &, int);

Polynomial operator*(int, const Polynomial &);

Polynomial operator*(const Polynomial &, const Polynomial &);

Polynomial operator/(const Polynomial &, int);

std::string power(int);

std::string toString(int, int, int);

std::ostream &operator<<(std::ostream &, const Polynomial &);



#endif //HOMEWORK2_POLYNOMIAL_H
