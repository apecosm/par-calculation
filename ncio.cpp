#include "ncio.h"
#include "boost_def.h"
#include "string_util.h"
#include "variables.h"
#include "variables_def.h"
#include <dirent.h>
#include <mpi.h>
#include <netcdf.h>
#ifdef PAR_NETCDF
#include <netcdf_par.h>
#endif
#include <regex>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

#define ERRCODE 2
#define ERR(e)                                 \
    {                                          \
        printf("Error: %s\n", nc_strerror(e)); \
        exit(ERRCODE);                         \
    }

/** Reads a 2D (y, x) output variable.
 *
*/
void read_gridvar(ma3f &var, const std::string filename, const std::string varname) {

    int status;
    int ncid;
    int varid;
    nc_type rh_type;
    int rh_ndims;
    int rh_natts;
    int rh_dimids[NC_MAX_VAR_DIMS];

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

#ifdef PAR_NETCDF
    status = nc_open_par(filename.c_str(), NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error opening %s\n", filename.c_str());
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error opening %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_varid(ncid, varname.c_str(), &varid);
    if (status != NC_NOERR) {
        printf("Error inq %s\n", varname.c_str());
        ERR(status);
    }

    int jjj = get_jstart(mpiRank);
    int iii = get_istart(mpiRank);

    status = nc_inq_var(ncid, varid, 0, &rh_type, &rh_ndims, rh_dimids, &rh_natts);
    /* Get the varid of the data variable, based on its name. */
    if (status != NC_NOERR) {
        printf("Error reading variable informations\n");
        ERR(status);
    }

    size_t start[rh_ndims];
    size_t count[rh_ndims];

    if (rh_ndims == 4) {
        start[0] = 0;
        start[1] = 0;
        start[2] = get_jstart(mpiRank);
        start[3] = get_istart(mpiRank);
        count[0] = 1;
        count[1] = NZ;
        count[2] = ny;
        count[3] = nx;
    } else {
        start[0] = 0;
        start[1] = get_jstart(mpiRank);
        start[2] = get_istart(mpiRank);
        count[0] = NZ;
        count[1] = ny;
        count[2] = nx;
    }

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        printf("Error reading %s\n", varname.c_str());
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing %s\n", filename.c_str());
        ERR(status);
    }

    if (mpiRank == 0)
        printf("%s: reading %s\n", varname.c_str(), filename.c_str());
    }

