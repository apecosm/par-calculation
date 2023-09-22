#ifndef NCIO_H
#define NCIO_H

#include "boost_def.h"

void read_var(ma3f &var, const std::string filename, const std::string varname, size_t i0, double conversion=1.0);
void read_var(ma2f &var, const std::string filename, const std::string varname, size_t i0, double conversion=1.0);
void read_parfrac(ma3f &var, const std::string filename, const std::string varname);
void read_gridvar(ma3f &var, const std::string filename, const std::string varname);
size_t get_ntime_file(std::string filename);
void define_output_file(int cpt);
void write_step(int cpt, int step, ma3f var, int time);

void read_parameters(std::string filename);
void set_parameters();

#endif
