#include <dirent.h>
#include <regex>
#include <vector>
#include "string_util.h"
#include "netcdf.h"
#include "boost_def.h"
#include "variables.h"

void read_var(ma3d &var, const char *filename, const char *varname, size_t istart) { 
    
    int status;
    int ncid;
    int varid;
    
    status = nc_open(filename, NC_NOWRITE, &ncid);
    status = nc_inq_varid(ncid, varname, &varid);
    size_t start[] = {istart, 0, 0, 0};
    size_t count[] = {1, NZ, NY, NX};
    
    
    
    
}