/** Get the number of time steps stored in a NetCDF output file
 *
*/
size_t get_spatial_dimension_file(string filename, string dimname) {

    int ncid;
    int status;
    int dimid;
    size_t nsteps;

#ifdef PAR_NETCDF
    status = nc_open_par(filename.c_str(), NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading %s\n", filename.c_str());
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_dimid(ncid, dimname.c_str(), &dimid);
    if (status != NC_NOERR) {
        printf("Error inq. %s\n", dimname.c_str());
        ERR(status);
    }

    status = nc_inq_dimlen(ncid, dimid, &nsteps);
    if (status != NC_NOERR) {
        printf("Error inq. dim length %s\n", dimname.c_str());
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing file %s\n", filename.c_str());
        ERR(status);
    }

    return nsteps;
}

/** Get the number of time steps stored in a NetCDF output file
 *
*/
size_t get_ntime_file(string filename) {

    int ncid;
    int status;
    int dimid;
    size_t nsteps;

#ifdef PAR_NETCDF
    status = nc_open_par(filename.c_str(), NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading %s\n", filename.c_str());
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_dimid(ncid, time_dimension.c_str(), &dimid);
    if (status != NC_NOERR) {
        printf("Error inq. %s\n", time_dimension.c_str());
        ERR(status);
    }

    status = nc_inq_dimlen(ncid, dimid, &nsteps);
    if (status != NC_NOERR) {
        printf("Error inq. dim length %s\n", time_dimension.c_str());
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing file %s\n", filename.c_str());
        ERR(status);
    }

    return nsteps;
}

/** Reads a 3D (depth, y, x) variable from NetCDF.
 *
*/
void read_var(ma3f &var, const std::string filename, const std::string varname, size_t i0, double conversion) {

    int status;
    int ncid;
    int varid;

    if (mpiRank == 0)
        printf("%s: reading %s, step=%ld\n", varname.c_str(), filename.c_str(), i0);

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

#ifdef PAR_NETCDF
    status = nc_open_par(filename, NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading file %s\n", filename);
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading file %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_varid(ncid, varname.c_str(), &varid);
    if (status != NC_NOERR) {
        printf("Error inq. var %s\n", varname.c_str());
        ERR(status);
    }

    size_t count[] = {1, NZ, ny, nx};
    size_t start[] = {i0, 0, get_jstart(mpiRank), get_istart(mpiRank)};

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        printf("Error reading var %s\n", varname.c_str());
        ERR(status);
    }


    for (size_t k = 0; k < NZ; k++) {
        for (size_t j = 0; j < ny; j++) {
            for (size_t i = 0; i < nx; i++) {
                var[k][j][i] *= conversion;
            }
        }
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing file %s\n", filename.c_str());
        ERR(status);
    }
}

/** Reads a 2D (y, x) output variable.
 *
*/
void read_var(ma2f &var, const std::string filename, const std::string varname, size_t i0, double conversion) {

    int status;
    int ncid;
    int varid;

    if (mpiRank == 0)
        printf("%s: reading %s, step=%ld\n", varname.c_str(), filename.c_str(), i0);

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

 #ifdef PAR_NETCDF
    status = nc_open_par(filename.c_str(), NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading file %s\n", filename.c_str());
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading file %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_varid(ncid, varname.c_str(), &varid);
    if (status != NC_NOERR) {
        printf("Error inq. variable %s\n", varname.c_str());
        ERR(status);
    }

    size_t start[] = {i0, get_jstart(mpiRank), get_istart(mpiRank)};
    size_t count[] = {1, ny, nx};

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        printf("Error reading variable %s\n", varname.c_str());
        ERR(status);
    }

    for (size_t j = 0; j < ny; j++) {
        for (size_t i = 0; i < nx; i++) {
            var[j][i] *= conversion;
        }
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing file %s\n", filename.c_str());
        ERR(status);
    }

}

void define_output_file(int cpt) {

    char ncfile[1096];

    int status;
    int ncid;
    int timeid;
    int yd, xd, zd;

#ifdef PAR_NETCDF
    sprintf(ncfile, "%s_%.05d.nc", output_prefix, cpt);
    int nx = NX;
    int ny = NY;
    int nz = NZ;
#else
    sprintf(ncfile, "%s_%.05d.nc.%3d", output_prefix.c_str(), cpt, mpiRank);
    int nx = get_nx(mpiRank);
    int ny = get_ny(mpiRank);
    int nz = NZ;
#endif

#ifdef PAR_NETCDF
    status = nc_create_par(ncfile, NC_CLOBBER | NC_NETCDF4 | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error creating filename %s\n", ncfile);
        ERR(status);
    }
#else
    status = nc_create(ncfile, NC_NETCDF4, &ncid);
    if (status != NC_NOERR) {
        printf("Error creating filename %s\n", ncfile);
        ERR(status);
    }
#endif

    status = nc_def_dim(ncid, "time", NC_UNLIMITED, &timeid);
    if (status != NC_NOERR) {
        printf("Error defining dimension %s\n", "time");
        ERR(status);
    }

    status = nc_def_dim(ncid, "z", nz, &zd);
    if (status != NC_NOERR) {
        printf("Error defining dimension %s\n", "z");
        ERR(status);
    }

    status = nc_def_dim(ncid, "y", ny, &yd);
    if (status != NC_NOERR) {
        printf("Error defining dimension %s\n", "y");
        ERR(status);
    }

    status = nc_def_dim(ncid, "x", nx, &xd);
    if (status != NC_NOERR) {
        printf("Error defining dimension %s\n", "x");
        ERR(status);
    }

    int output_ids[] = {timeid, zd, yd, xd};
    int varid;

    status = nc_def_var(ncid, output_var.c_str(), NC_FLOAT, 4, output_ids, &varid);
    if (status != NC_NOERR) {
        printf("Error defining variable %s\n", output_var.c_str());
        ERR(status);
    }

    int time_ids[] = {timeid};
    int tid;

    status = nc_def_var(ncid, "time", NC_INT, 1, time_ids, &tid);
    if (status != NC_NOERR) {
        printf("Error defining variable %s\n", "time");
        ERR(status);
    }

    status = nc_enddef(ncid); //end definitions: leave define mode
    if (status != NC_NOERR) {
        printf("Error ending definition file %s\n", ncfile);
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing definition file %s\n", ncfile);
        ERR(status);
    }
}

void write_step(int cpt, int step, ma3f var, int time) {

    int ncid, varid, status;

    char ncfile[1096];
    sprintf(ncfile, "%s_%.05d.nc", output_prefix.c_str(), cpt);

    size_t nx = get_nx(mpiRank);
    size_t ny = get_ny(mpiRank);

#ifdef PAR_NETCDF
    size_t start[] = {(size_t)step, 0, get_jstart(mpiRank), get_istart(mpiRank)};
#else
    size_t start[] = {(size_t)step, 0, 0, 0};
#endif
    size_t count[] = {1, NZ, ny, nx};

#ifdef PAR_NETCDF
    status = nc_open_par(ncfile, NC_WRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error opening the file %s\n", ncfile);
        ERR(status);
    }
#else
    status = nc_open(ncfile, NC_WRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error opening the file %s\n", ncfile);
        ERR(status);
    }
#endif

    if (mpiRank == 0)
        printf("%s: writting %s, step=%d\n", output_var.c_str(), ncfile, step);

    status = nc_inq_varid(ncid, output_var.c_str(), &varid);
    if (status != NC_NOERR) {
        printf("Error inq. variable %s\n", output_var.c_str());
        ERR(status);
    }

#ifdef PAR_NETCDF
    status = nc_var_par_access(ncid, varid, NC_COLLECTIVE);
    if (status != NC_NOERR) {
        printf("Error setting var access variable %s\n", output_var);
        ERR(status);
    }
#endif

    status = nc_put_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        printf("Error writting variable %s\n", output_var.c_str());
        ERR(status);
    }

    int tid;
    size_t tstart[] = {(size_t)step};
    size_t tcount[] = {1};

    status = nc_inq_varid(ncid, "time", &tid);
    if (status != NC_NOERR) {
        printf("Error inq. variable %s\n", "time");
        ERR(status);
    }

#ifdef PAR_NETCDF
    status = nc_var_par_access(ncid, tid, NC_COLLECTIVE);
    if (status != NC_NOERR) {
        printf("Error setting var access variable %s\n", "time");
        ERR(status);
    }
#endif

    status = nc_put_vara_int(ncid, tid, tstart, tcount, &time);
    if (status != NC_NOERR) {
        printf("Error writting var %s\n", "time");
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing var %s\n", ncfile);
        ERR(status);
    }
}

/** Reads the entire parfrac time series on the given tile.
*/
void read_parfrac(ma3f &var, string filename, string varname) {

    int status;
    int ncid;
    int varid;

    size_t ny = get_ny(mpiRank);
    size_t nx = get_nx(mpiRank);

#ifdef PAR_NETCDF
    status = nc_open_par(filename.c_str(), NC_NOWRITE | NC_MPIIO, MPI_COMM_WORLD, MPI_INFO_NULL, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading var %s\n", filename.c_str());
        ERR(status);
    }
#else
    status = nc_open(filename.c_str(), NC_NOWRITE, &ncid);
    if (status != NC_NOERR) {
        printf("Error reading var %s\n", filename.c_str());
        ERR(status);
    }
#endif

    status = nc_inq_varid(ncid, varname.c_str(), &varid);
    if (status != NC_NOERR) {
        printf("Error inq. %s\n", varname.c_str());
        ERR(status);
    }

    size_t start[] = {0, get_jstart(mpiRank), get_istart(mpiRank)};
    size_t count[] = {NFRAC, ny, nx};

    status = nc_get_vara_float(ncid, varid, start, count, var.data());
    if (status != NC_NOERR) {
        printf("Error reading %s\n", varname.c_str());
        ERR(status);
    }

    status = nc_close(ncid);
    if (status != NC_NOERR) {
        printf("Error closing file %s\n", filename.c_str());
        ERR(status);
    }

    if (mpiRank == 0)
        printf("%s: reading %s, step=[0, %ld]\n", varname.c_str(), filename.c_str(), NFRAC - 1);
}

void read_parameters(string filename) {

    std::regex regexp_line("^[a-zA-Z].*=.*$");

    string line, word;
    vector<string> row;
    fstream file(filename, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();
            if (!regex_match(line, regexp_line)) {
                continue;
            }

            stringstream str(line);

            while (getline(str, word, '=')) {
                row.push_back(word);
            }
            string key = row[0];
            string value = row[1];
            boost::trim_right(key);
            boost::trim_left(key);
            boost::trim_right(value);
            boost::trim_left(value);
            parameters[key] = value;
        }
    } else {
        cout << "Could not open the file\n";
    }
}

