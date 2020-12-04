#include "main.h"
#include "boost_def.h"
#include "ncio.h"
#include "string_util.h"
#include "variables.h"
#include <math.h>
#include <mpi.h>
#include <netcdf.h>
#include <stdio.h>
#include <vector>

#define get_chl(cell, z) (0)
#define get_qsr(cell) (0)
#define get_parfrac(cell) (0)
#define get_bottom(cell) (0)
#define get_deltaz(cell, k) (0)

const char *mesh_mask = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/mesh_mask.nc";

const char *chl_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc";
const char *chl_var = "Chltot";

const char *qsr_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc";
const char *qsr_var = "soshfldo";

const char *e3t_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc";
const char *e3t_var = "soshfldo";

/** Processors index to process. */
ma1iu istart(boost::extents[LON_MPI]);
ma1iu iend(boost::extents[LON_MPI]);
ma1iu jstart(boost::extents[LAT_MPI]);
ma1iu jend(boost::extents[LAT_MPI]);

ma3f tmask;
ma3f e3t_0;

using namespace std;

int mpiRank;
int mpiSize;

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

    if (mpiSize != LON_MPI * LAT_MPI) {
        printf("LON_MPI * LAT_MPI = %d, should be %d\n", LON_MPI * LAT_MPI, mpiSize);
        MPI_Finalize();
        exit(1);
    }

    vector<string> list_chl_files = get_files(chl_pattern);
    vector<string> list_qsr_files = get_files(qsr_pattern);
    vector<string> list_e3t_files = get_files(e3t_pattern);

    int cptchl = 0;
    int ichl = 0;
    size_t nchl = get_ntime_file(list_chl_files[ichl].c_str());

    int cptqsr = 0;
    int iqsr = 0;
    size_t nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());

    int cpte3t = 0;
    int ie3t = 0;
    size_t ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());

    init_mpi_domains();

    int nx = get_nx(mpiRank);
    int ny = get_ny(mpiRank);
    
    ma3f tmask(boost::extents[NZ][ny][nx]);
    read_var(tmask, mesh_mask, "tmask", 0);

    /*
    if (mpiRank == 0) {
        for (int k = 0; k < 1; k++) {
            for (int j = 0; j < ny; j++) {
                for (int i = 0; i < nx; i++) {
                // /printf("k=%d, j=%d, i=%d, mask=%f\n", k, j, i, tmask[k][j][i]);
                }
            }
        }
    }
    */

    //ma3f e3t_0;
    //read_var(e3t_0, mesh_mask, "e3t_0", 0);
    //for(int t = 0; t < NTIME; t++) {
    //
    //}

    // read the model mesh_mask
    MPI_Finalize();
}

void init_mpi_domains(void) {

    int ncellx = NX / LON_MPI;
    int ncelly = NY / LAT_MPI;

    // init the MPI layers in longitude
    istart[0] = 0;
    iend[LON_MPI - 1] = NX - 1;
    for (int i = 0; i < LON_MPI - 1; i++) {
        iend[i] = ncellx * (1 + i) - 1;
        istart[i + 1] = iend[i] + 1;
    }

    jstart[0] = 0;
    jend[LAT_MPI - 1] = NY - 1;
    for (int i = 0; i < LAT_MPI - 1; i++) {
        jend[i] = ncelly * (1 + i) - 1;
        jstart[i + 1] = jend[i] + 1;
    }
}
