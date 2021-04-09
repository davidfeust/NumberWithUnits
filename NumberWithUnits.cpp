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

ariel::NumberWithUnits::NumberWithUnits(double num, std::string unit) : n(num), unit(std::move(unit)) {
    if (!g.isThereAUnit(this->unit)) {
        throw std::runtime_error("Unknown unit");
    }
}

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
        g.insert_edge(split[0], split[2], 1 / stold(split[1]));
        g.insert_edge(split[2], split[0], stold(split[1]));
    }
    file.close();
}


const ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
    }
    double d = 1;
    if (this->unit != other.unit) {
        d = g.get_conv(this->unit, other.unit);
    }
    return ariel::NumberWithUnits(this->n + (other.n * d), this->unit);
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {
    if (!g.is_same_dim(this->unit, other.unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
    }
    double d = 1;
    if (this->unit != other.unit) {
        d = g.get_conv(this->unit, other.unit);
    }
    this->n += (other.n * d);
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator+() {
    return ariel::NumberWithUnits(-this->n, this->unit);
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
    }
    double d = 1;
    if (this->unit != other.unit) {
        d = g.get_conv(this->unit, other.unit);
    }
    return ariel::NumberWithUnits(this->n - (other.n * d), this->unit);
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {
    if (!g.is_same_dim(this->unit, other.unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]");
    }
    double d = 1;
    if (this->unit != other.unit) {
        d = g.get_conv(this->unit, other.unit);
    }
    this->n -= (other.n * d);
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-() {
    return ariel::NumberWithUnits(-this->n, this->unit);
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        return false;
    }
    NumberWithUnits temp{0, this->unit};
    temp += other;
    return abs(this->n - temp.n) < TOLERANCE;
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &other) const {
    return !(*this == other);
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        return false;
    }
    NumberWithUnits temp{0, this->unit};
    temp += other;
    return this->n < temp.n;
}

bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        return false;
    }
    NumberWithUnits temp{0, this->unit};
    temp += other;
    return this->n > temp.n;
}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        return false;
    }
    NumberWithUnits temp{0, this->unit};
    temp += other;
    return this->n <= temp.n;
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &other) const {
    if (!g.is_same_dim(this->unit, other.unit)) {
        return false;
    }
    NumberWithUnits temp{0, this->unit};
    temp += other;
    return this->n >= temp.n;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator++() {
    this->n++;
    return *this;
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator--() {
    this->n--;
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int dummy_flag_for_postfix_increment) {
    NumberWithUnits copy = *this;
    this->n++;
    return copy;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int dummy_flag_for_postfix_increment) {
    NumberWithUnits copy = *this;
    this->n--;
    return copy;
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

std::istream &ariel::operator>>(std::istream &is, ariel::NumberWithUnits &num) {
    char c;
    is >> num.n >> c >> num.unit >> c;
    return is;
}