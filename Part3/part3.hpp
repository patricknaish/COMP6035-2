#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <climits>

using namespace std;

// Exception for an out-of-range variable definition
class rangeException: public exception {
public:
	virtual const char* what() const throw() {
		return "Variable out of range";
	}
};

// Variadic template for finding a minimum value (passes through)
template <int... Values> struct MIN {};

// Variadic template for finding a minimum value recursively
template <int Value, int... Values> struct MIN <Value, Values...> {
	enum {
		apply = Value < MIN<Values...>::apply ? Value : MIN<Values...>::apply
	};
};

// Recursive base case for minimum values
template <> struct MIN <> {
	enum {
		apply = INT_MAX
	};
};

// Variadic template for finding a maximum value (passes through)
template <int... Values> struct MAX{};

// Variadic template for finding a maximum value recursively
template <int Value, int... Values> struct MAX <Value, Values...> {
	enum {
		apply = Value > MAX<Values...>::apply ? Value : MAX<Values...>::apply
	};
};

// Recursive base case for maximum values
template <> struct MAX <> {
	enum {
		apply = INT_MIN
	};
};

// Represents a raw value
// VAL<1> = 1
template <int i> class VAL {
public:
	static inline int eval(int vals[]) {
		return i;
	};
	enum {
		lower = i,
		higher = i
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
	enum {
		lower = b::lower,
		higher = b::higher
	};
};

// Represents an expression at the highest level
template <class e> class EXP {
public:
	static inline int eval(int vals[]) {
		varIndex = 0;
		int returnvalue = e::eval(vals);
#ifdef PRINTBOUNDS
		printf("Lower bound  : %d\n", e::lower;
		printf("Higher bound : %d\n", e::higher;
#endif
		return returnvalue;
	};
	enum {
		lower = e::lower,
		higher = e::higher
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
	enum {
		lower = l::lower + r::lower,
		higher = l::higher + r::higher
	};
};

// Represents a subtraction in Polish notation
// SUB<VAL<1>,VAL<2>> = 1 - 2
template <class l, class r> class SUB {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) - r::eval(vals);
	};
	enum {
		lower = l::lower - r::lower,
		higher = l::higher - r::higher
	};
};

// Represents a multiplication in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 * 2
template <class l, class r> class MUL {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) * r::eval(vals);
	};
	enum {
		lower = MIN<l::lower * r::lower, l::lower * r::higher, l::higher * r::lower, l::higher * r::higher>::apply,
		higher = MAX<l::lower * r::lower, l::lower * r::higher, l::higher * r::lower, l::higher * r::higher>::apply
	};
};

// Represents a division in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 / 2
template <class l, class r> class DIV {
public:
	static inline int eval(int vals[]) {
		return l::eval(vals) / r::eval(vals);
	};
	enum {
		lower = (r::lower < -1 && r::higher > 0) ? (int)MIN<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher, l::lower / -1, l::lower / 1, l::higher / -1, l::higher / 1>::apply : (int)MIN<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher>::apply,
		higher = (r::lower < -1 && r::higher > 0) ? (int)MAX<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher, l::lower / -1, l::lower / 1, l::higher / -1, l::higher / 1>::apply : (int)MAX<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher>::apply
	};
};
