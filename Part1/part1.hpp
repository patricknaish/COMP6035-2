#include <stdio.h>

using namespace std;

// Represents a raw value
// VAL<1> = 1
template <int i> class VAL {
public:
	static int eval(int x) {
		return i;
	}
};

// Represents the variable x
class VAR {
public:
	static int eval(int x) {
		return x;
	}
};

// Represents an expression at the highest level
template <class c> class EXP {
public:
	static int eval(int x) {
		return c::eval(x);
	}
};

// Represents an addition in Polish notation
// ADD<VAL<1>,VAL<2>> = 1 + 2
template <class l, class r> class ADD {
public:
	static int eval(int x) {
		return l::eval(x) + r::eval(x);
	}
};

// Represents a subtraction in Polish notation
// SUB<VAL<1>,VAL<2>> = 1 - 2
template <class l, class r> class SUB {
public:
	static int eval(int x) {
		return l::eval(x) - r::eval(x);
	}
};

// Represents a multiplication in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 * 2
template <class l, class r> class MUL {
public:
	static int eval(int x) {
		return l::eval(x) * r::eval(x);
	}
};

// Represents a division in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 / 2
template <class l, class r> class DIV {
public:
	static int eval(int x) {
		return l::eval(x) / r::eval(x);
	}
};
