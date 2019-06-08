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
	in.open("data.in", ios::in);
	matrix.scan(in);
	in.close();

	try
	{
		matrix.calculate();
		matrix.printAnswer(cout);

		fstream out;
		out.open("data.out", ios::out);
		matrix.printAnswer(out);
		out.close();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	cout << "\nDONE\n";

	return 0;
}
