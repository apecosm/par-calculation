#ifndef PAR_H
#define PAR_H

#include "boost_def.h"

#define NROWS 4
#define NCOLS 61

void init_zrgb(void);
void compute_par_c(ma3f &output, ma3f chl, ma2f qsr, ma3f e3t, ma3f tmask);

#endif
