#ifndef NCIO_H
#define NCIO_H

#include "boost_def.h"
#include <netcdf.h>
#include <netcdf_par.h>

void read_var(ma3b &var, const char *filename, const char *varname, size_t i0);
void read_var(ma3f &var, const char *filename, const char *varname, size_t i0);
void read_var(ma2f &var, const char *filename, const char *varname, size_t i0);
size_t get_ntime_file(const char *filename);

#endif
