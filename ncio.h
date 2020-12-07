#ifndef NCIO_H
#define NCIO_H

#include "boost_def.h"

void read_var(ma3d &var, const char *filename, const char *varname, size_t i0, double conversion=1.0);
void read_var(ma2d &var, const char *filename, const char *varname, size_t i0, double conversion=1.0);
void read_parfrac(ma3d &var, const char *filename, const char *varname);
size_t get_ntime_file(const char *filename);
void define_output_file(int cpt);
void write_step(int cpt, int step, ma3d var, int time);

#endif
