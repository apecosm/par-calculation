#include <dirent.h>
#include <regex>
#include <vector>
#include "string_util.h"
#include "netcdf.h"
#include "boost_def.h"
#include "variables.h"
#include "ncio.h"

void read_var(ma3f &var, const char *filename, const char *varname, int i0) { 
    
    int status;
    int ncid;
    int varid;
    
    status = nc_open(filename, NC_NOWRITE, &ncid);
    status = nc_inq_varid(ncid, varname, &varid);
    
    int count[] = {i0, 0, get_ny(mpiRank), get_nx(mpiRank)};
    int start[] = {1, NZ, get_jstart(mpiRank), get_istart(mpiRank)};
    
    status = nc_get_var_float(ncid, varid, var.data());
    
    status = nc_close(ncid);
    
}

void read_var(ma2f &var, const char *filename, const char *varname, int i0) { 
    
    int status;
    int ncid;
    int varid;
    
    status = nc_open(filename, NC_NOWRITE, &ncid);
    status = nc_inq_varid(ncid, varname, &varid);
    
    int start[] = {i0, get_ny(mpiRank), get_nx(mpiRank)};
    int count[] = {1, get_jstart(mpiRank), get_istart(mpiRank)};
    
    status = nc_get_var_float(ncid, varid, var.data());
    status = nc_close(ncid);
    
}