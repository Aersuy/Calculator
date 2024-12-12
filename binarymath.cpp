#include "binarymath.h"

std::string BinaryMath::binaryMultiply( std::string& bin1, std::string& bin2) {
    size_t point_pos1 = bin1.find('.');
    size_t point_pos2 = bin2.find('.');

    // Numarul total de numere fractionale
    size_t frac_len1 = (point_pos1 == std::string::npos) ? 0 : bin1.size() - point_pos1 - 1;
    size_t frac_len2 = (point_pos2 == std::string::npos) ? 0 : bin2.size() - point_pos2 - 1;

    // inmultire ca integeri
    std::string bin1_no_point = bin1;
    std::string bin2_no_point = bin2;
    if (point_pos1 != std::string::npos) bin1_no_point.erase(point_pos1, 1);
    if (point_pos2 != std::string::npos) bin2_no_point.erase(point_pos2, 1);

    std::string bin_product(bin1_no_point.size() + bin2_no_point.size(), '0');

    for (int i = bin1_no_point.size() - 1; i >= 0; --i) {
        for (int j = bin2_no_point.size() - 1; j >= 0; --j) {
            int product = (bin1_no_point[i] - '0') * (bin2_no_point[j] - '0');
            int pos = i + j + 1;
            bin_product[pos] += product;
            if (bin_product[pos] > '1') {
                bin_product[pos - 1] += (bin_product[pos] - '0') / 2;
                bin_product[pos] = ((bin_product[pos] - '0') % 2) + '0';
            }
        }
    }


    size_t total_frac_len = frac_len1 + frac_len2;
    if (total_frac_len > 0 && bin_product.size() > total_frac_len) {
        bin_product.insert(bin_product.end() - total_frac_len, '.');
    } else if (total_frac_len > 0) {
        bin_product = "0." + std::string(total_frac_len - bin_product.size(), '0') + bin_product;
    }

    // eliminarea zerourilor inutile
    size_t first_non_zero = bin_product.find_first_not_of('0');
    if (first_non_zero != std::string::npos) {
        bin_product = bin_product.substr(first_non_zero);
    } else {
        bin_product = "0";
    }

    return bin_product;
}
bool BinaryMath::myXOR(bool b1,bool b2)
{
    return (!(b1 + b2)%2);
}

