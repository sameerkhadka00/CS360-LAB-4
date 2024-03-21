#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Rational {
public:
    Rational(int num = 0, int den = 1);
    Rational add(const Rational& other) const;
    Rational subtract(const Rational& other) const;
    Rational multiply(const Rational& other) const;
    Rational divide(const Rational& other) const;
    void printFraction() const;
    void printFloatingPoint() const;

private:
    int numerator;
    int denominator;
    void reduce();
};

Rational::Rational(int num, int den) : numerator(num), denominator(den) {
    reduce();
}

Rational Rational::add(const Rational& other) const {
    int newNum = numerator * other.denominator + other.numerator * denominator;
    int newDen = denominator * other.denominator;
    return Rational(newNum, newDen);
}

Rational Rational::subtract(const Rational& other) const {
    int newNum = numerator * other.denominator - other.numerator * denominator;
    int newDen = denominator * other.denominator;
    return Rational(newNum, newDen);
}

Rational Rational::multiply(const Rational& other) const {
    int newNum = numerator * other.numerator;
    int newDen = denominator * other.denominator;
    return Rational(newNum, newDen);
}

Rational Rational::divide(const Rational& other) const {
    int newNum = numerator * other.denominator;
    int newDen = denominator * other.numerator;
    return Rational(newNum, newDen);
}

void Rational::printFraction() const {
    std::cout << numerator << "/" << denominator;
}

void Rational::printFloatingPoint() const {
    double result = static_cast<double>(numerator) / denominator;
    std::cout << result;
}

void Rational::reduce() {
    int commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
}

int main() {
    Rational r1(2, 4);
    Rational r2(3, 5);

    std::cout << "r1 + r2 = ";
    r1.add(r2).printFraction();
    std::cout << " ("; r1.add(r2).printFloatingPoint(); std::cout << ")" << std::endl;

    std::cout << "r1 - r2 = ";
    r1.subtract(r2).printFraction();
    std::cout << " ("; r1.subtract(r2).printFloatingPoint(); std::cout << ")" << std::endl;

    std::cout << "r1 * r2 = ";
    r1.multiply(r2).printFraction();
    std::cout << " ("; r1.multiply(r2).printFloatingPoint(); std::cout << ")" << std::endl;

    std::cout << "r1 / r2 = ";
    r1.divide(r2).printFraction();
    std::cout << " ("; r1.divide(r2).printFloatingPoint(); std::cout << ")" << std::endl;

    return 0;
}
