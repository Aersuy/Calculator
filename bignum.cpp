#include "bignum.h"
constexpr int MAX_PRECISION = 20;
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
    while (!m_frac.empty() && m_frac.back() == 0) {
        m_frac.pop_back();
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
        return *this - temp; // fa scaderea
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
std::vector<int> subtractVectors(const std::vector<int>& larger, const std::vector<int>& smaller,bool& mainBorrow) {
    std::vector<int> result(larger.size(), 0);
    int borrow = 0;

    for (int i = std::max(larger.size(),smaller.size()) - 1; i >= 0; i--) {
        int largerDigit = larger[i];
        int smallerDigit = (i < smaller.size()) ? smaller[i] : 0;

        int diff = largerDigit - smallerDigit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[i] = diff;
    }
    mainBorrow = borrow;
    // Remove leading zeros
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

BigNum BigNum::operator-(BigNum& other) {
    BigNum result;

    // Handle signs
    if (m_sign != other.m_sign) {
        // Subtracting a negative is the same as adding
        BigNum temp = other;
        temp.m_sign = !temp.m_sign;
        return *this + temp;
    }

    // Determine which is larger to handle subtraction order
    bool resultSign = true; // Assume result is positive
    if (*this < other) {
        resultSign = false; // Result will be negative

    }
     bool b;
    // Subtract fractional parts
    if (!m_frac.empty() || !other.m_frac.empty()) {
        // Ensure both fractions are the same length
        size_t maxFracLen = std::max(m_frac.size(), other.m_frac.size());
        std::vector<int> largerFrac = m_frac;
        std::vector<int> smallerFrac = other.m_frac;

        largerFrac.resize(maxFracLen, 0);
        smallerFrac.resize(maxFracLen, 0);

        // Subtract the fractional parts
        std::vector<int> fracResult = subtractVectors(largerFrac, smallerFrac,b);

        // Handle potential borrowing from the integer part
        if (b) {
            if (!m_num.empty()) {
                m_num[m_num.size() - 1] -= 1;
            }
        }

        result.m_frac = fracResult;
    }

    // Subtract integer parts
    result.m_num = subtractVectors(m_num, other.m_num,b);
    if(result.m_num.empty())
    {
        result.m_num.push_back(0);
    }
    while (result.m_num.size() > 1 && result.m_num.back() == 0) {
        result.m_num.pop_back(); // Remove the last digit if it's zero
    }


    result.m_sign = resultSign;
    return result;
}
BigNum BigNum::operator-(int other)
{
    BigNum otherBigNum(other);
    return (*this) - otherBigNum;
}
BigNum BigNum::operator-(double other)
{
    BigNum otherBigNum(other);
    return (*this) - otherBigNum;
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
BigNum BigNum::operator/(BigNum& other) {
    // Check for division by zero
    BigNum zero("0");
    if (other ==zero) {
        throw std::invalid_argument("Division by zero");
    }

    // Handle signs
    BigNum dividend = *this;
    BigNum divisor = other;
    BigNum result;
    result.m_sign = (m_sign != other.m_sign); // Result is negative if signs are different
    dividend.m_sign = false;
    divisor.m_sign = false;

    // Normalize decimal places by shifting
    int scale = std::max(m_frac.size(), other.m_frac.size());
    dividend.shiftDecimalLeft(scale);
    divisor.shiftDecimalLeft(scale);

    // Perform integer division
    BigNum quotient("0");
    BigNum remainder("0");

    for (int i = dividend.m_num.size() - 1; i >= 0; --i) {
        remainder.shiftDecimalLeft(1); // Make room for the next digit
        remainder.m_num[0] = dividend.m_num[i];

        // Find the largest digit for the quotient
        int digit = 0;
        while (remainder > divisor || remainder == divisor) {
            remainder = remainder - divisor;
            digit++;
        }

        quotient.m_num.push_back(digit);
    }

    // Reverse quotient digits to get the correct order
    std::reverse(quotient.m_num.begin(), quotient.m_num.end());

    // Handle fractional part (if needed)
    BigNum fractionalPart("0");
    remainder.shiftDecimalLeft(scale);

    for (size_t i = 0; i < MAX_PRECISION; ++i) {
        remainder.shiftDecimalLeft(1); // Multiply remainder by 10
        int digit = 0;
        while (remainder > divisor || remainder == divisor) {
            remainder = remainder - divisor;
            digit++;
        }

        fractionalPart.m_frac.push_back(digit);

        if (remainder == zero) {
            break; // No more fractional part
        }
    }

    // Combine integer and fractional parts
    result.m_num = quotient.m_num;
    result.m_frac = fractionalPart.m_frac;
    result.normalize(); // Ensure no leading/trailing zeros

    return result;
}
void BigNum::shiftDecimalRight(size_t positions) {
    while (positions > 0 && !m_frac.empty()) {
        // Move the first fractional digit to the integer part
        m_num.insert(m_num.begin(), m_frac.front());
        m_frac.erase(m_frac.begin());
        positions--;
    }

    // If there are still positions left, pad with zeros in the integer part
    while (positions > 0) {
        m_num.insert(m_num.begin(), 0);
        positions--;
    }
    normalize();
}
void BigNum::shiftDecimalLeft(size_t positions) {
    while (positions > 0 && !m_num.empty()) {
        // Move the last integer digit to the fractional part
        m_frac.insert(m_frac.begin(), m_num.back());
        m_num.pop_back();
        positions--;
    }
    // If there are still positions left, pad with zeros in the fractional part
    while (positions > 0) {
        m_frac.insert(m_frac.begin(), 0);
        positions--;
    }
    normalize();
}
void BigNum::normalize() {
    // Remove leading zeros from the integer part
    while (m_num.size() > 1 && m_num.back() == 0) {
        m_num.pop_back();
    }

    // If the integer part becomes empty, add a single zero
    if (m_num.empty()) {
        m_num.push_back(0);
    }

    // Remove trailing zeros from the fractional part
    while (!m_frac.empty() && m_frac.back() == 0) {
        m_frac.pop_back();
    }
}







