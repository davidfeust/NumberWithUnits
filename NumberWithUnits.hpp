//
// Created by david on 06/04/2021.
//

#pragma once

#include <fstream>
#include <ostream>

namespace ariel {

    class NumberWithUnits {
    private:
        int kg;

    public:

        NumberWithUnits(int num, std::string unit);

        static void read_units(std::ifstream stream);

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