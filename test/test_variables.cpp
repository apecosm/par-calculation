
#include "ncio.h"
#include "variables.h"
#include <string.h>

/** Running the test on the ORCA1 grid (Northfold F-pivot, zonal cyclicity) */
int main(int argc, char *argv[]) {

    read_parameters("parameters.csv");
    set_parameters();

    if (time_dimension.compare("time_counter") != 0) {
        printf("Error reading time_dimension\n");
        return 1;
    }

    if (parfrac_file.compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc") != 0) {
        printf("Error reading parfrac_file\n");
        return 1;
    }

    if (parfrac_var.compare("soshfldo") != 0) {
        printf("Error reading parfrac_var\n");
        return 1;
    }

    if (mesh_mask.compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/new_mesh_mask.nc") != 0) {
        printf("Error reading mesh_mask\n");
        return 1;
    }

    if (chl_pattern.compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc") != 0) {
        printf("Error reading chl_pattern\n");
        return 1;
    }

    if (chl_var.compare("Chltot") != 0) {
        printf("Error reading chl_var\n");
        return 1;
    }

    if (conversion_chl != 1.0) {
        printf("Error reading conversion_chl\n");
        return 1;
    }

    if (LON_MPI != 3) {
        printf("Error reading LON_MPI\n");
    }

    if (LAT_MPI != 2) {
        printf("Error reading LAT_MPI\n");
    }

    return 0;

}