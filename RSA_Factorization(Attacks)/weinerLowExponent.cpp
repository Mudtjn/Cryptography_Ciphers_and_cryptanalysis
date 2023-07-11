#include <bits/stdc++.h>
#define lli long long int
#define N 160523347
#define E 60728973
using namespace std;

class Fraction
{
private:
    // Calculates the greates common divisor with
    // Euclid's algorithm
    // both arguments have to be positive
    long long gcd(long long a, long long b)
    {
        while (a != b)
        {
            if (a > b)
            {
                a -= b;
            }
            else
            {
                b -= a;
            }
        }
        return a;
    }

public:
    long long numerator, denominator;

    Fraction()
    {
        numerator = 0;
        denominator = 1;
    }

    Fraction(long long n, long long d)
    {
        if (d == 0)
        {
            cerr << "Denominator may not be 0." << endl;
            exit(0);
        }
        else if (n == 0)
        {
            numerator = 0;
            denominator = 1;
        }
        else
        {
            int sign = 1;
            if (n < 0)
            {
                sign *= -1;
                n *= -1;
            }
            if (d < 0)
            {
                sign *= -1;
                d *= -1;
            }

            long long tmp = gcd(n, d);
            numerator = n / tmp * sign;
            denominator = d / tmp;
        }
    }

    operator int() { return (numerator) / denominator; }
    operator float() { return ((float)numerator) / denominator; }
    operator double() { return ((double)numerator) / denominator; }
};

Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
                 lhs.denominator * rhs.denominator);
    return tmp;
}

Fraction operator+=(Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
                 lhs.denominator * rhs.denominator);
    lhs = tmp;
    return lhs;
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator,
                 lhs.denominator * rhs.denominator);
    return tmp;
}

Fraction operator-=(Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator,
                 lhs.denominator * rhs.denominator);
    lhs = tmp;
    return lhs;
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.numerator,
                 lhs.denominator * rhs.denominator);
    return tmp;
}

Fraction operator*=(Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.numerator,
                 lhs.denominator * rhs.denominator);
    lhs = tmp;
    return lhs;
}

Fraction operator*(int lhs, const Fraction &rhs)
{
    Fraction tmp(lhs * rhs.numerator, rhs.denominator);
    return tmp;
}

Fraction operator*(const Fraction &rhs, int lhs)
{
    Fraction tmp(lhs * rhs.numerator, rhs.denominator);
    return tmp;
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    Fraction tmp(lhs.numerator * rhs.denominator,
                 lhs.denominator * rhs.numerator);
    return tmp;
}

std::ostream &operator<<(std::ostream &strm, const Fraction &a)
{
    if (a.denominator == 1)
    {
        strm << a.numerator;
    }
    else
    {
        strm << a.numerator << "/" << a.denominator;
    }
    return strm;
}

vector<lli> continuedFractionCalculator(Fraction f)
{
    lli num = f.numerator, den = f.denominator, rem, q;
    vector<lli> contFrac;
    q = num / den;
    rem = num - q * den;
    contFrac.push_back(q);
    num = den;
    den = rem;
    while (rem != 0)
    {
        q = num / den;
        rem = num - q * den;
        contFrac.push_back(q);
        num = den;
        den = rem;
    }
    return contFrac;
}

Fraction convergentChecker(vector<lli> &contFrac, int i, int n)
{
    if (i == n)
    {
        return Fraction(contFrac[i], 1);
    }
    Fraction f1, f2, f3;
    f1 = Fraction(contFrac[i], 1);
    f2 = convergentChecker(contFrac, i + 1, n);
    f3 = f2;
    f2.numerator = f3.denominator;
    f2.denominator = f3.numerator;
    return f1 + f2;
}

vector<Fraction> convergent(vector<lli> &contFrac)
{
    vector<Fraction> result;
    for (lli i = 0; i < contFrac.size(); i++)
    {
        result.push_back(convergentChecker(contFrac, 0, i));
        // cout<<result[i]<<endl;
    }
    return result;
}

bool calcPrimes(lli phi)
{
    lli a = N - phi + 1;           // p+q
    lli b = sqrt(a * a - 4.0 * N); // p-q
    // a=
    lli p = (a + b) / 2;
    lli q = N / p;
    if (p * q != N)
        return false;
    cout << "p is " << p << endl;
    cout << "q is " << q << endl;
    return true;
}

void calcPhi(vector<Fraction> &convergentList)
{
    lli e = E, d, t, temp, phi;
    for (lli i = 0; i < convergentList.size(); i++)
    {
        if (convergentList[i].numerator != 0)
        {
            // e=convergentList[i].numerator;
            t = convergentList[i].numerator;
            d = convergentList[i].denominator;
            temp = e * d - 1;
            if (temp % t != 0)
                continue;
            // cout<<"d is "<<d<<endl;
            phi = temp / t;
            if (calcPrimes(phi))
                break;
            // return;
        }
    }
}

int main()
{
    Fraction a(E, N);
    vector<lli> contFracList = continuedFractionCalculator(a);
    // for(lli i=0;i<contFracList.size();i++){
    //     cout<<contFracList[i]<<endl;
    // }
    vector<Fraction> result = convergent(contFracList);
    calcPhi(result);

    return 0;
}
