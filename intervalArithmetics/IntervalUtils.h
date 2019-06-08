#pragma once
#include "stdafx.h"

using namespace std;

/*
bool contains(interval& i, mpreal v) {
	return i.a <= v && v <= i.b;
}

void print(interval& number, ostream& out) {
	out << "[ " << number.a << ",\t  " << number.a << " ]";
}
*/

/*
void scannn(GaussJordanMatrix& matrix, istream& in) {
	in >> matrix.m;
	matrix.n = matrix.m + 1;
	long double v;

	interval zero = interval(0, 0);
	interval one = interval(1, 1);
	for (int y = 0; y < matrix.m; y++) {
		row r;
		row r2;
		for (int x = 0; x < matrix.n; x++) {
			in >> v;
			interval i(v,v);
			r.push_back(i);

			if (x == y) {
				r2.push_back(one);
			}
			else {
				r2.push_back(zero);
			}
		}
		matrix.matrix.push_back(r);
	}
}
*/

/*
void print(GaussJordanMatrix& matrix, ostream& out) {
	out << "\nCurrent matrix:\n";
	for (int y = 0; y < matrix.m; y++) {
		for (int x = 0; x < matrix.n; x++) {
			print(matrix.matrix[y][x], out);
		}
		out << endl;
	}
	out << "Current matrix reversed:\n";
	for (int y = 0; y < matrix.m; y++) {
		for (int x = 0; x < matrix.n - 1; x++) {
			print(matrix.matrix2[y][x], out);
		}
		out << endl;
	}
}
*/