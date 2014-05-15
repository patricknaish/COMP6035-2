#include "part2.hpp"

int main() {
	try {
		// (x + 3) * (x + 5), x_{0,5}
		printf("Actual value : %d\n", EXP<MUL<ADD<VAR<BOUNDS<0,5>>,VAL<3>>,ADD<VAR<BOUNDS<0,5>>,VAL<5>>>>::eval(2));
	} catch (exception &e) {
		cout << e.what() << endl;
	}
}
