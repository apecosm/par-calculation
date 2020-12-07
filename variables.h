#ifndef VARIABLES_H
#define VARIABLES_H

#include "boost_def.h"

/** ###########################################
 * TO be modified by the user
 *  ########################################### */

/** Number of tiles along X */
#define LON_MPI 2

/** Number of tiles along Y */
#define LAT_MPI 2

/** Number of points along X */
#define NX 32
/** Number of points along Y */
#define NY 22
/** Number of points along Z */
#define NZ 31
/** Number of time steps to process */
#define NTIME 12

/** if defined, use variable layer thickness instead of e3t_0 */
#undef VVL

/** if defined, use a parfrac file to convert qsr into par */
#undef PARFRAC

/** Define the name of the time dimension in the file. */
#define TIMEDIMENSION "time_counter"

#ifdef PARFRAC
/** Name of the Parfrac file */
#define parfrac_file "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc"

/** Number of time steps in the par frac file. */
#define NFRAC 12

/** Name of the PAR FRAC variable */
#define parfrac_var "soshfldo"
#endif

/** Name of the mesh_mask file */
#define mesh_mask "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/new_mesh_mask.nc"

/** Pattern of the Chl files to read */
#define chl_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc"
/** Name of the Chl variable */
#define chl_var "Chltot"
/** Conversion factor to convert Chl in mg/m3 */
#define conversion_chl 1.0

/** Pattern of the Chl files to read */
#define qsr_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc"
/** Name of the qsr variable to read */
#define qsr_var "soshfldo"

#ifdef VVL
/** Pattern of the e3t files to read */
#define e3t_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc"
/** Name of the e3t variable to read */
#define e3t_var "votemper"
#endif

/** Prefix of the file (warning, no .nc, generated by the program) */
#define output_prefix "clim_GYRE_5d_00010101_00101231_PAR"
/** Name of the output variable. */
#define output_var "par"
/** Number of time steps in an output file. */
#define output_frequency 2

/** ###########################################
 * Do not modifiy
 *  ########################################### */

// Macros to recover MPI sub-domain
#define get_istart(p) (istart[(int)(p % LON_MPI)])
#define get_iend(p) (iend[(int)(p % LON_MPI)])
#define get_jstart(p) (jstart[(int)(p / LON_MPI)])
#define get_jend(p) (jend[(int)(p / LON_MPI)])
#define get_nx(p) (get_iend(p) - get_istart(p) + 1)
#define get_ny(p) (get_jend(p) - get_jstart(p) + 1)

/** Processors index to process. */
extern ma1iu istart;
extern ma1iu iend;
extern ma1iu jstart;
extern ma1iu jend;

extern int mpiRank;
extern int mpiSize;

#endif
