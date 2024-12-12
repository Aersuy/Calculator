#ifndef BIGNUM_H
#define BIGNUM_H
#include <vector>    // std::vector
#include <string>    // std::string
#include <algorithm> // std::find
#include <iostream>  // std::cout
#include "lonefunctions.h" // findCh
#include "binarymath.h" // binaryMultiply()
#include <cmath> // std::floor
class BigNum
{
private:
    std::vector<int> m_num;
    std::vector<int> m_frac;
    bool m_sign;
    int m_length;
public:
    BigNum();
    BigNum(std::string);
    BigNum(int);
    BigNum(double);
    BigNum(BigNum&);
    ~BigNum() = default;


    void print();
    void divideByTwo();
    void multiplyByTwo();
    std::string toBinary();
    void fromBinary(std::string& binary);
    void addFraction( BigNum& fraction);

    BigNum operator+(BigNum& other);
    BigNum operator+(int);
    BigNum operator+(double);

    BigNum operator-(BigNum& other);
    BigNum operator-(int);
    BigNum operator-(double);

    BigNum operator*(BigNum& other);
    BigNum operator*(int);
    BigNum operator*(double);

    BigNum operator/(BigNum& other);
    BigNum operator/(int);
    BigNum operator/(double);

    bool operator>(BigNum& other);
    bool operator>(int);
    bool operator>(double);

    bool operator<(BigNum& other);
    bool operator<(int);
    bool operator<(double);

    bool operator==(BigNum& other);
    bool operator==(int);
    bool operator==(double);


};

#endif // BIGNUM_H
