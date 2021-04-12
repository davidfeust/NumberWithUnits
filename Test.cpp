//
// Created by david on 06/04/2021.
//

#include "doctest.h"
#include "NumberWithUnits.hpp"
#include "UnitGraph.hpp"

using namespace std;
using namespace ariel;

double random(double min, double max);

set<string> all_units;

// Mathematical operators:
TEST_CASE ("Init") {
    ifstream units_file{"units.txt"};
    if (!units_file.is_open()) {
        cout << "Failed to open file!" << endl;
    }
    NumberWithUnits::read_units(units_file);
    ifstream units_file_temp{"units.txt"};
    string line;
    while (getline(units_file_temp, line)) {
        array<string, 3> split;
        size_t j = 0;
        while (j < 3) {
            string s = line.substr(0, line.find_first_of(' ', 0));
            if (s != "1" && s != "=") {
                split.at(j++) = s;
            }
            line = line.substr(line.find_first_of(' ', 0) + 1);
        }
        all_units.insert(split[0]);
        all_units.insert(split[2]);
    }
}

TEST_CASE ("Mathematical operators for same _unit") {
    for (const string &i: all_units) {
        double x = random(-30, 30);
        double y = random(-30, 30);
        NumberWithUnits a{x, i};
        NumberWithUnits b{y, i};
        // +
                CHECK(+a == NumberWithUnits{+x, i});
                CHECK(a + b == NumberWithUnits{x + y, i});
        NumberWithUnits temp1 = a += b;
        x += y;
                CHECK(temp1 == NumberWithUnits{x, i});
                CHECK(a == NumberWithUnits{x, i});

        // -
                CHECK(-a == NumberWithUnits{-x, i});
                CHECK(a - b == NumberWithUnits{x - y, i});
        NumberWithUnits temp2 = a -= b;
        x -= y;
                CHECK(temp2 == NumberWithUnits{x, i});
                CHECK(a == NumberWithUnits{x, i});

        // ++
                CHECK(a++ == NumberWithUnits{x++, i});
                CHECK(a == NumberWithUnits{x, i});
                CHECK(++a == NumberWithUnits{++x, i});
                CHECK(a == NumberWithUnits{x, i});

        // --
                CHECK(a-- == NumberWithUnits{x--, i});
                CHECK(a == NumberWithUnits{x, i});
                CHECK(--a == NumberWithUnits{--x, i});
                CHECK(a == NumberWithUnits{x, i});
    }
}

TEST_CASE ("Multiplication") {
    for (const string &i: all_units) {
        double x = random(-30, 30);
        double y = random(-30, 30);
        NumberWithUnits a{x, i};
                CHECK(a * y == NumberWithUnits{x * y, i});
                CHECK(y * a == NumberWithUnits{x * y, i});
    }
}


TEST_CASE ("Relation operators for same _unit") {
    for (const string &i: all_units) {
        double x = random(-30, 30);
        double y = random(-30, 30);
        NumberWithUnits a{x, i};
        NumberWithUnits b{y, i};
        try {
                    CHECK((x < y) == (a < b));
        } catch (const std::exception &ex) {}
    }
}

TEST_CASE ("Output") {
    for (const string &i: all_units) {
        double x = random(-30, 30);
        ostringstream output;
        NumberWithUnits num{x, i};
        std::stringstream stream;
        output << num;
        stream << fixed << setprecision(4) << x;
        CHECK(output.str() == stream.str() + "[" + i + "]");
    }
}

TEST_CASE ("Input") {
    NumberWithUnits num{0, "_units_graph"};
    for (const string &i: all_units) {
        double x = random(-30, 30);
        istringstream input{to_string(x) + " [ " + i + " ]"};
        input >> num;
                CHECK(num == NumberWithUnits{x, i});
    }
}

double random(double min, double max) {
    return ((double) rand() * (max - min) / (double) RAND_MAX - min);
}