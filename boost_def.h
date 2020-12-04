/** 
 * \file OOPE_definitions.h
 * \author P.Verley
 * 
 * \brief Defines some types, the main variables and declares main functions of the
 * program.
 *
 * \date 27 March 2014, 13:52
 */

#ifndef OOPE_DEFINITIONS_H
#define OOPE_DEFINITIONS_H

#include "boost/multi_array.hpp"

//////////////////
// Type definition
//////////////////

// double[]
typedef boost::multi_array<double, 1> ma1d;
// double[][]
typedef boost::multi_array<double, 2> ma2d;
// double[][][]
typedef boost::multi_array<double, 3> ma3d;
// double[][][][]
typedef boost::multi_array<double, 4> ma4d;
// double[][][][][]
typedef boost::multi_array<double, 5> ma5d;

typedef ma1d::index_range range_ma1d;
// 3d range for double array {i, j}
typedef ma2d::index_range range_ma2d;
// 3d range for double array {i, j, k}
typedef ma3d::index_range range_ma3d;
// 4d range for double array {i, j, k, l}
typedef ma4d::index_range range_ma4d;
typedef ma5d::index_range range_ma5d;

// int[]
typedef boost::multi_array<int, 1> ma1i;
// int[][]
typedef boost::multi_array<int, 2> ma2i;
// int[][][]
typedef boost::multi_array<int, 3> ma3i;
// size_t[]
typedef boost::multi_array<size_t, 1> ma1iu;
// size_t[][]
typedef boost::multi_array<size_t, 2> ma2iu;
// size_t[][][]
typedef boost::multi_array<size_t, 3> ma3iu;

// float[]
typedef boost::multi_array<float, 1> ma1f;
// float[][]
typedef boost::multi_array<float, 2> ma2f;
// float[][][]
typedef boost::multi_array<float, 3> ma3f;
// float[][][][]
typedef boost::multi_array<float, 4> ma4f;
// float[][][][][]
typedef boost::multi_array<float, 5> ma5f;

// boolea[]
typedef boost::multi_array<bool, 1> ma1b;
// boolean[][]
typedef boost::multi_array<bool, 2> ma2b;

#endif
