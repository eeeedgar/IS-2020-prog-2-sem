#include "polynomial.h"

Polynomial::Polynomial()
    : lowestDegree_(0)
    , highestDegree_(0)
{
    factors_ = new int{0};
}

Polynomial::Polynomial(int l, int h, int a [])
{
    lowestDegree_ = l;
    highestDegree_ = h;
    int size = h - l + 1;
    factors_ = new int [size];
    std::copy(a, a + size, factors_);
}

Polynomial::Polynomial(const Polynomial &other)
    : lowestDegree_(other.lowestDegree_)
    , highestDegree_(other.highestDegree_)
{
    int size = highestDegree_ - lowestDegree_ + 1;
    factors_ = new int [size];
    std::copy(other.factors_, other.factors_ + size, factors_);
}

int Polynomial::getFactor(int degree) const
{
    if (degree < lowestDegree_ || degree > highestDegree_)
        return 0;
    return factors_[degree - lowestDegree_];
}

Polynomial Polynomial::refactor() const
{
    int realMin = lowestDegree_;
    int realMax = highestDegree_;
    while (factors_[realMin - lowestDegree_] == 0 && realMin < highestDegree_)
    {
        realMin++;
    }
    while (factors_[realMax - lowestDegree_] == 0 && realMax > realMin)
    {
        realMax--;
    }
    if (realMin >= realMax)
    {
        if (factors_[realMin - lowestDegree_] == 0)
            return Polynomial(0, 0, new int[1]{0});
    }

    int *buf = new int[realMax - realMin + 1];
    std::copy(factors_ + realMin - lowestDegree_, factors_ + realMax - lowestDegree_, buf);
    return Polynomial(realMin, realMax, buf);
}

void Polynomial::operator+=(const Polynomial &other)
{
    int minDegree = (lowestDegree_ < other.lowestDegree_) ? lowestDegree_ : other.lowestDegree_;

    int maxDegree = (highestDegree_ > other.highestDegree_) ? highestDegree_ : other.highestDegree_;

    int *buf = new int[maxDegree - minDegree + 1];

    int *p = buf;

    int *j = factors_;
    int *k = other.factors_;
    for (int i = minDegree; i <= maxDegree; i++)
    {
        *p = 0;
        if (i >= lowestDegree_ and i <= highestDegree_)
        {
            *p += *j;
            j++;
        }
        if (i >= other.lowestDegree_ and i <= other.highestDegree_)
        {
            *p += *k;
            k++;
        }
        p++;
    }

    delete [] factors_;

    factors_ = new int[maxDegree - minDegree + 1];

    std::copy(buf, buf + maxDegree - minDegree + 1, factors_);

    lowestDegree_ = minDegree;
    highestDegree_ = maxDegree;
}

//todo copy-paste from +=
void Polynomial::operator-=(const Polynomial &other)
{
    int minDegree = (lowestDegree_ < other.lowestDegree_) ? lowestDegree_ : other.lowestDegree_;

    int maxDegree = (highestDegree_ > other.highestDegree_) ? highestDegree_ : other.highestDegree_;

    int *buf = new int[maxDegree - minDegree + 1];

    int *p = buf;

    int *j = factors_;
    int *k = other.factors_;
    for (int i = minDegree; i <= maxDegree; i++)
    {
        *p = 0;
        if (i >= lowestDegree_ and i <= highestDegree_)
        {
            *p += *j;
            j++;
        }
        if (i >= other.lowestDegree_ and i <= other.highestDegree_)
        {
            *p -= *k;
            k++;
        }
        p++;
    }

    delete [] factors_;

    factors_ = new int[maxDegree - minDegree + 1];

    std::copy(buf, buf + maxDegree - minDegree + 1, factors_);

    lowestDegree_ = minDegree;
    highestDegree_ = maxDegree;
}

void Polynomial::operator*=(int k)
{
    for (int i = 0; i < highestDegree_ - lowestDegree_ + 1; i++)
        factors_[i] *= k;
}

void Polynomial::operator/=(int k)
{
	//todo use for_each
    for (int i = 0; i < highestDegree_ - lowestDegree_ + 1; i++)
    {
        factors_[i] /= k;
    }
}

int Polynomial::operator[](int degree) const
{
    if (degree < lowestDegree_ || degree > highestDegree_)
        return 0;
    return factors_[degree - lowestDegree_];
}

