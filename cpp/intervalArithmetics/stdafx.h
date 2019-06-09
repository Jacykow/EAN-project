#pragma once
#include <boost/numeric/interval.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Interval.h"
#define real long double
#define interval interval_arithmetic::Interval<real>
#define row vector<interval>
#include "IntervalUtils.h"
#include "GaussJordanMatrix.h"