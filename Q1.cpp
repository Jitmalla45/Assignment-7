#include <iostream>
using namespace std;

struct Y; // Forward declaration of Y

struct X {
    int i;

    // Constructor to initialize X with an int
    X(int val) : i(val) {}

    // Overload + operator to add int to X
    X operator+(int val) const {
        return X(i + val);
    }

    // Overload + operator to add X to X
    X operator+(const X& other) const {
        return X(i + other.i);
    }

    // Friend function to overload * operator for X * Y
    friend X operator*(const X& lhs, const Y& rhs);
};

struct Y {
    int i;

    // Constructor to initialize Y with an int
    Y(int val) : i(val) {}

    // Conversion operator to convert Y to int
    operator int() const {
        return i;
    }

    // Overload + operator to add X to Y
    Y operator+(const X& x) const {
        return Y(i + x.i);
    }

    // Overload + operator to add Y to Y
    Y operator+(const Y& y) const {
        return Y(i + y.i);
    }
};

// Overload * operator for X * Y
X operator*(const X& lhs, const Y& rhs) {
    return X(lhs.i * rhs.i);
}

// Overload * operator for int * Y
Y operator*(int lhs, const Y& rhs) {
    return Y(lhs * rhs.i);
}

// External function f(X) returning int
int f(X x) {
    return x.i;
}

int main() {
    X x = 1;   // Calls X(int)
    Y y = 2;   // Calls Y(int)

    int i = 2;

    // Printing results of each expression
    cout << "i + 10 = " << (i + 10) << endl;             // int + int
    cout << "y + 10 = " << (static_cast<int>(y) + 10) << endl;
    cout << "y + 10 * y = " << (y + 10 * y).i << endl;

    cout << "x + y + i = " << (x + y + i).i << endl;     // X + Y + int
    cout << "x + x + i = " << (x + x + i).i << endl;     // X + X + int
    cout << "f(7) = " << f(7) << endl;                   // f(X(7))

    cout << "f(y) = " << f(X(y)) << endl;                // f(X(Y -> int))
    cout << "y + y = " << (y + y).i << endl;             // Y + Y
    cout << "106 + y = " << (106 + static_cast<int>(y)) << endl;

    return 0;
}

/*  
1. i + 10
Conversion: None (both are int).
Result Type: int
2. y + 10
Conversion: Y → int (via operator int()).
Result Type: int
3. y + 10 * y
Conversion:
int * Y (via operator*(int, Y)).
Y + Y (via operator+(Y, Y)).
Result Type: Y
4. x + y + i
Conversion: Y → int (via operator int()).
Result Type: X
5. x * x + i
Conversion: None (assuming x * x is valid).
Result Type: X
6. f(7)
Conversion: int → X (via constructor X(int)).
Result Type: int
7. f(y)
Conversion: Y → X (via X(Y → int)).
Result Type: int
8. y + y
Conversion: None (both are Y).
Result Type: Y
9. 106 + y
Conversion: Y → int (via operator int()).
Result Type: int
*/