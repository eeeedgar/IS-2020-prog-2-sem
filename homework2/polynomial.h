#ifndef HOMEWORK2_POLYNOMIAL_H
#define HOMEWORK2_POLYNOMIAL_H

#include <iostream>
#include <sstream>

class Polynomial
{
private:
    int lowestDegree_;
    int highestDegree_;
    int* factors_;

public:
    Polynomial(int l, int h, int a[])
    {
        lowestDegree_ = l;
        highestDegree_ = h;
        int size = h - l + 1;
        factors_ = (int*)malloc(sizeof(int)*size);
        for (int i = 0; i < size; i++)
        {
            factors_[i] = a[i];
        }
    }

    Polynomial(const Polynomial& other)
        : lowestDegree_(other.lowestDegree_)
        , highestDegree_(other.highestDegree_)
    {
        int size = highestDegree_ - lowestDegree_ + 1;
        factors_ = (int*)malloc(sizeof(int)*size);
        for (int i = 0; i < size; i++)
        {
            factors_[i] = other.factors_[i];
        }
    }

    int getHighestNotZeroDegree() const
    {
        return highestDegree_;
    }

    int getLowestNotZeroDegree() const
    {
        return lowestDegree_;
    }

    int getFactor(int degree) const
    {
        if (degree < lowestDegree_ || degree > highestDegree_)
            return 0;
        return factors_[degree - lowestDegree_];
    }

    int lowestDegree() const
    {
        return lowestDegree_;
    }

    int highestDegree() const
    {
        return highestDegree_;
    }

    void show()
    {
        for (int i = highestDegree_; i >= lowestDegree_; i--)
        {
            if (factors_[i] != 0)
            {
                std::cout << factors_[i - lowestDegree_];
                switch (i)
                {
                    case 0:
                        break;
                    case 1:
                        std::cout << "x";
                        break;
                    default:
                        std::cout << "x^" << i;
                        break;
                }
                if (i != lowestDegree_)
                {
                    std::cout << " + ";
                }
            }
        }
        std::cout << std::endl;
    }

    void operator*=(int k)
    {
        for (int i = 0; i < highestDegree_ - lowestDegree_ + 1; i++)
        {
            factors_[i] *= k;
        }
    }

    int operator[](int degree)
    {
        if (degree < lowestDegree_ || degree > highestDegree_)
            return 0;
        return factors_[degree - lowestDegree_];
    }

    friend sstream& operator<<(sstream& ss, const Polynomial p);
};

Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
    int highestDegree, lowestDegree;
    int aL = a.getLowestNotZeroDegree();
    int aH = a.getHighestNotZeroDegree();
    int bL = b.getLowestNotZeroDegree();
    int bH = b.getHighestNotZeroDegree();

    if (aH > bH)
        highestDegree = aH;
    else
        highestDegree = bH;

    if (aL < bL)
        lowestDegree = aL;
    else
        lowestDegree = bL;

    int size = highestDegree - lowestDegree + 1;

    int array[size];

    for (int i = 0; i < size; i++)
    {
        array[i] = 0;
    }

    for (int i = aL; i < aH + 1; i++)
    {
        array[i - lowestDegree] += a.getFactor(i);
    }

    for (int i = bL; i < bH + 1; i++)
    {
        array[i - lowestDegree] += b.getFactor(i);
    }

    return Polynomial(lowestDegree, highestDegree, array);
}

Polynomial operator*(const Polynomial p, int k)
{
    int lowestDegree = p.lowestDegree();
    int highestDegree = p.highestDegree();
    int factors[highestDegree - lowestDegree + 1];
    for (int i = lowestDegree; i <= highestDegree; i++)
    {
        factors[i - lowestDegree] = p.getFactor(i) * k;
    }
    return Polynomial(lowestDegree, highestDegree, factors);
}





#endif //HOMEWORK2_POLYNOMIAL_H
