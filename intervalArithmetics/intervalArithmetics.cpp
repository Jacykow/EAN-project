#include <iostream>
#include <fstream>
#include "GaussJordanMatrix.h"
#include "IntervalUtils.h"

int main(int argc, char* argv[])
{
	const int digits = 50;

	cout << "START\n";

	GaussJordanMatrix matrix;

	fstream in;
	in.open("data2.in", ios::in);
	matrix.scan(in);
	in.close();

	matrix.calculate();
	matrix.printAnswer(cout);
	matrix.printAnswer(cout);
	matrix.printAnswer(cout);
	matrix.printAnswer(cout);

	fstream out;
	out.open("data.out", ios::out);
	//matrix.print(out);
	out.close();

	cout << "DONE\n";

	return 0;
}