void set_parameters() {

    // Definition the spatial variables
    LON_MPI = stoi(parameters["LON_MPI"]);

    LAT_MPI = stoi(parameters["LAT_MPI"]);
    x_dimension = parameters["x_dimension"];
    y_dimension = parameters["y_dimension"];
    z_dimension = parameters["z_dimension"];

    mesh_mask = parameters["mesh_mask"];

    // define name of time dimension
    time_dimension = parameters["time_dimension"];

    // define pattern
    chl_pattern = parameters["chl_pattern"];
    chl_var = parameters["chl_var"];
    conversion_chl = stof(parameters["conversion_chl"]);

    qsr_pattern = parameters["qsr_pattern"];
    qsr_var = parameters["qsr_var"];

    output_prefix = parameters["output_prefix"];
    output_var = parameters["output_var"];
    output_frequency = stoi(parameters["output_frequency"]);

    qsr_pattern = parameters["qsr_pattern"];

    // Check if VVL is defined.
    if((parameters.find("e3t_pattern") == parameters.end()) || (parameters.find("e3t_var") == parameters.end())) {
        use_vvl = false;
    } else {
        use_vvl = true;
        e3t_pattern = parameters["e3t_pattern"];
        e3t_var = parameters["e3t_var"];
    }

    // Check if variable par file is defined.
    if((parameters.find("parfrac_file") == parameters.end()) || (parameters.find("parfrac_var") == parameters.end())) {
        use_parfrac = false;
    } else {
        use_parfrac = true;
        parfrac_file = parameters["parfrac_file"];
        parfrac_var = parameters["parfrac_var"];
    }

}


size_t get_total_ntime(vector<string> list_of_files) {

    int ntotal = 0;
    for(int i = 0; i < list_of_files.size(); i++) {
        ntotal += get_ntime_file(list_of_files[i]);
    }

    return ntotal;

}