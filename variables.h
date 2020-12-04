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
extern size_t LON_MPI;
extern size_t LAT_MPI;
extern size_t NX;
extern size_t NY;
extern size_t NZ;
extern size_t NTIME;
extern const char *TIMEDIMENSION;

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
