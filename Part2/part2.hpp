#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <climits>

#define PRINTBOUNDS

using namespace std;

// Exception for an out-of-range variable definition
class rangeException: public exception {
public:
	virtual const char* what() const throw() {
		return "Variable out of range";
	}
};

template <int Value=INT_MAX, int... Values> struct MIN {
	enum {
		RET = Value < MIN<Values...>::RET ? Value : MIN<Values...>::RET
	};
};

template <> struct MIN <> {
	enum {
		RET = INT_MAX
	};
};

template <int Value=INT_MIN, int... Values> struct MAX {
	enum {
		RET = Value > MAX<Values...>::RET ? Value : MAX<Values...>::RET
	};
};

template <> struct MAX <> {
	enum {
		RET = INT_MIN
	};
};

// Represents a raw value
// VAL<1> = 1
template <int i> class VAL {
public:
	static inline int eval(int x) {
		return i;
	};
	enum {
		lower = i,
		higher = i
	};
};

// Represents the variable x, with bounds
// VAR<BOUND<0,10>> = x_{0,10}
template <class b> class VAR {
public:
	static inline int eval(int x) {
		if (x < b::lower || x > b::higher) {
			throw rangeException();
		};
		return x;
	};
	enum {
		lower = b::lower,
		higher = b::higher
	};
};

// Represents an expression at the highest level
template <class e> class EXP {
public:
	static inline int eval(int x) {
		int returnvalue = e::eval(x);
#ifdef PRINTBOUNDS
		printf("Lower bound  : %d\n", e::lower);
		printf("Higher bound : %d\n", e::higher);
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
	static inline int eval(int x) {
		return l::eval(x) + r::eval(x);
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
	static inline int eval(int x) {
		return l::eval(x) - r::eval(x);
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
	static inline int eval(int x) {
		return l::eval(x) * r::eval(x);
	};
	enum {
		lower = MIN<l::lower * r::lower, l::lower * r::higher, l::higher * r::lower, l::higher * r::higher>::RET,
		higher = MAX<l::lower * r::lower, l::lower * r::higher, l::higher * r::lower, l::higher * r::higher>::RET
	};
};

// Represents a division in Polish notation
// MUL<VAL<1>,VAL<2>> = 1 / 2
template <class l, class r> class DIV {
public:
	static inline int eval(int x) {
		return l::eval(x) / r::eval(x);
	};
	enum {
		lower = (r::lower < -1 && r::higher > 0) ? (int)MIN<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher, l::lower / -1, l::lower / 1, l::higher / -1, l::higher / 1>::RET : (int)MIN<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher>::RET,
		higher = (r::lower < -1 && r::higher > 0) ? (int)MAX<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher, l::lower / -1, l::lower / 1, l::higher / -1, l::higher / 1>::RET : (int)MAX<l::lower / r::lower, l::lower / r::higher, l::higher / r::lower, l::higher / r::higher>::RET
	};
};
