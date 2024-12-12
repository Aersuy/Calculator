#include "bignum.h"

BigNum::BigNum()
{

}

BigNum::BigNum(std::string stringInput)
{    m_length = stringInput.size();
    if(stringInput[0] == '-')
    {
        m_sign = false;
        stringInput = stringInput.substr(1);
    } else {
        m_sign = true;
    }
    int it = LoneFunctions::findCh('.',stringInput);
    std::string sbString = stringInput.substr(0,it);

    for(int i = 0;i <= sbString.size()-1;++i)
    {
        m_num.push_back(sbString[i] - '0');
    }
    if(it != -1)
    {
        std::string fracPart = stringInput.substr(it+1);
        for(char digit: fracPart)
        {
            m_frac.push_back(digit - '0');
        }
    }
}
BigNum::BigNum(int inputInt)
{
    if(inputInt < 0)
    {
        m_sign = false;
        inputInt = -inputInt;
    } else{
        m_sign = true;
    }
    if(inputInt == 0)
    {
        m_num.push_back(0);
        return;
    }
    while(inputInt > 0)
    {
        m_num.push_back(inputInt % 10);
        inputInt /=10;
    }
    std::reverse(m_num.begin(),m_num.end());
}
BigNum::BigNum(double inputFloat)
{
    std::string stringInput = std::to_string(inputFloat);
    m_length = stringInput.size();
    if(stringInput[0] == '-')
    {
        m_sign = false;
        stringInput = stringInput.substr(1);
    } else {
        m_sign = true;
    }
    int it = LoneFunctions::findCh('.',stringInput);
    std::string sbString = stringInput.substr(0,it);

    for(int i = 0;i <= sbString.size()-1;++i)
    {
        m_num.push_back(sbString[i] - '0');
    }
    if(it != -1)
    {
        std::string fracPart = stringInput.substr(it+1);
        for(char digit: fracPart)
        {
            m_frac.push_back(digit - '0');
        }
    }
}
BigNum::BigNum(BigNum& other)
{
    m_sign = other.m_sign;
    m_frac = other.m_frac;
    m_num = other.m_num;
    m_length = other.m_length;
}
void BigNum::print()
{   if(m_sign == false)
    {
        std::cout << '-';
    }
    for (int i = 0; i < m_num.size(); ++i)
    {
        std::cout << m_num[i];
    }
    std::cout << '.';
    for (int i = 0; i < m_frac.size(); ++i)
    {
        std::cout << m_frac[i];
    }
    std::cout << '\n';
}
BigNum BigNum::operator+(BigNum& other)
{
    BigNum result;
    if((*this).m_sign != other.m_sign)
    {
        BigNum temp = other;
        temp.m_sign = !temp.m_sign;
       // return *this - temp; // fa scaderea
    }
    int fractSize1, fractSize2;
    fractSize1 = this->m_frac.size();
    fractSize2 = other.m_frac.size();
    int maxFractSize = std::max(fractSize1, fractSize2);

    std::vector<int> frac1 = this->m_frac;
    std::vector<int> frac2 = other.m_frac;

    while (frac1.size() < maxFractSize) frac1.push_back(0);
    while (frac2.size() < maxFractSize) frac2.push_back(0);


    int carry = 0;
    for (int i = maxFractSize - 1; i >= 0; --i) {
        int sum = frac1[i] + frac2[i] + carry;
        result.m_frac.push_back(sum % 10);
        carry = sum / 10;

    }

    std::reverse(result.m_frac.begin(), result.m_frac.end());

    std::vector<int> num1 = this->m_num;
    std::vector<int> num2 = other.m_num;

    while (num1.size() < num2.size()) num1.insert(num1.begin(), 0);
    while (num2.size() < num1.size()) num2.insert(num2.begin(), 0);

    for (int i = num1.size() - 1; i >= 0; --i) {
        int sum = num1[i] + num2[i] + carry;
        result.m_num.push_back(sum % 10);
        carry = sum / 10;
    }

    if (carry) result.m_num.push_back(carry);

    std::reverse(result.m_num.begin(), result.m_num.end());

    result.m_sign = this->m_sign;

    return result;

}
BigNum BigNum::operator+(int other)
{
    BigNum otherBigNum(other);
    return (*this) + otherBigNum;
}
BigNum BigNum::operator+(double other)
{
    BigNum otherBigNum(other);
    return (*this) + otherBigNum;
}
bool BigNum::operator==(BigNum& other)
{
    bool answer = true;
    if((*this).m_frac.size() != other.m_frac.size() || (*this).m_num.size() != other.m_num.size())
    {
        return false;
    }
    for (int i = 0; i < other.m_num.size(); ++i) {
        if(this->m_num[i] != other.m_num[i])
        {
            return false;
        }
    }
    for (int i = 0; i < other.m_frac.size(); ++i) {
        if(this->m_frac[i] != other.m_frac[i])
        {
            return false;
        }
    }
    return true;
}
bool BigNum::operator==(double other)
{
    BigNum ne{other};
    if((*this) == ne)
    {
        return true;
    }
    return false;
}

