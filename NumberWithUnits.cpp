//
// Created by david on 06/04/2021.
//

#include <map>
#include <utility>
#include <iostream>
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

Unit NumberWithUnits::g;

ariel::NumberWithUnits::NumberWithUnits(double num, std::string unit) : n(num), unit(std::move(unit)) {}

void NumberWithUnits::read_units(std::ifstream &file) {
    string line;
    while (getline(file, line)) {
        string split[3];
        int j = 0;
        while (j < 3) {
            string s = line.substr(0, line.find_first_of(' ', 0));
            if (s != "1" && s != "=") {
                split[j++] = s;
            }
            line = line.substr(line.find_first_of(' ', 0) + 1);
        }
        g.insert_edge(split[0], split[2], 1 /stold(split[1]));
        g.insert_edge(split[2], split[0],  stold(split[1]));
    }
    file.close();
}


const ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        throw std::runtime_error("Can not add " + (this->unit) + " with " + other.unit + "!");
    }

    if (this->unit == other.unit) {
        return ariel::NumberWithUnits(this->n + other.n, this->unit);
    }
    double d = g.get_conv(this->unit, other.unit);
    return ariel::NumberWithUnits(this->n + (other.n * d), this->unit);
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator+() {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-() {
    return ariel::NumberWithUnits(-this->n, this->unit);
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &other) const {
    return false;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator++() {
    return *this;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator--() {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int dummy_flag_for_postfix_increment) {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int dummy_flag_for_postfix_increment) {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::operator*(const ariel::NumberWithUnits &num, double n) {
    return ariel::NumberWithUnits(num.n * n, num.unit);
}

const ariel::NumberWithUnits ariel::operator*(double n, const ariel::NumberWithUnits &num) {
    return num * n;
}

const ariel::NumberWithUnits ariel::operator*(const ariel::NumberWithUnits &num, int n) {
    return num * (double) n;
}

const ariel::NumberWithUnits ariel::operator*(int n, const ariel::NumberWithUnits &num) {
    return num * (double) n;
}

std::ostream &ariel::operator<<(std::ostream &os, const ariel::NumberWithUnits &num) {
    os << num.n << "[" << num.unit << "]";
    return os;
}

std::istream &ariel::operator>>(std::istream &is, const ariel::NumberWithUnits &num) {
    return is;
}

//double NumberWithUnits::find_diff(const NumberWithUnits& unit1, const NumberWithUnits& unit2) {
//    string key = unit1.unit + "-" + unit2.unit;
//    if (convert_big.contains(key)) {
//        return convert_big.at(key);
//    }
//    key = unit2.unit + "-" + unit1.unit ;
//    if (convert_big.contains(key)) {
//        return convert_big.at(key);
//    }
//    double ans;
//    while (true) {
//        ans = convert_big.at(key);
//        key =
//    }
//    return 0;
//}


//bool is_same_dim(const ariel::Unit &unit1, const ariel::Unit &unit2) {
//    if (unit1 == Unit::km || unit1 == Unit::m || unit1 == Unit::cm) {
//        if (unit2 != Unit::km || unit2 != Unit::m || unit2 != Unit::cm) {
//            return false;
//        }
//    } else if (unit1 == Unit::ton || unit1 == Unit::kg || unit1 == Unit::g) {
//        if (unit2 != Unit::ton || unit2 != Unit::kg || unit2 != Unit::g) {
//            return false;
//        }
//    } else if (unit1 == Unit::hou || unit1 == Unit::min || unit1 == Unit::sec) {
//        if (unit2 != Unit::hou || unit2 != Unit::min || unit2 != Unit::sec) {
//            return false;
//        }
//    } else if (unit1 == Unit::USD || unit1 == Unit::ILS) {
//        if (unit2 != Unit::USD || unit2 != Unit::ILS) {
//            return false;
//        }
//    }
//    return true;
//}
