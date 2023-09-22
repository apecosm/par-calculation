#ifndef VARIABLES_DEF_H
#define VARIABLES_DEF_H

#include "boost_def.h"
#include <iostream>
#include <map>
#include <string>

/** ###########################################
 * Do not modifiy
 *  ########################################### */

/** Processors index to process. */
ma1iu istart;
ma1iu iend;
ma1iu jstart;
ma1iu jend;

int mpiRank;
int mpiSize;

// Define external variables for storing variables

/** Number of tiles along X */
int LON_MPI;

/** Number of tiles along Y */
int LAT_MPI;

/** Number of points along X */
size_t NX;

/** Number of points along Y */
size_t NY;

/** Number of points along Z */
size_t NZ;

/** Number of time steps to process */
int NTIME;


/** Define the name of the time dimension in the file. */
string time_dimension;

/** Name of the Parfrac file */
string parfrac_file;

/** Number of time steps in the par frac file. */
size_t NFRAC;

/** Name of the PAR FRAC variable */
string parfrac_var;

/** Name of the mesh_mask file */
string mesh_mask;

/** Pattern of the Chl files to read */
string chl_pattern;
/** Name of the Chl variable */
string chl_var;
/** Conversion factor to convert Chl in mg/m3 */
double conversion_chl;

/** Pattern of the Chl files to read */
string qsr_pattern;
/** Name of the qsr variable to read */
string qsr_var;

/** Pattern of the e3t files to read */
string e3t_pattern;
/** Name of the e3t variable to read */
string e3t_var;

/** Prefix of the file (warning, no .nc, generated by the program) */
string output_prefix;
/** Name of the output variable. */
string output_var;
/** Number of time steps in an output file. */
int output_frequency;

bool use_vvl;
bool use_parfrac;

std::map<std::string, std::string> parameters;

#endif