bool BigNum::operator==(int other)
{
    BigNum ne{other};
    if((*this) == ne)
    {
        return true;
    }
    return false;
}
bool BigNum::operator<( BigNum &other) {

    if (this->m_sign != other.m_sign) {
        return !this->m_sign;
    }


    if (this->m_num.size() != other.m_num.size()) {
        if (this->m_sign) {
            return this->m_num.size() < other.m_num.size();
        } else {
            return this->m_num.size() > other.m_num.size();
        }
    }

    for (size_t i = 0; i < this->m_num.size(); ++i) {
        if (this->m_num[i] != other.m_num[i]) {
            if (this->m_sign) {
                return this->m_num[i] < other.m_num[i];
            } else {
                return this->m_num[i] > other.m_num[i];
            }
        }
    }

    size_t maxFracLength = std::max(this->m_frac.size(), other.m_frac.size());
    for (size_t i = 0; i < maxFracLength; ++i) {
        int thisDigit = (i < this->m_frac.size()) ? this->m_frac[i] : 0;
        int otherDigit = (i < other.m_frac.size()) ? other.m_frac[i] : 0;

        if (thisDigit != otherDigit) {
            if (this->m_sign) {
                return thisDigit < otherDigit;
            } else {
                return thisDigit > otherDigit;
            }
        }
    }

    return false;
}
bool BigNum::operator<(double other)
{
    BigNum otherNum(other);
    if((*this) < otherNum)
    {
        return true;
    }
    else return false;
}
bool BigNum::operator<(int other)
{
    BigNum otherNum(other);
    if((*this) < otherNum)
    {
        return true;
    }
    else return false;
}
bool BigNum::operator>(BigNum& other)
{
    if((*this) == other)
    {
        return false;
    } else if ((*this) < other) {
        return false;
    } else
    {
        return true;
    }

}
bool BigNum::operator>(double other)
{
    BigNum bOther(other);
    if((*this) == bOther)
    {
        return false;
    } else if ((*this) < bOther) {
        return false;
    } else
    {
        return true;
    }
}
bool BigNum::operator>(int other)
{
    BigNum bOther(other);
    if((*this) == bOther)
    {
        return false;
    } else if ((*this) < bOther) {
        return false;
    } else
    {
        return true;
    }
}
BigNum BigNum::operator*(BigNum& other) {

    BigNum result;

    std::string binary1 = this->toBinary();
    std::string binary2 = other.toBinary();



    std::string res = BinaryMath::binaryMultiply(binary1,binary2);

    result.fromBinary(res);
    result.m_sign = BinaryMath::myXOR(this->m_sign,other.m_sign);

    return result;
}
void BigNum::divideByTwo() {
    int carry = 0;


    for (size_t i = 0; i < this->m_num.size(); ++i) {
        int current = carry * 10 + this->m_num[i];
        this->m_num[i] = current / 2;
        carry = current % 2;
    }


    for (size_t i = 0; i < this->m_frac.size(); ++i) {
        int current = carry * 10 + this->m_frac[i];
        this->m_frac[i] = current / 2;
        carry = current % 2;
    }


    while (!this->m_frac.empty() && this->m_frac.back() == 0) {
        this->m_frac.pop_back();
    }


    while (this->m_num.size() > 1 && this->m_num.front() == 0) {
        this->m_num.erase(this->m_num.begin());
    }
}


void BigNum::multiplyByTwo() {
    int carry = 0;


    for (int i = m_frac.size() - 1; i >= 0; --i) {
        int current = m_frac[i] * 2 + carry;
        m_frac[i] = current % 10;
        carry = current / 10;
    }


    for (int i = m_num.size() - 1; i >= 0; --i) {
        int current = m_num[i] * 2 + carry;
        m_num[i] = current % 10;
        carry = current / 10;
    }


    if (carry > 0) {
        m_num.insert(m_num.begin(), carry);
    }
}


std::string BigNum::toBinary() {

    std::string binary_int;
    BigNum temp((*this));


    while (!temp.m_num.empty() && !(temp.m_num.size() == 1 && temp.m_num[0] == 0))
    {
        binary_int.insert(binary_int.begin(), (temp.m_num.back() % 2 == 0 ? '0' : '1'));
        temp.divideByTwo();
    }


    std::string binary_frac;
    BigNum frac_part;
    frac_part.m_num.clear();
    frac_part.m_frac = this->m_frac;

    for (size_t i = 0; i < 200 && !frac_part.m_frac.empty(); ++i) {
        frac_part.multiplyByTwo();
        if (!frac_part.m_num.empty() && frac_part.m_num[0] == 1) {
            binary_frac.push_back('1');
            frac_part.m_num[0] = 0;
        } else {
            binary_frac.push_back('0');
        }
    }
    while (!binary_frac.empty() && binary_frac.back() == '0') {
        binary_frac.pop_back();
    }

    if (binary_frac.empty()) {
        return binary_int;
    } else {
        return binary_int + '.' + binary_frac;
    }
}
void BigNum::fromBinary(std::string& binary) {
    size_t point_pos = binary.find('.');
    std::string binary_int = (point_pos == std::string::npos) ? binary : binary.substr(0, point_pos);
    std::string binary_frac = (point_pos == std::string::npos) ? "" : binary.substr(point_pos + 1);


    this->m_num.clear();
    BigNum temp;
    for (char bit : binary_int) {
        temp.multiplyByTwo();
        if (bit == '1') {
            if (temp.m_num.empty()) {
                temp.m_num.push_back(1);
            } else {
                temp.m_num.back() += 1;
            }
        }
    }
    this->m_num = temp.m_num;


    BigNum fracPart(0.0);
    this->m_frac.clear();
    double frac_unit = 0.5;

    for (char bit : binary_frac) {
        if (bit == '1') {
           fracPart = fracPart + frac_unit;
        }

        frac_unit = frac_unit/2;
    }
    this->m_frac = fracPart.m_frac;

    while (!this->m_frac.empty() && this->m_frac.back() == 0) {
        this->m_frac.pop_back();
    }
}