int &Polynomial::operator[](int i)
{
    if (i > highestDegree_)
    {
        int *array = new int[i - lowestDegree_ + 1];
        for (int *j = array; j <= array + i; j++)
            *j = 0;
        int *p = array;
        for (int *j = factors_; j <= factors_ + highestDegree_ - lowestDegree_; j++, p++)
            *p = *j;
        delete[] factors_;
        highestDegree_ = i;
        factors_ = array;
    }
    if (i < lowestDegree_)
    {
        int *array = new int[highestDegree_ - i + 1];
        for (int *j = array; j <= array + highestDegree_ - i; j++)
            *j = 0;
        int *p = array - lowestDegree_;
        for (int *j = factors_; j <= factors_ + highestDegree_ - lowestDegree_; j++, p++)
            *p = *j;
        delete[] factors_;
        lowestDegree_= i;
        factors_ = array;
    }
    return factors_[i - lowestDegree_];
}



Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
    Polynomial buf(a);
    buf += b;
    return buf;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b)
{
    Polynomial buf(a);
    buf -= b;
    return buf;
}

Polynomial operator*(const Polynomial &p, int k)
{
    Polynomial buf(p);
    buf *= k;
    return buf;
}

Polynomial operator*(int k, const Polynomial &p)
{
    Polynomial buf(p);
    buf *= k;
    return buf;
}

Polynomial Polynomial::operator-()
{
    Polynomial buf(lowestDegree_, highestDegree_, factors_);
    for (int i = 0; i < highestDegree_ - lowestDegree_ + 1; i++)
        buf.factors_[i] *= -1;
    return buf;
}

Polynomial operator*(const Polynomial &a, const Polynomial &b)
{
    if (a.lowestDegree_ == a.highestDegree_ and a.lowestDegree_ == 0)
        return Polynomial();
    if (b.lowestDegree_ == b.highestDegree_ and b.lowestDegree_ == 0)
        return Polynomial();
    int max = a.highestDegree_ + b.highestDegree_;
    int min = a.lowestDegree_ + b.lowestDegree_;
    int *array = new int[max - min + 1];
    for (int *i = array; i <= array + max - min; i++)
        *i = 0;
    for (int *i = a.factors_; i <= a.factors_ + a.highestDegree_ - a.lowestDegree_; i++)
        for (int *j = b.factors_; j <= b.factors_ + b.highestDegree_ - b.lowestDegree_; j++)
            *(array + (i - a.factors_) + (j - b.factors_)) += *i * *j;
    Polynomial pol(min, max, array);
    return pol;
}

bool operator==(const Polynomial &p1, const Polynomial &p2)
{
	//todo refactor original parameters (mb you will need const cast)
    Polynomial a(p1);
    Polynomial b(p2);

    //a.refactor();
    //b.refactor();

    if (a.lowestDegree_ != b.lowestDegree_ || a.highestDegree_ != b.highestDegree_)
        return false;
    else
    {
        for (int i = 0; i < a.highestDegree_ - a.lowestDegree_ + 1; i++)
            if (a.factors_[i] != b.factors_[i])
                return false;
    }
    return true;
}

Polynomial operator/(const Polynomial &p, int k)
{
    Polynomial buf(p);
    buf/=k;
    return buf.refactor();
    //return buf;

}

std::string power(int pow)
{
    if (pow == 1 or pow == 0)
        return "";
    return "^" + std::to_string(pow);
};

std ::string toString(int coeff, int pow, int max)
{
    std::string result = "";
    if (coeff != 0)
    {
        if (pow == 0)
            if (coeff > 0)
                result = "+" + std::to_string(coeff);
            else
                result = std::to_string(coeff);
        else if (coeff == -1 or coeff == 1)
        {
            if (pow != max)
                result = "+";
            if (coeff == -1)
                result = "-";
            result += "x" + power(pow);
        }
        else
        {
            if (coeff > 0 and pow != max)
                result = "+";
            result += std::to_string(coeff) + "x" + power(pow);
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &poly)
{
    Polynomial polynomial(poly);
    //polynomial.refactor();
    int *x = polynomial.factors_ + polynomial.highestDegree_ - polynomial.lowestDegree_;
    if (polynomial.highestDegree_ == polynomial.lowestDegree_)
    {
        out << *(polynomial.factors_) << power(polynomial.highestDegree_);
        return out;
    }
    for (int *i = x; i >= polynomial.factors_; i--)
        out << toString(*i, i - polynomial.factors_ + polynomial.lowestDegree_, polynomial.highestDegree_);
    return out;
}