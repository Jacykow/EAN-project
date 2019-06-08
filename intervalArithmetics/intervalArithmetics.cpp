#pragma once
#include "stdafx.h"

int main(int argc, char* argv[])
{
	const int digits = 50;

	mpreal::set_default_prec(mpfr::digits2bits(digits));

	cout << "START\n";

	GaussJordanMatrix matrix;

	fstream in;
	in.open("data.in", ios::in);
	//scan(matrix, in);
	in.close();

	//matrix.calculate();
	//print(matrix, cout);

	fstream out;
	out.open("data.out", ios::out);
	//print(matrix, out);
	out.close();

	cout << "DONE\n";

	return 0;
}
