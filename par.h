#ifndef PAR_H
#define PAR_H

#include "boost_def.h"

#define NROWS 4
#define NCOLS 61

void init_zrgb(void);
void compute_par_c(ma3d &output, ma3d chl, ma2d qsr, ma3d e3t, ma3d tmask);

#endif
