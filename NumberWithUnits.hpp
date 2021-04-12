//
// Created by david on 06/04/2021.
//

#pragma once

#include <fstream>
#include <ostream>
#include <map>
#include <vector>
#include "UnitGraph.hpp"


namespace ariel {

    class NumberWithUnits {
    private:
        std::string _unit;
        double _n;
        static UnitGraph _units_graph;

        const float TOLERANCE = 0.001;

    public:

        NumberWithUnits(double num, std::string unit);

        static void read_units(std::ifstream &file);

        NumberWithUnits operator+(const NumberWithUnits &other) const;

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        NumberWithUnits operator+();

        NumberWithUnits operator-(const NumberWithUnits &other) const;

        NumberWithUnits &operator-=(const NumberWithUnits &other);

        NumberWithUnits operator-();

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
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment);

        NumberWithUnits operator--(int dummy_flag_for_postfix_increment);

        friend NumberWithUnits operator*(const NumberWithUnits &num, double n);

        friend NumberWithUnits operator*(double n, const NumberWithUnits &num);

        friend NumberWithUnits operator*(const NumberWithUnits &num, int n);

        friend NumberWithUnits operator*(int n, const NumberWithUnits &num);


        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num);

        friend std::istream &operator>>(std::istream &is, NumberWithUnits &num);

    };
}