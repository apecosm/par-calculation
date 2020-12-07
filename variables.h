#ifndef VARIABLES_H
#define VARIABLES_H

#include "boost_def.h"

/*
#define LON_MPI 1
#define LAT_MPI 1
#define NX 32
#define NY 22
#define NZ 31
#define NTIME 73

#define TIMEDIMENSION "time_counter"
#define VVL
*/


#define LON_MPI 1
#define LAT_MPI 1
#define NX 32
#define NY 22
#define NZ 31
#define NTIME 73

#define TIMEDIMENSION "time_counter"
#define VVL

#define mesh_mask "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/mesh_mask.nc"

#define chl_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc"
#define chl_var "Chltot"

#define qsr_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc"
#define qsr_var "soshfldo"

#ifdef VVL
#define e3t_pattern "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc"
#define e3t_var "votemper"
#endif

#define output_prefix "clim_GYRE_5d_00010101_00101231_PAR"
#define output_var "par"
#define output_frequency 73

// Macros to recover MPI sub-domain
#define get_istart(p) (istart[(int) (p % LON_MPI)])
#define get_iend(p) (iend[(int) (p % LON_MPI)])
#define get_jstart(p) (jstart[(int) (p / LON_MPI)])
#define get_jend(p) (jend[(int) (p / LON_MPI)])
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
