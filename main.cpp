#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int gcd(int a, int b){
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return abs(a);
}

class RationalDivisionByZero {
};


class Rational {
private:
    int p;
    int q; // is maintained to be positive

    void reduce()
    {
        int gcd1 = gcd(this->p, this->q);
        this->p /= gcd1;
        this->q /= gcd1;
        if (this->q < 0){
            this->p *= -1;
            this->q *= -1;
        }
    }

public:
    Rational():p(0), q(1){}
    Rational(int p, int q): p(p), q(q){
        this->reduce();
    }
    Rational(int a):p(a), q(1){}
    Rational(const Rational &other): p(other.p), q(other.q){}
    int getNumerator() const{
        return this->p;
    }
    int getDenominator() const{
        return this->q;
    }
    Rational operator+(const Rational &rat) const{
        int gcd1 = gcd(this->q, rat.q);
        int denom = this->q / gcd1 * rat.q;
        int nom = rat.q / gcd1 * this->p + this->q / gcd1 * rat.p;
        Rational res(nom, denom);
        res.reduce();
        return res;
    }
    Rational operator+(const int a) const{
        return *this + Rational(a);
    }
    Rational operator-() const{
        return Rational(-this->p, this->q);
    }
    Rational operator-(const Rational &rat) const{
        return *this + (-rat);
    }
    Rational operator-(const int a) const{
        return *this - Rational(a);
    }
    Rational operator*(const Rational &rat) const{
        int gcd1 = gcd(this->p, rat.q), gcd2 = gcd(this->q, rat.p);
        Rational res(this->p / gcd1 * rat.p / gcd2, this->q / gcd2 * rat.q / gcd1);
        return res;
    }
    Rational operator*(const int a) const{
        return *this * Rational(a);
    }
    Rational operator/(const Rational &rat) const{
        if (rat.p == 0)
            throw RationalDivisionByZero();
        else {
            int gcd1 = gcd(this->p, rat.p), gcd2 = gcd(this->q, rat.q);
            Rational res(this->p / gcd1 * rat.q / gcd2, this->q / gcd2 * rat.p / gcd1);
            return res;
        }
    }
    Rational operator/(const int a) const{
        return *this / Rational(a);
    }
    Rational& operator+=(const Rational &rat){
        int gcd1 = gcd(this->q, rat.q);
        this->p = rat.q / gcd1 * this->p + this->q / gcd1 * rat.p;
        this->q = this->q / gcd1 * rat.q;
        this->reduce();
        return *this;
    }
    Rational& operator-=(const Rational& rat){
        int gcd1 = gcd(this->q, rat.q);
        this->p = rat.q / gcd1 * this->p - this->q / gcd1 * rat.p;
        this->q = this->q / gcd1 * rat.q;
        this->reduce();
        return *this;
    }
    Rational& operator*=(const Rational& rat){
        int gcd1 = gcd(this->p, rat.q), gcd2 = gcd(this->q, rat.p);
        this->p = this->p / gcd1 * rat.p / gcd2;
        this->q = this->q / gcd2 * rat.q / gcd1;
        return *this;
    }
    Rational& operator/=(const Rational& rat){
        int gcd1 = gcd(this->p, rat.p), gcd2 = gcd(this->q, rat.q);
        this->p = this->p / gcd1 * rat.q / gcd2;
        this->q = this->q / gcd2 * rat.p / gcd1;
        return *this;
    }
    bool operator==(const Rational &rat) const{
        return this->p == rat.p && this->q == rat.q;
    }
    bool operator!=(const Rational &rat) const{
        return !(*this == rat);
    }
    bool operator>(const Rational &rat) const{
        return (*this - rat).p > 0;
    }
    bool operator<(const Rational &rat) const{
        return (*this - rat).p < 0;
    }
    bool operator>=(const Rational &rat) const{
        return (*this - rat).p >= 0;
    }
    bool operator<=(const Rational &rat) const{
        return (*this - rat).p <= 0;
    }
    Rational& operator++(){
        this->p += this->q;
        return *this;
    }
    Rational operator++(int not_used){
        Rational oldValue(*this);
        this->p += this->q;
        return oldValue;
    }
    Rational& operator--(){
        this->p -= this->q;
        return *this;
    }
    Rational operator--(int not_used){
        Rational oldValue(*this);
        this->p -= this->q;
        return oldValue;
    }
    Rational operator+() const{
        return Rational(this->p, this->q);
    }
    friend const Rational operator+(const int, const Rational&);
    friend const Rational operator-(const int, const Rational&);
    friend const Rational operator*(const int, const Rational&);
    friend const Rational operator/(const int, const Rational&);
    friend const bool operator>(const int, const Rational&);
    friend const bool operator<(const int, const Rational&);
    friend const bool operator>=(const int, const Rational&);
    friend const bool operator<=(const int, const Rational&);
    friend const bool operator==(const int, const Rational&);
    friend const bool operator!=(const int, const Rational&);
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational&);
};

