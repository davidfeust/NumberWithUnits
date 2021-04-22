//
// Created by david on 06/04/2021.
//

#include <map>
#include <utility>
#include <iostream>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

UnitGraph NumberWithUnits::_units_graph;

NumberWithUnits::NumberWithUnits(double num, std::string unit) : _n(num), _unit(std::move(unit)) {
    if (!_units_graph.isThereAUnit(this->_unit)) {
        throw std::runtime_error("Unknown unit");
    }
}

NumberWithUnits::NumberWithUnits() : _n(0) {}

/**
 * read units for file
 * @param file
 */
void NumberWithUnits::read_units(std::ifstream &file) {
    string line;
    while (getline(file, line)) {
        array<string, 3> split;
        size_t j = 0;
        while (j < 3) {
            string s = line.substr(0, line.find_first_of(' ', 0));
            if (s != "1" && s != "=") {
                split.at(j++) = s;
            }
            line = line.substr(line.find_first_of(' ', 0) + 1);
        }
        double conv1 = 1. / (double) stold(split[1]);
        double conv2 = (double) stold(split[1]);
        _units_graph.insert_edge(split[0], split[2], conv1);
        _units_graph.insert_edge(split[2], split[0], conv2);
    }
    file.close();
}

///////////////////////////
// Mathematical operators:
///////////////////////////

NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    double d = 1;
    if (this->_unit != other._unit) {
        d = _units_graph.get_conv(this->_unit, other._unit);
    }
    return ariel::NumberWithUnits(this->_n + (other._n * d), this->_unit);
}

NumberWithUnits &ariel::NumberWithUnits::operator+=(const NumberWithUnits &other) {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    double d = 1;
    if (this->_unit != other._unit) {
        d = _units_graph.get_conv(this->_unit, other._unit);
    }
    this->_n += (other._n * d);
    return *this;
}

NumberWithUnits ariel::NumberWithUnits::operator+() {
    return ariel::NumberWithUnits(this->_n, this->_unit);
}

NumberWithUnits ariel::NumberWithUnits::operator-(const NumberWithUnits &other) const {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    double d = 1;
    if (this->_unit != other._unit) {
        d = _units_graph.get_conv(this->_unit, other._unit);
    }
    return ariel::NumberWithUnits(this->_n - (other._n * d), this->_unit);
}

NumberWithUnits &ariel::NumberWithUnits::operator-=(const NumberWithUnits &other) {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    double d = 1;
    if (this->_unit != other._unit) {
        d = _units_graph.get_conv(this->_unit, other._unit);
    }
    this->_n -= (other._n * d);
    return *this;
}

NumberWithUnits ariel::NumberWithUnits::operator-() {
    return ariel::NumberWithUnits(-this->_n, this->_unit);
}

NumberWithUnits &ariel::NumberWithUnits::operator++() {
    this->_n++;
    return *this;
}

NumberWithUnits &ariel::NumberWithUnits::operator--() {
    this->_n--;
    return *this;
}

NumberWithUnits ariel::NumberWithUnits::operator++(int) {
    NumberWithUnits copy = *this;
    this->_n++;
    return copy;
}

NumberWithUnits ariel::NumberWithUnits::operator--(int) {
    NumberWithUnits copy = *this;
    this->_n--;
    return copy;
}

NumberWithUnits ariel::operator*(const NumberWithUnits &num, double n) {
    return ariel::NumberWithUnits(num._n * n, num._unit);
}

NumberWithUnits ariel::operator*(double n, const NumberWithUnits &num) {
    return num * n;
}

NumberWithUnits ariel::operator*(const ariel::NumberWithUnits &num, int n) {
    return num * (double) n;
}

NumberWithUnits ariel::operator*(int n, const ariel::NumberWithUnits &num) {
    return num * (double) n;
}

///////////////////////
// Relation operators:
///////////////////////

bool NumberWithUnits::operator==(const NumberWithUnits &other) const {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    NumberWithUnits temp{0, this->_unit};
    temp += other;
    return abs(this->_n - temp._n) < TOLERANCE;
}

bool NumberWithUnits::operator!=(const NumberWithUnits &other) const {
    return !(*this == other);
}

bool NumberWithUnits::operator<(const NumberWithUnits &other) const {
    if (!_units_graph.is_same_dim(this->_unit, other._unit)) {
        throw std::runtime_error(
                "Units do not match - [" + other._unit + "] cannot be converted to [" + this->_unit + "]");
    }
    NumberWithUnits temp{0, this->_unit};
    temp += other;
    return this->_n < temp._n;
}

bool NumberWithUnits::operator>(const NumberWithUnits &other) const {
    return !(*this < other) && (*this != other);
}

bool NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    return (*this < other) || (*this == other);
}

bool NumberWithUnits::operator>=(const NumberWithUnits &other) const {
    return (*this > other) || (*this == other);
}

/////////////////
// IO operators:
/////////////////

std::ostream &ariel::operator<<(std::ostream &os, const ariel::NumberWithUnits &num) {
    os << num._n << "[" << num._unit << "]";
    return os;
}

std::istream &ariel::operator>>(std::istream &is, ariel::NumberWithUnits &num) {
    double number = 0;
    string unit_str;
    char c = 0;
    is >> number;
    is >> skipws >> c;
    if (c != '[') {
        is.setstate(ios::failbit);
    }
    is >> unit_str;
    bool flag = false;
    if (unit_str[unit_str.size() - 1] == ']') {
        flag = true;
    }
    unit_str = unit_str.substr(unit_str.find_first_not_of(' '), unit_str.find_first_of(']'));
    num._n = number;
    num._unit = unit_str;
    if (!NumberWithUnits::_units_graph.isThereAUnit(num._unit)) {
        throw std::runtime_error("Unknown unit");
    }
    if (!flag) {
        is >> skipws >> c;
        if (c != ']') {
            is.setstate(ios::failbit);
        }
    }
    return is;
}