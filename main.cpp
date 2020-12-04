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

size_t LON_MPI = 1;
size_t LAT_MPI = 1;
size_t NX = 32;
size_t NY = 22;
size_t NZ = 31;
size_t NTIME = 73;

const char *TIMEDIMENSION = "time_counter";
#define VVL

const char *mesh_mask = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/mesh_mask.nc";

const char *chl_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/Chltot.nc";
const char *chl_var = "Chltot";

const char *qsr_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc";
const char *qsr_var = "soshfldo";

#ifdef VVL
const char *e3t_pattern = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_grid_T.nc";
const char *e3t_var = "votemper";
#endif

const char *output_prefix = "/home/barrier/Codes/apecosm/git-apecosm-config/gyre/data/clim_GYRE_5d_00010101_00101231_PAR";
const char *output_var = "PAR";
int output_frequency = 73;

/** Processors index to process. */
ma1iu istart;
ma1iu iend;
ma1iu jstart;
ma1iu jend;

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
        printf("LON_MPI * LAT_MPI = %ld, should be %d\n", LON_MPI * LAT_MPI, mpiSize);
        MPI_Finalize();
        exit(1);
    }

    vector<string> list_chl_files = get_files(chl_pattern);
    vector<string> list_qsr_files = get_files(qsr_pattern);
#ifdef VVL
    vector<string> list_e3t_files = get_files(e3t_pattern);
#endif

    // count the number of read for the given file
    size_t cptchl = 0;
    // ichl = index of the file in the list of files
    int ichl = 0;
    // nchl = number of time steps in the file
    size_t nchl = get_ntime_file(list_chl_files[ichl].c_str());

    size_t cptqsr = 0;
    int iqsr = 0;
    size_t nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());

#ifdef VVL
    size_t cpte3t = 0;
    int ie3t = 0;
    size_t ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());
#endif

    init_mpi_domains();

    int nx = get_nx(mpiRank);
    int ny = get_ny(mpiRank);

    ma3f tmask(boost::extents[NZ][ny][nx]);
    ma3f e3t(boost::extents[NZ][ny][nx]);
    ma3f chl(boost::extents[NZ][ny][nx]);
    ma2f qsr(boost::extents[ny][nx]);

    // Reading variable for mask
    read_var(e3t, mesh_mask, "e3t_0", 0);

    for (int t = 0; t < NTIME; t++) {

        if (cptchl == nchl) {
            ichl++;
            cptchl = 0;
            nchl = get_ntime_file(list_chl_files[ichl].c_str());
        }

        if (cptqsr == nqsr) {
            iqsr++;
            cptqsr = 0;
            nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());
        }

#ifdef VVL
        if (cpte3t == ne3t) {
            ie3t++;
            cpte3t = 0;
            ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());
        }
#endif

        printf("+++++++++++++++++++++++++++++++ time = %d\n", t);
        read_var(qsr, list_qsr_files[iqsr].c_str(), qsr_var, cptqsr);
        read_var(chl, list_chl_files[ichl].c_str(), chl_var, cptchl);
        read_var(e3t, list_e3t_files[ie3t].c_str(), e3t_var, cpte3t);

        cptchl++;
        cptqsr++;
#ifdef VVL
        cpte3t++;
#endif
    }

    // read the model mesh_mask
    MPI_Finalize();
}

void init_mpi_domains(void) {

    istart.resize(boost::extents[LON_MPI]);
    iend.resize(boost::extents[LON_MPI]);
    jstart.resize(boost::extents[LAT_MPI]);
    jend.resize(boost::extents[LAT_MPI]);

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
