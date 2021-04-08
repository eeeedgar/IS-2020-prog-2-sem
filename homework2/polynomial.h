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
	//fixed make operator=
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

    Polynomial& operator=(const Polynomial &);

    //fixed return Polynomial&
    Polynomial& operator+=(const Polynomial &);

    Polynomial& operator-=(const Polynomial &);

    Polynomial& operator*=(int);

    Polynomial& operator/=(int);

    Polynomial operator-();

    int operator[](int) const;

    int &operator[](int);

    std::string toString() const;

    std::string power(int) const;

    //fixed (my) repair refactor, make it Polynomial&
    //fixed (my) repair << ( (-1, -1, new int[1]{1}) - 1^-1 )
    //fixed (my) how to use refactor after &operator[] if toString is const and << uses const
    void refactor() const;

    double get(int n) const;

    friend Polynomial operator+(const Polynomial &, const Polynomial &);
    friend Polynomial operator-(const Polynomial &, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, int);
    friend Polynomial operator*(int, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend Polynomial operator/(const Polynomial &, int);
    friend bool operator==(const Polynomial &, const Polynomial &);
    friend std::ostream &operator<<(std::ostream &, const Polynomial &);
};


#endif //HOMEWORK2_POLYNOMIAL_H
