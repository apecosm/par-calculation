#ifndef VARIABLES_H
#define VARIABLES_H

#include "boost_def.h"
#include <iostream>
#include <map>
#include <string>

/** ###########################################
 * Do not modifiy
 *  ########################################### */

/** Processors index to process. */
extern ma1iu istart;
extern ma1iu iend;
extern ma1iu jstart;
extern ma1iu jend;

extern int mpiRank;
extern int mpiSize;

// Define external variables for storing variables

/** Number of tiles along X */
extern int LON_MPI;

/** Number of tiles along Y */
extern int LAT_MPI;

/** Number of points along X */
extern size_t NX;

/** Number of points along Y */
extern size_t NY;

/** Number of points along Z */
extern size_t NZ;

/** Number of time steps to process */
extern int NTIME;


/** Define the name of the time dimension in the file. */
extern char* TIMEDIMENSION;

/** Name of the Parfrac file */
extern char* parfrac_file;

/** Number of time steps in the par frac file. */
extern int NFRAC;

/** Name of the PAR FRAC variable */
extern char* parfrac_var;

/** Name of the mesh_mask file */
extern char* mesh_mask;

/** Pattern of the Chl files to read */
extern char* chl_pattern;
/** Name of the Chl variable */
extern char* chl_var;
/** Conversion factor to convert Chl in mg/m3 */
extern double conversion_chl;

/** Pattern of the Chl files to read */
extern char* qsr_pattern;
/** Name of the qsr variable to read */
extern char* qsr_var;

/** Pattern of the e3t files to read */
extern char* e3t_pattern;
/** Name of the e3t variable to read */
extern char* e3t_var;

/** Prefix of the file (warning, no .nc, generated by the program) */
extern char* output_prefix;
/** Name of the output variable. */
extern char* output_var;
/** Number of time steps in an output file. */
extern int output_frequency;

extern std::map<std::string, std::string> parameters;

// Macros to recover MPI sub-domain
#define get_istart(p) (istart[(int)(p % LON_MPI)])
#define get_iend(p) (iend[(int)(p % LON_MPI)])
#define get_jstart(p) (jstart[(int)(p / LON_MPI)])
#define get_jend(p) (jend[(int)(p / LON_MPI)])
#define get_nx(p) (get_iend(p) - get_istart(p) + 1)
#define get_ny(p) (get_jend(p) - get_jstart(p) + 1)

#endif
