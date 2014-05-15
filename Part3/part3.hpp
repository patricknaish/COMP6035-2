#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

// Exception for an out-of-range variable definition
class rangeException: public exception {
public:
	virtual const char* what() const throw() {
		return "Variable out of range";
	}
};

// Represents a raw value
// VAL<1> = 1
template <int i> class VAL {
public:
	static inline int eval(int vals[]) {
		return i;
	};
	static inline int lower() {
		return i;
	};
	static inline int higher() {
		return i;
	};
};

// Represents the current position through the array of input values
static int varIndex;

// Represents a variable with bounds
// VAR<BOUND<0,10>> = x_{0,10}
template <class b> class VAR {
public:
	static inline int eval(int vals[]) {
		if (vals[varIndex] < b::lower || vals[varIndex] > b::higher) {
			throw rangeException();
		};
		return vals[varIndex++];
	};
	static inline int lower() {
		return b::lower;
	};
	static inline int higher() {
		return b::higher;
	};
};

// Represents an expression at the highest level
template <class e> class EXP {
public:
	static inline int eval(int vals[]) {
		varIndex = 0;
		int returnvalue = e::eval(vals);
#ifdef PRINTBOUNDS
		printf("Lower bound  : %d\n", e::lower());
		printf("Higher bound : %d\n", e::higher());
#endif
		return returnvalue;
	};
	static inline int lower() {
		return e::lower();
	};
	static inline int higher() {
		return e::higher();
	};
};

// Represents an upper and lower bound on a variable
// BOUND<0,10> = 0..10
template <int low, int high> class BOUNDS {
public:
	enum {
		lower = low,
		higher = high
	};
};

// Represents an addition in Polish notation
// ADD<VAL<1>,VAL<2>> = 1 + 2
template <class l, class r> class ADD {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) + r::eval(vals);
	};
	static inline int lower() {
		return l::lower() + r::lower();
	};
	static inline int higher() {
		return l::higher() + r::higher();
	};
};

// Represents a subtraction in Polish notation
// SUB<VAL<1>,VAL<2>> = 1 - 2
template <class l, class r> class SUB {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) - r::eval(vals);
	};
	static inline int lower() {
		return l::lower() - r::lower();
	};
	static inline int higher() {
		return l::higher() - r::higher();
	};
};

// Represents a multiplication in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 * 2
template <class l, class r> class MUL {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) * r::eval(vals);
	};
	static inline int lower() {
		return min(l::lower() * r::lower(), min(l::lower() * r::higher(), min(l::higher() * r::lower(), l::higher() * r::higher())));
	};
	static inline int higher() {
		return max(l::lower() * r::lower(), max(l::lower() * r::higher(), max(l::higher() * r::lower(), l::higher() * r::higher())));
	};
};

// Represents a division in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 / 2
template <class l, class r> class DIV {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) / r::eval(vals);
	};
	static inline int lower() {
		if (r::lower() < -1 && r::higher() > 0) {
			return min(l::lower() / r::lower(), min(l::lower() / r::higher(), min(l::higher() / r::lower(), min(l::higher() / r::higher(), min(l::lower() / -1, min(l::lower() / 1, min(l::higher() / -1, l::higher() / 1)))))));
		} else {
			return min(l::lower() / r::lower(), min(l::lower() / r::higher(), min(l::higher() / r::lower(), l::higher() / r::higher())));
		}
	};
	static inline int higher() {
		if (r::lower() < -1 && r::higher() > 0) {
			return max(l::lower() / r::lower(), max(l::lower() / r::higher(), max(l::higher() / r::lower(), max(l::higher() / r::higher(), max(l::lower() / -1, max(l::lower() / 1, max(l::higher() / -1, l::higher() / 1)))))));
		}
		return max(l::lower() / r::lower(), max(l::lower() / r::higher(), max(l::higher() / r::lower(), l::higher() / r::higher())));
	};
};
