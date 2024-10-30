#include <iostream>
#include <stdexcept>

class Tiny {
    char v;

    void assign(int i) {
        if (i < 0 || i > 63) throw Bad_range(); // 6 bits can represent 0 to 63
        v = i;
    }

public:
    class Bad_range { };

    // Constructor from int
    Tiny(int i) {
        assign(i);
    }

    // Implicit conversion to int
    operator int() const {
        return static_cast<int>(v);
    }

    // Overload the + operator
    Tiny operator+(const Tiny& other) const {
        return Tiny(static_cast<int>(*this) + static_cast<int>(other));
    }

    // Overload the - operator
    Tiny operator-(const Tiny& other) const {
        return Tiny(static_cast<int>(*this) - static_cast<int>(other));
    }

    // Overload the assignment operator
    Tiny& operator=(const Tiny& other) {
        if (this != &other) {
            assign(static_cast<int>(other));
        }
        return *this;
    }

    // Overload the + operator for Tiny + int
    friend Tiny operator+(const Tiny& tiny, int value) {
        return Tiny(static_cast<int>(tiny) + value);
    }

    // Overload the - operator for Tiny - int
    friend Tiny operator-(const Tiny& tiny, int value) {
        return Tiny(static_cast<int>(tiny) - value);
    }

    // Overload the + operator for int + Tiny
    friend Tiny operator+(int value, const Tiny& tiny) {
        return Tiny(value + static_cast<int>(tiny));
    }

    // Overload the - operator for int - Tiny
    friend Tiny operator-(int value, const Tiny& tiny) {
        return Tiny(value - static_cast<int>(tiny));
    }
};

// Example of Tiny objects mixing with ints in arithmetic expressions
int main() {
    try {
        Tiny c1 = 2; // Perform range check
        Tiny c2 = 62; // Perform range check
        Tiny c3 = c2 - c1; // c3 = 60
        Tiny c4 = c3; // no range check required

        int i = c1 + c2; // i = 64
        std::cout << "c1 + c2 = " << i << std::endl; // Output: c1 + c2 = 64

        // Uncommenting the following line will throw a range error:
        // c1 = c1 + c2; // range error: c1 can’t be 64

        // This line will safely compute: 
        Tiny result = c3 - 64; // result will be valid, but -4 is out of range
        std::cout << "c3 - 64 = " << static_cast<int>(result) << std::endl; // Output will be -4, but will not assign to Tiny

        // Uncommenting the following line will throw a range error:
        // c2 = c3 - 64; // range error: c2 can’t be -4

        c3 = c4; // no range check required
    } catch (const Tiny::Bad_range&) {
        std::cerr << "Range error occurred!" << std::endl;
    }

    return 0;
}
