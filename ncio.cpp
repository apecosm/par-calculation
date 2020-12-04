#include <dirent.h>
#include <regex>
#include <vector>
#include <mpi.h>
#include "string_util.h"
#include "netcdf.h"
#include "boost_def.h"
#include "variables.h"
#include "ncio.h"

size_t get_ntime_file(const char *filename) {
    
    int ncid;
    int status;
    int dimid;
    size_t nsteps;
    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    status = nc_inq_dimid(ncid, TIMEDIMENSION, &dimid);
    status = nc_inq_dimlen(ncid, dimid, &nsteps);
}

void read_var(ma3f &var, const char *filename, const char *varname, size_t i0) { 
    
    int status;
    int ncid;
    int varid;
    
    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);
    
    var.resize(boost::extents[NZ][ny][nx]);
    
    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    
    status = nc_open(filename, NC_NOWRITE, &ncid);
    status = nc_inq_varid(ncid, varname, &varid);
    
    size_t count[] = {1, NZ, ny, nx};
    size_t start[] = {i0, 0, get_jstart(mpiRank), get_istart(mpiRank)};

    if (mpiRank == 0) {
        printf("count = %d, %d, %ld, %ld\n", 1, NZ, ny, nx);
        printf("start = %ld, %d, %ld, %ld\n", i0, 0, get_jstart(mpiRank), get_istart(mpiRank));
    }

    status = nc_get_vara_float(ncid, varid, start, count, var.data());

    if (mpiRank == 0) {
        for (int k = 0; k < 1; k++) {
            for (int j = 0; j < ny; j++) {
                for (int i = 0; i < nx; i++) {
                    printf("k=%d, j=%d, i=%d, var=%f\n", k, j, i, var[k][j][i]);
                }
            }
        }
    }

    status = nc_close(ncid);
    
}

void read_var(ma2f &var, const char *filename, const char *varname, size_t i0) { 
    
    int status;
    int ncid;
    int varid;

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

    var.resize(boost::extents[ny][nx]);

    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    status = nc_inq_varid(ncid, varname, &varid);
    
    size_t start[] = {i0, get_jstart(mpiRank), get_istart(mpiRank)};
    size_t count[] = {1, ny, nx};
    
    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    status = nc_close(ncid);
    
}
