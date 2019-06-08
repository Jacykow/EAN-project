#ifndef GAUSSJORDANMATRIX_H
#define GAUSSJORDANMATRIX_H

#include <vector>
#include "Interval.h"

#define real long double
#define interval interval_arithmetic::Interval<real>
#define row vector<interval>

using namespace std;

class GaussJordanMatrix {
public:
	int m;
	int n;
	vector<vector<interval> > matrix;

	GaussJordanMatrix() {
		m = 0;
		n = 0;
	}

	void calculate() {
		interval zero = interval(0,0);
		interval one = interval(1,1);
		for (int a = 0; a < n - 1; a++) {
			int b = a;
			while (b < m) {
				if (!contains(matrix[b][a],0)) {
					break;
				}
				b++;
			}
			if (b >= m) {
				cout << a << endl;
				throw "Empty column!";
			}
			if (b > a) {
				cout << "swapping: " << a << " and " << b << endl;
				vector<interval> temp = matrix[b];
				matrix[b] = matrix[a];
				matrix[a] = temp;
			}

			for (int x = a + 1; x < n; x++) {
				matrix[b][x] = matrix[b][x] / matrix[b][a];
			}
			matrix[b][a] = one;

			for (int y = 0; y < m; y++) {
				if (y == b)continue;
				for (int x = a + 1; x < n; x++) {
					matrix[y][x] = matrix[y][x] - matrix[y][a] * matrix[b][x];
				}
				matrix[y][a] = zero;
			}
		}
	}

	bool contains(interval& i, real v) {
		return i.a <= v && v <= i.b;
	}

	void scan(istream& in) {
		in >> m;
		n = m + 1;
		real v;

		interval zero = interval(0, 0);
		interval one = interval(1, 1);
		for (int y = 0; y < m; y++) {
			row r;
			row r2;
			for (int x = 0; x < n; x++) {
				in >> v;
				interval i(v, v);
				r.push_back(i);

				if (x == y) {
					r2.push_back(one);
				}
				else {
					r2.push_back(zero);
				}
			}
			matrix.push_back(r);
		}
	}

	void printAnswer(ostream& out) {
		out << "\nAnswer:\n";
		for (int y = 0; y < m; y++) {
			print(matrix[y][n-1], out);
			out << endl;
		}
	}

	void printMatrix(ostream& out) {
		out << "\nMatrix:\n";
		for (int y = 0; y < m; y++) {
			for (int x = 0; x < n-1; x++) {
				print(matrix[y][x], out);
			}
			out << endl;
		}
	}

private:
	void print(interval& number, ostream& out) {
		string left, right;
		number.IEndsToStrings(left, right);
		out << "[ " << left << ",\t" << right << "]";
	}
};

#endif