#include <iostream>
#include <fstream>
#include <windows.h>
#include "GaussJordanMatrix.h"

int main(int argc, char* argv[])
{
	GaussJordanMatrix matrix;
	matrix.scan(cin);

	try
	{
		matrix.calculate();
		matrix.printAnswer(cout);
		system("pause");
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		system("pause");
		return -1;
	}

	return 0;
}
