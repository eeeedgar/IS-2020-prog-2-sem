#include "polynomial.h"
#include <algorithm>

Polynomial::Polynomial()
    : lowestDegree_(0)
    , highestDegree_(0)
{
    factors_ = new int[1]{0};
}

Polynomial::Polynomial(int l, int h, int a [])
{
    lowestDegree_ = l;
    highestDegree_ = h;
    int size = h - l + 1;
    factors_ = new int [size];
    std::copy(a, a + size, factors_);
    refactor();
}

Polynomial::Polynomial(const Polynomial &other)
    : lowestDegree_(other.lowestDegree_)
    , highestDegree_(other.highestDegree_)
{
    int size = highestDegree_ - lowestDegree_ + 1;
    factors_ = new int [size];
    std::copy(other.factors_, other.factors_ + size, factors_);
    refactor();
}

Polynomial& Polynomial::operator=(const Polynomial &other)
{
    lowestDegree_ = other.lowestDegree_;
    highestDegree_ = other.highestDegree_;
    int size = highestDegree_ - lowestDegree_ + 1;
    factors_ = new int[size];
    std::copy(other.factors_, other.factors_ + size, factors_);
    refactor();
    return *this;
}

int Polynomial::getFactor(int degree) const
{
    if (degree < lowestDegree_ || degree > highestDegree_)
        return 0;
    return factors_[degree - lowestDegree_];
}

void Polynomial::refactor() const
{
    Polynomial *buffer = const_cast<Polynomial*>(this);
    int realMin = lowestDegree_;

    while (realMin <= highestDegree_ && factors_[realMin - lowestDegree_] == 0)
        realMin++;
    if (realMin > highestDegree_)
    {
        delete [] buffer->factors_;
        buffer->factors_ = new int[1]{0};
        buffer->lowestDegree_ = 0;
        buffer->highestDegree_ = 0;
    }

    int realMax = highestDegree_;

    while (realMax >= realMin && factors_[realMax - lowestDegree_] == 0)
        realMax--;

    int* buf = new int[realMax - realMin + 1];

    for (int i = realMin; i <= realMax; i++)
        buf[i - realMin] = factors_[i - lowestDegree_];

    delete [] buffer->factors_;
    buffer->factors_ = new int[realMax - realMin + 1];
    std::copy(buf, buf + realMax - realMin + 1, factors_);
    delete [] buf;
    buffer->highestDegree_ = realMax;
    buffer->lowestDegree_ = realMin;
}

Polynomial & Polynomial::plusOrMinus(const Polynomial &other, int option)
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
            *p += *k * option;
            k++;
        }
        p++;
    }

    delete [] factors_;

    factors_ = new int[maxDegree - minDegree + 1];

    std::copy(buf, buf + maxDegree - minDegree + 1, factors_);

    lowestDegree_ = minDegree;
    highestDegree_ = maxDegree;

    refactor();

    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial &other)
{
    plusOrMinus(other, 1);

    return *this;
}

//fixed copy-paste from +=
Polynomial& Polynomial::operator-=(const Polynomial &other)
{
    plusOrMinus(other, -1);

    return *this;
}

Polynomial& Polynomial::operator*=(int k)
{
    std::for_each(factors_, factors_ + highestDegree_ - lowestDegree_ + 1, [k] (int &v) {v *= k;});
    refactor();
    return *this;
}

Polynomial& Polynomial::operator/=(int k)
{
	//fixed use for_each
	std::for_each(factors_, factors_ + highestDegree_ - lowestDegree_ + 1, [k] (int &v) {v /= k;});
    refactor();
    return *this;
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
    buf.refactor();
    return buf;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b)
{
    Polynomial buf(a);
    buf -= b;
    buf.refactor();
    return buf;
}

Polynomial operator*(const Polynomial &p, int k)
{
    Polynomial buf(p);
    buf *= k;
    buf.refactor();
    return buf;
}

Polynomial operator*(int k, const Polynomial &p)
{
    Polynomial buf(p);
    buf *= k;
    buf.refactor();
    return buf;
}

Polynomial Polynomial::operator-()
{
    Polynomial buf(lowestDegree_, highestDegree_, factors_);
    for (int i = 0; i < highestDegree_ - lowestDegree_ + 1; i++)
        buf.factors_[i] *= -1;
    buf.refactor();
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
    pol.refactor();
    return pol;
}

bool operator==(const Polynomial &p1, const Polynomial &p2)
{
	//fixed refactor original parameters (mb you will need const cast)
    Polynomial a(p1);
    Polynomial b(p2);

    a.refactor();
    b.refactor();

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
    buf.refactor();
    return buf;

}

double Polynomial::get(int x) const
{
    int notNegativeDegreeAnswer = 0;
    if (highestDegree_ > 0)
    {
        int minNotNegativeDegree = (lowestDegree_ > 0) ? lowestDegree_: 0;

        for (int i = highestDegree_; i >= minNotNegativeDegree; i--)
        {
            notNegativeDegreeAnswer *= x;
            notNegativeDegreeAnswer += factors_[i - lowestDegree_];
        }
    }

    double negativeDegreeAnswer = 0;
    if (lowestDegree_ < 0)
    {
        int maxNegativeDegree = (highestDegree_ < 0) ? highestDegree_ : -1;

        for (int i = lowestDegree_; i <= maxNegativeDegree; i++)
        {
            negativeDegreeAnswer += factors_[i - lowestDegree_];
            negativeDegreeAnswer /= x;
        }
    }
    return notNegativeDegreeAnswer + negativeDegreeAnswer;
}


std::ostream &operator<<(std::ostream &out, const Polynomial &p)
{
    out << p.toString();
    return out;
}


std::string Polynomial::power(int n) const
{
    if (n > highestDegree_ or n < lowestDegree_)
        return "";
    if (factors_[n - lowestDegree_] == 0)
        return "";

    std::string answer = "";

    if (n != highestDegree_ and factors_[n - lowestDegree_] > 0)
        answer += "+";
    if (n == 0)
    {
        answer += std::to_string(factors_[n - lowestDegree_]);
        return answer;
    }
    else
    {
        switch (factors_[n - lowestDegree_])
        {
            case 1:
                break;
            case -1:
                answer += "-";
                break;
            default:
                answer += std::to_string(factors_[n - lowestDegree_]);
                break;
        }
        answer += "x";
        if (n != 1)
            answer += "^" + std::to_string(n);
    }
    return answer;
}


std::string Polynomial::toString() const
{
    refactor();
    std::string result = "";

    for (int i = highestDegree_; i >= lowestDegree_; i--)
        result += power(i);


    if (result.size() == 0)
        return "0";
    return result;
}