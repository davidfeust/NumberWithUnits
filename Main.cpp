#include <iostream>
#include <stdexcept>

using namespace std;

#include "NumberWithUnits.hpp"

using namespace ariel;

int main() {
//    ifstream units_file{"units_file.txt"};
    ifstream units_file{"myTestFile2.txt"};
    NumberWithUnits::read_units(units_file);

    char input = -1;
    NumberWithUnits x, y;
    cout << "Enter 2 numbers with units:" << endl;
    cin >> x;
    cin >> y;
    cout << "The numbers:" << endl;
    cout << x << endl;
    cout << y << endl;
    try {
        x+y;
    } catch (const std::exception &ex) {
        cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
        exit(-1);
    }
    cout << boolalpha; // print booleans as strings from now on:
    while (input != 0) {
        cout << "Choose math or relation operation: +, -, *, <, >, = (==), ! (!=), 0 (to exit)" << endl;
        cin >> input;
        switch (input) {
            case '+' :
                cout << x << "+" << y << "=" << (x + y) << endl;
                cout << y << "+" << x << "=" << (y + x) << endl;
                break;
            case '-' :
                cout << x << "-" << y << "=" << (x - y) << endl;
                cout << y << "-" << x << "=" << (y - x) << endl;
                break;
            case '*' :
                cout << "enter real number:" << endl;
                double d;
                cin >> d;
                cout << x << "*" << d << "=" << (x * d) << endl;
                cout << y << "*" << d << "=" << (y * d) << endl;
                break;
            case '<' :
                cout << x << "<" << y << "=" << (x < y) << endl;
                break;
            case '>' :
                cout << x << ">" << y << "=" << (x > y) << endl;
                break;
            case '=' :
                cout << x << "==" << y << "=" << (x == y) << endl;
                break;
            case '!' :
                cout << x << "!=" << y << "!=" << (x != y) << endl;
                break;
            case '0':
                exit(0);
            default:
                cout << "Invalid operation" << endl;
                break;
        }

    }
    return 0;
}