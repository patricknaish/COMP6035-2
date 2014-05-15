#include "part3.hpp"

int main() {
	try {
		int outputs[4];
		int vals[3];

		// x + (y - 2) * (z - 3), x_{0,3}, y_{0,5}, z_{0,7}

		// x = 1, y = 3, z = 5
		vals[0] = 1;
		vals[1] = 3;
		vals[2] = 5;
		outputs[0] = EXP<ADD<VAR<BOUNDS<0,3>>,MUL<SUB<VAR<BOUNDS<0,5>>,VAL<2>>,SUB<VAR<BOUNDS<0,7>>,VAL<3>>>>>::eval(vals);

		// x = 0, y = 5, z = 0 (minimum possible value)
		vals[0] = 0;
		vals[1] = 5;
		vals[2] = 0;
		outputs[1] = EXP<ADD<VAR<BOUNDS<0,3>>,MUL<SUB<VAR<BOUNDS<0,5>>,VAL<2>>,SUB<VAR<BOUNDS<0,7>>,VAL<3>>>>>::eval(vals);

		// x = 3, y = 5, z = 7 (maximum possible value)
		vals[0] = 3;
		vals[1] = 5;
		vals[2] = 7;
		outputs[2] = EXP<ADD<VAR<BOUNDS<0,3>>,MUL<SUB<VAR<BOUNDS<0,5>>,VAL<2>>,SUB<VAR<BOUNDS<0,7>>,VAL<3>>>>>::eval(vals);

		// x = 0, y = 0, z = 0
		vals[0] = 0;
		vals[1] = 0;
		vals[2] = 0;
		outputs[3] = EXP<ADD<VAR<BOUNDS<0,3>>,MUL<SUB<VAR<BOUNDS<0,5>>,VAL<2>>,SUB<VAR<BOUNDS<0,7>>,VAL<3>>>>>::eval(vals);

		printf("outputs[0]: %d\n",outputs[0]);
		printf("outputs[1]: %d\n",outputs[1]);
		printf("outputs[2]: %d\n",outputs[2]);
		printf("outputs[3]: %d\n",outputs[3]);

	} catch (exception &e) {
		cout << e.what() << endl;
	}
}
