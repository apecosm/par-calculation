#ifndef NCIO_H
#define NCIO_H

#include <vector>
#include "boost_def.h"

using namespace std;

void read_var(ma3f &var, const string filename, const string varname, size_t i0, double conversion=1.0);
void read_var(ma2f &var, const string filename, const string varname, size_t i0, double conversion=1.0);
void read_parfrac(ma3f &var, const string filename, const string varname);
void read_gridvar(ma3f &var, const string filename, const string varname);
size_t get_ntime_file(string filename);
size_t get_total_ntime(vector<string> filelist);
void define_output_file(int cpt);
void write_step(int cpt, int step, ma3f var, int time);
size_t get_spatial_dimension_file(string filename, string dimname);

void read_parameters(string filename);
void set_parameters();

#endif
