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
void init(string file) {
    all_units.clear();
    ifstream units_file{file};
    if (!units_file.is_open()) {
        cout << "Failed to open file!" << endl;
    }
    NumberWithUnits::read_units(units_file);
    ifstream units_file_temp{file};
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

TEST_CASE ("Mathematical operators for same unit") {
    init("units.txt");
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

TEST_CASE ("Mathematical operators for different unit") {
    init("units_file.txt");
    // conversations units 
    double d2y = 365;
    double h2d = 24;
    double m2h = 60;
    double s2m = 60;
    for (int i = 0; i < 20; i++) {
        int max = 30;
        int min = -max;
        double ny = random(min, max);
        double nd = random(min, max);
        double nh = random(min, max);
        double nm = random(min, max);
        double ns = random(min, max);
        NumberWithUnits y{ny, "year"};
        NumberWithUnits d{nd, "day"};
        NumberWithUnits h{nh, "hour"};
        NumberWithUnits m{nm, "min"};
        NumberWithUnits s{ns, "sec"};
                SUBCASE("+") {
                    CHECK_EQ(y + d, NumberWithUnits{ny + (1. / d2y) * nd, "year"});
                    CHECK_EQ(d + y, NumberWithUnits{nd + d2y * ny, "day"});
                    CHECK_EQ(d + h, NumberWithUnits{nd + (1. / h2d) * nh, "day"});
                    CHECK_EQ(h + d, NumberWithUnits{nh + h2d * nd, "hour"});
                    CHECK_EQ(m + s, NumberWithUnits{nm + (1. / s2m) * ns, "min"});
                    CHECK_EQ(s + m, NumberWithUnits{ns + s2m * nm, "sec"});
                    CHECK_EQ(h + m, NumberWithUnits{nh + (1. / m2h) * nm, "hour"});
            double calc = ny + (1. / d2y) * (nd + (1. / h2d) * (nh + (1. / m2h) * (nm + (1. / s2m) * ns)));
                    CHECK_EQ(y + d + h + m + s, NumberWithUnits{calc, "year"});
        }
                SUBCASE("-") {
                    CHECK_EQ(y - d, NumberWithUnits{ny - (1. / d2y) * nd, "year"});
                    CHECK_EQ(d - y, NumberWithUnits{nd - d2y * ny, "day"});
                    CHECK_EQ(d - h, NumberWithUnits{nd - (1. / h2d) * nh, "day"});
                    CHECK_EQ(h - d, NumberWithUnits{nh - h2d * nd, "hour"});
                    CHECK_EQ(m - s, NumberWithUnits{nm - (1. / s2m) * ns, "min"});
                    CHECK_EQ(s - m, NumberWithUnits{ns - s2m * nm, "sec"});
                    CHECK_EQ(h - m, NumberWithUnits{nh - (1. / m2h) * nm, "hour"});
        }

                SUBCASE("<") {
                    CHECK_EQ(y < d, ny < (1. / d2y) * nd);
                    CHECK_EQ(d < h, nd < (1. / h2d) * nh);
                    CHECK_EQ(h < d, nh < h2d * nd);
                    CHECK_EQ(m < s, nm < (1. / s2m) * ns);
                    CHECK_EQ(s < m, ns < s2m * nm);
                    CHECK_EQ(h < m, nh < (1. / m2h) * nm);
        }
                SUBCASE(">") {
                    CHECK_EQ(y > d, ny > (1. / d2y) * nd);
                    CHECK_EQ(d > h, nd > (1. / h2d) * nh);
                    CHECK_EQ(h > d, nh > h2d * nd);
                    CHECK_EQ(m > s, nm > (1. / s2m) * ns);
                    CHECK_EQ(s > m, ns > s2m * nm);
                    CHECK_EQ(h > m, nh > (1. / m2h) * nm);
        }
                SUBCASE("<=") {
                    CHECK_EQ(y <= d, ny <= (1. / d2y) * nd);
                    CHECK_EQ(d <= h, nd <= (1. / h2d) * nh);
                    CHECK_EQ(h <= d, nh <= h2d * nd);
                    CHECK_EQ(m <= s, nm <= (1. / s2m) * ns);
                    CHECK_EQ(s <= m, ns <= s2m * nm);
                    CHECK_EQ(h <= m, nh <= (1. / m2h) * nm);
        }
                SUBCASE(">=") {
                    CHECK_EQ(y >= d, ny >= (1. / d2y) * nd);
                    CHECK_EQ(d >= h, nd >= (1. / h2d) * nh);
                    CHECK_EQ(h >= d, nh >= h2d * nd);
                    CHECK_EQ(m >= s, nm >= (1. / s2m) * ns);
                    CHECK_EQ(s >= m, ns >= s2m * nm);
                    CHECK_EQ(h >= m, nh >= (1. / m2h) * nm);
        }
                SUBCASE("==") {
                    CHECK_EQ(y == d, ny == (1. / d2y) * nd);
                    CHECK_EQ(d == h, nd == (1. / h2d) * nh);
                    CHECK_EQ(h == d, nh == h2d * nd);
                    CHECK_EQ(m == s, nm == (1. / s2m) * ns);
                    CHECK_EQ(s == m, ns == s2m * nm);
                    CHECK_EQ(h == m, nh == (1. / m2h) * nm);
        }
                SUBCASE("!=") {
                    CHECK_EQ(y != d, ny != (1. / d2y) * nd);
                    CHECK_EQ(d != h, nd != (1. / h2d) * nh);
                    CHECK_EQ(h != d, nh != h2d * nd);
                    CHECK_EQ(m != s, nm != (1. / s2m) * ns);
                    CHECK_EQ(s != m, ns != s2m * nm);
                    CHECK_EQ(h != m, nh != (1. / m2h) * nm);
        }
    }
}

TEST_CASE ("Multiplication") {
    init("units.txt");
    for (const string &i: all_units) {
        double x = random(-30, 30);
        double y = random(-30, 30);
        NumberWithUnits a{x, i};
                CHECK(a * y == NumberWithUnits{x * y, i});
                CHECK(y * a == NumberWithUnits{x * y, i});
    }
}

TEST_CASE ("Relation operators for same unit") {
    init("units.txt");
    for (const string &i: all_units) {
        double x = random(-30, 30);
        double y = random(-30, 30);
        NumberWithUnits a{x, i};
        NumberWithUnits b{y, i};
        try {
                    CHECK((x < y) == (a < b));
                    CHECK((x > y) == (a > b));
                    CHECK((x == y) == (a == b));
                    CHECK((x != y) == (a != b));
                    CHECK((x <= y) == (a <= b));
                    CHECK((x >= y) == (a >= b));
        } catch (const std::exception &ex) {}
    }
}

TEST_CASE ("Output") {
    init("units.txt");
    for (const string &i: all_units) {
        double x = random(-30, 30);
        ostringstream output;
        NumberWithUnits num{x, i};
        std::stringstream stream;
        output << fixed << setprecision(4) << num;
        stream << fixed << setprecision(4) << x;
                CHECK(output.str() == stream.str() + "[" + i + "]");
    }
}

TEST_CASE ("Input") {
    init("units.txt");
    NumberWithUnits num1, num2, num3, num4;
    for (const string &i: all_units) {
        double x = random(-30, 30);
        istringstream input1{to_string(x) + " [ " + i + " ]"};
        input1 >> num1;

                CHECK(num1 == NumberWithUnits{x, i});
        istringstream input2{to_string(x) + "[" + i + "]"};
        input2 >> num2;
                CHECK(num2 == NumberWithUnits{x, i});
        istringstream input3{to_string(x) + " [" + i + "]"};
        input3 >> num3;
                CHECK(num3 == NumberWithUnits{x, i});
        istringstream input4{to_string(x) + "[" + i + " ]"};
        input4 >> num4;
                CHECK(num4 == NumberWithUnits{x, i});

    }
}

double random(double min, double max) {
    return ((double) rand() * (max - min) / (double) RAND_MAX - min);
}