const Rational operator+(const int a, const Rational& rat){
    return Rational(a) + rat;
}

const Rational operator-(const int a, const Rational& rat){
    return Rational(a) - rat;
}

const Rational operator*(const int a, const Rational &rat){
    return Rational(a) * rat;
}

const Rational operator/(const int a, const Rational &rat) {
    return Rational(a) / rat;
}

const bool operator>(const int a, const Rational &rat){
    return rat < a;
}

const bool operator<(const int a, const Rational &rat){
    return rat > a;
}

const bool operator>=(const int a, const Rational& rat){
    return rat <= a;
}

const bool operator<=(const int a, const Rational &rat){
    return rat >= a;
}

const bool operator==(const int a, const Rational &rat){
    return rat == a;
}

const bool operator!=(const int a, const Rational &rat){
    return rat != a;
}

istream &operator>>(istream &is, Rational &rat) {
    char str[30];
    is >> str;
    char* split_str = strtok(str, "/"); //разделяем по '/'
    rat.p = atoi(split_str);
    split_str = strtok(NULL, "/");
    if (split_str != NULL)
        rat.q = atoi(split_str);
    else
        rat.q = 1;
    rat.reduce();
    return is;
}

ostream &operator<<(ostream &os, const Rational &rat) {
    os << rat.p;
    if (rat.q != 1)
        os << "/" << rat.q;
    return os;
}

int main(int argc, char** argv) {
    int a;
    cin >> a;

    int p, q;
    cin >> p >> q;
    const Rational rc(p, q); // q != 0 is guaranteed by author of tests
    cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

    Rational r1, r2;
    cin >> r1 >> r2;

    cout << r1 << endl;
    cout << r2 << endl;

    try {
        cout << 1/r1 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot get reciprocal of r1." << endl;
    }

    try {
        cout << rc/r2 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot divide by r2." << endl;
    }

    cout << (r1 < r2) << endl;
    cout << (r1 <= r2) << endl;
    cout << (r1 > r2) << endl;
    cout << (r1 >= r2) << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;

    cout << (r1 < a) << endl;
    cout << (r1 <= a) << endl;
    cout << (r1 > a) << endl;
    cout << (r1 >= a) << endl;
    cout << (r1 == a) << endl;
    cout << (r1 != a) << endl;

    cout << (a < r2) << endl;
    cout << (a <= r2) << endl;
    cout << (a > r2) << endl;
    cout << (a >= r2) << endl;
    cout << (a == r2) << endl;
    cout << (a != r2) << endl;

    cout << rc + a << endl
         << a + rc << endl
         << -rc * r1 << endl
         << (+r1 - r2 * rc) * a << endl;

    cout << ++r1 << endl;
    cout << r1 << endl;
    cout << r1++ << endl;
    cout << r1 << endl;
    cout << --r1 << endl;
    cout << r1 << endl;
    cout << r1-- << endl;
    cout << r1 << endl;
    cout << ++++r1 << endl;
    cout << r1 << endl;

    cout << ((((r1 += r2) /= Rational(-5,3)) -= rc) *= a) << endl;
    cout << (r1 += r2 /= 3) << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    return 0;
}