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

    const float TOLERANCE = 0.001;

    class NumberWithUnits {
    private:
        std::string _unit;
        double _n;
        static UnitGraph _units_graph;


    public:

        NumberWithUnits(double num, std::string unit);

        NumberWithUnits();

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
        const NumberWithUnits operator++(int);

        const NumberWithUnits operator--(int);

        friend NumberWithUnits operator*(const NumberWithUnits &num, double n);

        friend NumberWithUnits operator*(double n, const NumberWithUnits &num);

        friend NumberWithUnits operator*(const NumberWithUnits &num, int n);

        friend NumberWithUnits operator*(int n, const NumberWithUnits &num);


        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num);

        friend std::istream &operator>>(std::istream &is, NumberWithUnits &num);

    };
}