
#include "ncio.h"
#include "string_util.h"
#include "variables.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

/** Running the test on the ORCA1 grid (Northfold F-pivot, zonal cyclicity) */
int main(int argc, char *argv[]) {

    read_parameters("parameters_1d.csv");
    set_parameters();

    if(!check_variable_existence(mesh_mask, "tmask")) {
        printf("tmask variable is not found in mesh_mask\n");
        return 1;
    }

    if(!check_variable_existence(mesh_mask, "tmaskutil")) {
        printf("tmaskutil variable is not found in mesh_mask\n");
        return 1;
    }

    if (check_variable_existence(mesh_mask, "toto")) {
        printf("toto variable is found in mesh_mask\n");
        return 1;
    }

    if (check_variable_existence(mesh_mask, "x")) {
        printf("x variable is found in mesh_mask\n");
        return 1;
    }

    return 0;

}
