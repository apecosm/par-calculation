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

#include <boost/multi_array.hpp>

//////////////////
// Type definition
//////////////////

// double[]
typedef boost::multi_array<double, 1> ma1d;
typedef boost::multi_array<double, 2> ma2d;
typedef boost::multi_array<double, 3> ma3d;
typedef boost::multi_array<double, 4> ma4d;
typedef boost::multi_array<double, 5> ma5d;

typedef ma1d::index_range range_ma1d;
typedef ma2d::index_range range_ma2d;
typedef ma3d::index_range range_ma3d;
typedef ma4d::index_range range_ma4d;
typedef ma5d::index_range range_ma5d;


typedef boost::multi_array<int, 1> ma1i;
typedef boost::multi_array<int, 2> ma2i;
typedef boost::multi_array<int, 3> ma3i;

typedef boost::multi_array<size_t, 1> ma1iu;
typedef boost::multi_array<size_t, 2> ma2iu;
typedef boost::multi_array<size_t, 3> ma3iu;

typedef boost::multi_array<float, 1> ma1f;
typedef boost::multi_array<float, 2> ma2f;
typedef boost::multi_array<float, 3> ma3f;
typedef boost::multi_array<float, 4> ma4f;
typedef boost::multi_array<float, 5> ma5f;

typedef boost::multi_array<short, 1> ma1b;
typedef boost::multi_array<short, 2> ma2b;
typedef boost::multi_array<short, 3> ma3b;

#endif
