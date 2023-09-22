
#include "ncio.h"
#include "string_util.h"
#include "variables.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

int test_chl_files();
int test_qsr_files();

/** Running the test on the ORCA1 grid (Northfold F-pivot, zonal cyclicity) */
int main(int argc, char *argv[]) {

    read_parameters("parameters_1d.csv");
    set_parameters();

    if (test_chl_files()) {
        return 1;
    }

    if (test_qsr_files()) {
        return 1;
    }

    return 0;
}

int test_chl_files() {

    vector<string> list_chl_files = get_files(chl_pattern);
    if (list_chl_files.size() != 6) {
        printf("Number of Chl files is wrong. Expected 6, got %ld\n", list_chl_files.size());
        return 1;
    }

    fs::path p1;
    fs::path p2;

    p1 = list_chl_files[0];
    p2 = "./nico_HOTv420_1ts_20100101_20100228_ptrc_T.nc";
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [0]");
        return 1;
    }

    p1 = list_chl_files[1];
    p2 = "./nico_HOTv420_1ts_20100301_20100430_ptrc_T.nc";
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [1]");
        return 1;
    }

    p1 = list_chl_files[2];
    p2 = "./nico_HOTv420_1ts_20100501_20100630_ptrc_T.nc";
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [2]");
        return 1;
    }

    p1 = list_chl_files[3];
    p2 = "./nico_HOTv420_1ts_20100701_20100831_ptrc_T.nc";
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [3]");
        return 1;
    }

    p1 = list_chl_files[4];
    p2 = "./nico_HOTv420_1ts_20100901_20101031_ptrc_T.nc";
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [4]");
        return 1;
    }

    p2 = "./nico_HOTv420_1ts_20101101_20101231_ptrc_T.nc";
    p1 = list_chl_files[5];
    if (p1.compare(p2) != 0) {
        printf("Error with chl file [5]");
        return 1;
    }

    if (get_total_ntime(list_chl_files) != 8760) {
        printf("Error reading total number of time-steps in qsr");
        return 1;
    }

    if (get_ntime_file(list_chl_files[0]) != 1416) {
        return 1;
    }
    if (get_ntime_file(list_chl_files[1]) != 1464) {
        return 1;
    }
    if (get_ntime_file(list_chl_files[2]) != 1464) {
        return 1;
    }
    if (get_ntime_file(list_chl_files[3]) != 1488) {
        return 1;
    }
    if (get_ntime_file(list_chl_files[4]) != 1464) {
        return 1;
    }
    if (get_ntime_file(list_chl_files[5]) != 1464) {
        return 1;
    }

    return 0;
}

int test_qsr_files() {

    fs::path p1;
    fs::path p2;

    vector<string> list_qsr_files = get_files(qsr_pattern);
    if (list_qsr_files.size() != 12) {
        printf("Number of Chl files is wrong. Expected 6, got %ld\n", list_qsr_files.size());
        return 1;
    }

    p2 = "./nico_HOTv420_1ts_20100101_20100131_grid_T.nc";
    p1 = list_qsr_files[0];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [0]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100201_20100228_grid_T.nc";
    p1 = list_qsr_files[1];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [1]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100301_20100331_grid_T.nc";
    p1 = list_qsr_files[2];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [2]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100401_20100430_grid_T.nc";
    p1 = list_qsr_files[3];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [3]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100501_20100531_grid_T.nc";
    p1 = list_qsr_files[4];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [4]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100601_20100630_grid_T.nc";
    p1 = list_qsr_files[5];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [5]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100701_20100731_grid_T.nc";
    p1 = list_qsr_files[6];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [6]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100801_20100831_grid_T.nc";
    p1 = list_qsr_files[7];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [7]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20100901_20100930_grid_T.nc";
    p1 = list_qsr_files[8];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [8]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20101001_20101031_grid_T.nc";
    p1 = list_qsr_files[9];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [9]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20101101_20101130_grid_T.nc";
    p1 = list_qsr_files[10];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [10]\n");
        return 1;
    }
    p2 = "./nico_HOTv420_1ts_20101201_20101231_grid_T.nc";
    p1 = list_qsr_files[11];
    if (p1.compare(p2) != 0) {
        printf("Error with qsr file [11]\n");
        return 1;
    }

    if (get_total_ntime(list_qsr_files) != 8760) {
        printf("Error reading total number of time-steps in qsr");
        return 1;
    }

    if (get_ntime_file(list_qsr_files[0]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[1]) != 672) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[2]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[3]) != 720) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[4]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[5]) != 720) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[6]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[7]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[8]) != 720) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[9]) != 744) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[10]) != 720) {
        return 1;
    }
    if (get_ntime_file(list_qsr_files[11]) != 744) {
        return 1;
    }

    return 0;
}