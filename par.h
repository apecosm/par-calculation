#ifndef PAR_H
#define PAR_H

#include "boost_def.h"

#define NROWS 4
#define NCOLS 61


void init_zrgb(void);
void compute_par_c(void);

// Dimnsion: CHL concentration; R/G/B
ma2f zrgb(boost::extents[NROWS][NCOLS]);

#endif
