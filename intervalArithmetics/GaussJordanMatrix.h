#pragma once
#ifndef GAUSSJORDANMATRIX_HEADER
#define GAUSSJORDANMATRIX_HEADER

#include "stdafx.h"

using namespace std;

class GaussJordanMatrix {
public:
	int m;
	int n;
	vector<vector<interval> > matrix;
	vector<vector<interval> > matrix2;

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
				if (matrix[b][a].b==0) {
					break;
				}
				b++;
			}
			if (b > a) {
				cout << "swapping: " << a << " and " << b << endl;
				vector<interval> temp = matrix[b];
				matrix[b] = matrix[a];
				matrix[a] = temp;

				temp = matrix2[b];
				matrix2[b] = matrix2[a];
				matrix2[a] = temp;
			}
			if (b >= m) {
				cout << a << endl;
				throw "Empty column!";
			}

			for (int x = 0; x < n - 1; x++) {
				//matrix2[b][x] = matrix2[b][x] / matrix[b][a];
			}
			for (int x = a + 1; x < n; x++) {
				//matrix[b][x] = matrix[b][x] / matrix[b][a];
			}
			//matrix[b][a] = one;

			for (int y = 0; y < m; y++) {
				if (y == b)continue;
				for (int x = 0; x < n - 1; x++) {
					//matrix2[y][x] = matrix2[y][x] - matrix[y][a] * matrix2[b][x];
				}
			}
			for (int y = 0; y < m; y++) {
				if (y == b)continue;
				for (int x = a + 1; x < n; x++) {
					//matrix[y][x] = matrix[y][x] - matrix[y][a] * matrix[b][x];
				}
				//matrix[y][a] = zero;
			}
		}
	}
};

#endif