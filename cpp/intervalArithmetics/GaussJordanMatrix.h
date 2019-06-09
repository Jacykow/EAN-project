#ifndef GAUSSJORDANMATRIX_H
#define GAUSSJORDANMATRIX_H

#include <vector>
#include "Interval.h"

#define real long double
#define interval interval_arithmetic::Interval<real>

using namespace std;

class GaussJordanAnswer {
public:
	real left;
	real right;
	real value() {
		real value = 2;
		return (left + right) / value;
	}
};

class GaussJordanMatrix {
public:
	const char* ERROR_NO_ANSWER = "No answer";
	int m;
	int n;
	vector<vector<interval> > matrix;
	vector<GaussJordanAnswer> answer;

	GaussJordanMatrix() {
		m = 0;
		n = 0;
	}

	void calculate() {
		real zeroR = 0;
		real oneR = 0;
		interval zero = interval(zeroR, zeroR);
		interval one = interval(oneR, oneR);
		for (int a = 0; a < n - 1; a++) {
			int b = a;
			while (b < m) {
				if (!contains(matrix[b][a], zeroR)) {
					break;
				}
				b++;
			}
			if (b >= m) {
				throw exception(ERROR_NO_ANSWER);
			}
			if (b > a) {
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
		for (int y = 0; y < m; y++) {
			GaussJordanAnswer a;
			a.left = matrix[y][n - 1].a;
			a.right = matrix[y][n - 1].b;
			answer.push_back(a);
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
			vector<interval> r;
			for (int x = 0; x < n; x++) {
				in >> v;
				interval i(v, v);
				r.push_back(i);
			}
			matrix.push_back(r);
		}
	}

	void printAnswer(ostream& out) {
		out.setf(std::ios_base::scientific);
		for (int y = 0; y < answer.size(); y++) {
			print(answer[y].value(), out);
			out << endl;
			print(answer[y].left, out);
			out << endl;
			print(answer[y].right, out);
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
	void print(real number, ostream& out) {
		out.setf(std::ios_base::scientific);
		out << ((number > 0) ? " " : "") << std::setprecision(14) << number;
	}

	void print(interval& number, ostream& out) {
		out << "[";
		print(number.a, out);
		out << ",";
		print(number.b, out);
		out << ",";
		real middle = 2;
		middle = (number.a + number.b) / middle;
		print(middle, out);
		out << "]";
	}
};

#endif