
#include "ncio.h"
#include "variables.h"
#include <string.h>

/** Running the test on the ORCA1 grid (Northfold F-pivot, zonal cyclicity) */
int main(int argc, char *argv[]) {

    read_parameters("parameters.csv");

    if (parameters.size() != 15) {
        printf("Wrong number of parameters. Expected 15, got %ld", parameters.size());
        return 1;
    }

    if (parameters["TIMEDIMENSION"].compare("time_counter") != 0) {
        printf("Error reading TIMEDIMENSION");
        return 1;
    }

    if (parameters["parfrac_file"].compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc") != 0) {
        printf("Error reading parfrac_file");
        return 1;
    }

    if (parameters["NFRAC"].compare("12") != 0) {
        printf("Error reading NFRAC");
        return 1;
    }

    if (parameters["parfrac_var"].compare("soshfldo") != 0) {
        printf("Error reading parfrac_var");
        return 1;
    }

    if (parameters["mesh_mask"].compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/new_mesh_mask.nc") != 0) {
        printf("Error reading mesh_mask");
        return 1;
    }

    if (parameters["chl_pattern"].compare("/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc") != 0) {
        printf("Error reading chl_pattern");
        return 1;
    }

    if (parameters["chl_var"].compare("Chltot") != 0) {
        printf("Error reading chl_var");
        return 1;
    }

    if (parameters["conversion_chl"].compare("1.0") != 0) {
        printf("Error reading conversion_chl");
        return 1;
    }

// qsr_pattern =  /home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc
// qsr_var =  soshfldo

// e3t_pattern /home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc
// e3t_var votemper

// output_prefix clim_GYRE_5d_00010101_00101231_PAR
// output_var par
// output_frequency 2

    return 0;

}