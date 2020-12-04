#ifndef MAIN_H
#define MAIN_H

#include "boost_def.h"

#define NROWS 4
#define NCOLS 61

// Dimnsion: CHL concentration; R/G/B
ma2f zrgb(boost::extents[NROWS][NCOLS]);

void init_zrgb(void);
void compute_par_c(void);
void init_mpi_domains(void);

#endif
