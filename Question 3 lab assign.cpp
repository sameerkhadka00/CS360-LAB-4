#include <iostream>
#include <cstring>
#include <algorithm>

class HugeInteger {
public:
    HugeInteger();
    HugeInteger(const char* number);
    void input(const char* number);
    void output() const;
    HugeInteger add(const HugeInteger& other) const;
    HugeInteger subtract(const HugeInteger& other) const;
    bool isEqualTo(const HugeInteger& other) const;
    bool isNotEqualTo(const HugeInteger& other) const;
    bool isGreaterThan(const HugeInteger& other) const;
    bool isLessThan(const HugeInteger& other) const;
    bool isGreaterThanOrEqualTo(const HugeInteger& other) const;
    bool isLessThanOrEqualTo(const HugeInteger& other) const;
    bool isZero() const;
    HugeInteger multiply(const HugeInteger& other) const;
    HugeInteger divide(const HugeInteger& other) const;
    HugeInteger modulus(const HugeInteger& other) const;

private:
    static const int SIZE = 40;
    int digits[SIZE];
    void zeroOut();
};

HugeInteger::HugeInteger() {
    zeroOut();
}

HugeInteger::HugeInteger(const char* number) {
    zeroOut();
    input(number);
}

void HugeInteger::input(const char* number) {
    int length = strlen(number);
    int startIndex = SIZE - length;

    for (int i = 0; i < length; ++i) {
        digits[startIndex + i] = number[i] - '0';
    }
}

void HugeInteger::output() const {
    int i = 0;
    while (digits[i] == 0 && i < SIZE - 1) {
        ++i;
    }

    while (i < SIZE) {
        std::cout << digits[i++];
    }
}

HugeInteger HugeInteger::add(const HugeInteger& other) const {
    HugeInteger result;
    int carry = 0;

    for (int i = SIZE - 1; i >= 0; --i) {
        result.digits[i] = digits[i] + other.digits[i] + carry;
        carry = result.digits[i] / 10;
        result.digits[i] %= 10;
    }

    return result;
}

HugeInteger HugeInteger::subtract(const HugeInteger& other) const {
    HugeInteger result;
    int borrow = 0;

    for (int i = SIZE - 1; i >= 0; --i) {
        result.digits[i] = digits[i] - other.digits[i] - borrow;
        if (result.digits[i] < 0) {
            result.digits[i] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }

    return result;
}

bool HugeInteger::isEqualTo(const HugeInteger& other) const {
    for (int i = 0; i < SIZE; ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool HugeInteger::isNotEqualTo(const HugeInteger& other) const {
    return !isEqualTo(other);
}

bool HugeInteger::isGreaterThan(const HugeInteger& other) const {
    for (int i = 0; i < SIZE; ++i) {
        if (digits[i] > other.digits[i]) {
            return true;
        } else if (digits[i] < other.digits[i]) {
            return false;
        }
    }
    return false;
}

bool HugeInteger::isLessThan(const HugeInteger& other) const {
    return !isGreaterThan(other) && !isEqualTo(other);
}

bool HugeInteger::isGreaterThanOrEqualTo(const HugeInteger& other) const {
    return isGreaterThan(other) || isEqualTo(other);
}

bool HugeInteger::isLessThanOrEqualTo(const HugeInteger& other) const {
    return !isGreaterThan(other);
}

bool HugeInteger::isZero() const {
    for (int i = 0; i < SIZE; ++i) {
        if (digits[i] != 0) {
            return false;
        }
    }
    return true;
}

HugeInteger HugeInteger::multiply(const HugeInteger& other) const {
    HugeInteger result;
    HugeInteger temp;
    int carry = 0;

    for (int i = SIZE - 1; i >= SIZE / 2; --i) {
        temp.zeroOut();
        for (int j = SIZE - 1; j >= SIZE / 2; --j) {
            temp.digits[i + j - SIZE] = digits[i] * other.digits[j] + carry;
            carry = temp.digits[i + j - SIZE] / 10;
            temp.digits[i + j - SIZE] %= 10;
        }
        result = result.add(temp);
    }

    return result;
}

HugeInteger HugeInteger::divide(const HugeInteger& other) const {
    HugeInteger result;
    HugeInteger remainder(*this);

    while (remainder.isGreaterThanOrEqualTo(other)) {
        result.digits[0]++;
        remainder = remainder.subtract(other);
    }

    return result;
}

HugeInteger HugeInteger::modulus(const HugeInteger& other) const {
    HugeInteger result(*this);
    while (result.isGreaterThanOrEqualTo(other)) {
        result = result.subtract(other);
    }
    return result;
}

void HugeInteger::zeroOut() {
    for (int i = 0; i < SIZE; ++i) {
        digits[i] = 0;
    }
}

int main() {
    HugeInteger h1("1234567890123456789012345678901234567890");
    HugeInteger h2("9876543210987654321098765432109876543210");
    HugeInteger sum = h1.add(h2);
    HugeInteger difference = h1.subtract(h2);
    HugeInteger product = h1.multiply(h2);
    HugeInteger quotient = h1.divide(h2);
    HugeInteger mod = h1.modulus(h2);

    std::cout << "Sum: ";
    sum.output();
    std::cout << std::endl;

    std::cout << "Difference: ";
    difference.output();
    std::cout << std::endl;

    std::cout << "Product: ";
    product.output();
    std::cout << std::endl;
    std::cout << "Modulus: ";
    mod.output();
    std::cout << std::endl;
    return 0;
}

