//
// Created by david on 06/04/2021.
//

#include "NumberWithUnits.hpp"


ariel::NumberWithUnits::NumberWithUnits(int num, std::string unit) {

}

void ariel::NumberWithUnits::read_units(std::ifstream stream) {

}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &other) const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator+() {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const{
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits &ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-() {
    return ariel::NumberWithUnits(0, "");
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
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::operator*(double n, const ariel::NumberWithUnits &num) {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::operator*(const ariel::NumberWithUnits &num, int n) {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::operator*(int n, const ariel::NumberWithUnits &num) {
    return ariel::NumberWithUnits(0, "");
}

std::ostream &ariel::operator<<(std::ostream &os, const ariel::NumberWithUnits &num) {
    return os;
}

std::istream &ariel::operator>>(std::istream &is, const ariel::NumberWithUnits &num) {
    return is;
}
