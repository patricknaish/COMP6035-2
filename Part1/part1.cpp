#include "part1.hpp"

int main() {
	// x + (x - 2) * (x - 3)
	printf("Actual value : %d\n", EXP<ADD<VAR,MUL<SUB<VAR,VAL<2>>,SUB<VAR,VAL<3>>>>>::eval(5));
}
