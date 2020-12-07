#include "ncio.h"
#include "boost_def.h"
#include "string_util.h"
#include "variables.h"
#include <dirent.h>
#include <mpi.h>
#include <netcdf.h>
#include <netcdf_par.h>
#include <regex>
#include <vector>

#define ERRCODE 2
#define ERR(e)                                 \
    {                                          \
        printf("Error: %s\n", nc_strerror(e)); \
        exit(ERRCODE);                         \
    }

/** Get the number of time steps stored in a NetCDF output file 
 * 
*/
size_t get_ntime_file(const char *filename) {

    int ncid;
    int status;
    int dimid;
    size_t nsteps;

    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_inq_dimid(ncid, TIMEDIMENSION, &dimid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_inq_dimlen(ncid, dimid, &nsteps);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    return nsteps;
}

/** Reads a 3D (depth, y, x) variable from NetCDF. 
 * 
*/
void read_var(ma3f &var, const char *filename, const char *varname, size_t i0) {

    int status;
    int ncid;
    int varid;

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_inq_varid(ncid, varname, &varid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    size_t count[] = {1, NZ, ny, nx};
    size_t start[] = {i0, 0, get_jstart(mpiRank), get_istart(mpiRank)};

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        ERR(status);
    }

    printf("%s: reading %s, step=%ld\n", varname, filename, i0);

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }
}

/** Reads a 2D (y, x) output variable. 
 * 
*/
void read_var(ma2f &var, const char *filename, const char *varname, size_t i0) {

    int status;
    int ncid;
    int varid;

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_inq_varid(ncid, varname, &varid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    size_t start[] = {i0, get_jstart(mpiRank), get_istart(mpiRank)};
    size_t count[] = {1, ny, nx};

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    printf("%s: reading %s, step=%ld\n", varname, filename, i0);
}

void define_output_file(int cpt) {

    char ncfile[1096];
    sprintf(ncfile, "%s_%.05d.nc", output_prefix, cpt);

    int status;
    int ncid;
    int timeid;
    int yd, xd, zd;

    int nx = NX;
    int ny = NY;
    int nz = NZ;

    status = nc_create_par(ncfile, NC_CLOBBER | NC_NETCDF4 | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_def_dim(ncid, "time", NC_UNLIMITED, &timeid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_def_dim(ncid, "z", nz, &zd);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_def_dim(ncid, "y", ny, &yd);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_def_dim(ncid, "x", nx, &xd);
    if (status != NC_NOERR) {
        ERR(status);
    }

    int output_ids[] = {timeid, zd, yd, xd};
    int varid;

    status = nc_def_var(ncid, output_var, NC_FLOAT, 4, output_ids, &varid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_enddef(ncid); //end definitions: leave define mode
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }
}

void write_step(int cpt, int step, ma3f var) {

    int ncid, varid, status;

    char ncfile[1096];
    sprintf(ncfile, "%s_%.05d.nc", output_prefix, cpt);

    size_t nx = get_nx(mpiRank);
    size_t ny = get_ny(mpiRank);

    size_t start[] = {(size_t)step, 0, get_jstart(mpiRank), get_istart(mpiRank)};
    size_t count[] = {1, NZ, ny, nx};

    status = nc_open_par(ncfile, NC_WRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error opening the file %s\n", ncfile);
        ERR(status);
    }

    status = nc_inq_varid(ncid, output_var, &varid);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_var_par_access(ncid, varid, NC_COLLECTIVE);
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_put_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        ERR(status);
    }
}
