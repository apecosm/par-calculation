#ifndef VARIABLES_H
#define VARIABLES_H

#include "boost_def.h"

#define LON_MPI 2
#define LAT_MPI 2
#define NX 32
#define NY 22
#define NZ 31
#define NTIME 73

// Macros to recover MPI sub-domain
#define get_istart(p) (istart[(int) (p % LON_MPI)])
#define get_iend(p) (iend[(int) (p % LON_MPI)])
#define get_jstart(p) (jstart[(int) (p / LON_MPI)])
#define get_jend(p) (jend[(int) (p / LON_MPI)])
#define get_nx(p) (get_iend(p) - get_istart(p) + 1)
#define get_ny(p) (get_jend(p) - get_jstart(p) + 1)

/** Processors index to process. */
extern ma1i istart;
extern ma1i iend;
extern ma1i jstart;
extern ma1i jend;

extern int mpiRank;
extern int mpiSize;

#endif