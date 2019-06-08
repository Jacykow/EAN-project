#pragma once
#include <boost/numeric/interval.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <mpreal.h>
#include "Interval.h"
#include "IntervalUtils.h"
#include "GaussJordanMatrix.h"

#define interval interval_arithmetic::Interval<long double>

using mpfr::mpreal;
using std::cout;