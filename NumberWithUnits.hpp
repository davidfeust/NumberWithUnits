//
// Created by david on 06/04/2021.
//

#pragma once

#include <fstream>
#include <ostream>
#include <map>
#include <vector>
#include "Unit.hpp"


namespace ariel {

    class NumberWithUnits {
    private:
        std::string unit;
        double n;
        static Unit g;
//        static std::map<std::string, std::string[2]> convert_big;
//        static std::map<std::string, std::string[2]> convert_small;
//        static std::map<std::string, std::vector<std::string>> same;
//    static std::vector<std::vector<std::string>> same;

        static double find_diff(const NumberWithUnits& unit1, const NumberWithUnits& unit2) ;

    public:

        NumberWithUnits(double num, std::string unit);

        static void read_units(std::ifstream &file);

        const NumberWithUnits operator+(const NumberWithUnits &other) const;

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        const NumberWithUnits operator+();

        const NumberWithUnits operator-(const NumberWithUnits &other) const;

        NumberWithUnits &operator-=(const NumberWithUnits &other);

        const NumberWithUnits operator-();

        bool operator==(const NumberWithUnits &other) const;

        bool operator!=(const NumberWithUnits &other) const;

        bool operator<(const NumberWithUnits &other) const;

        bool operator>(const NumberWithUnits &other) const;

        bool operator<=(const NumberWithUnits &other) const;

        bool operator>=(const NumberWithUnits &other) const;

        // prefix:
        NumberWithUnits &operator++();

        NumberWithUnits &operator--();

        // postfix:
        const NumberWithUnits operator++(int dummy_flag_for_postfix_increment);

        const NumberWithUnits operator--(int dummy_flag_for_postfix_increment);

        friend const NumberWithUnits operator*(const NumberWithUnits &num, double n);

        friend const NumberWithUnits operator*(double n, const NumberWithUnits &num);

        friend const NumberWithUnits operator*(const NumberWithUnits &num, int n);

        friend const NumberWithUnits operator*(int n, const NumberWithUnits &num);


        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num);

        friend std::istream &operator>>(std::istream &is, const NumberWithUnits &num);

    };
}