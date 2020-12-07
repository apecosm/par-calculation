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
        printf("LON_MPI * LAT_MPI = %d, should be %d\n", LON_MPI * LAT_MPI, mpiSize);
        MPI_Finalize();
        exit(1);
    }

    vector<string> list_chl_files = get_files(chl_pattern);
    vector<string> list_qsr_files = get_files(qsr_pattern);
#ifdef VVL
    vector<string> list_e3t_files = get_files(e3t_pattern);
#endif

    // count the number of read for the given file
    // ichl = index of the file in the list of files
    // cptchl = time step being read in the file
    // nchl = number of time steps in the file
    size_t cptchl = 0;
    int ichl = 0;
    size_t nchl = get_ntime_file(list_chl_files[ichl].c_str());

    size_t cptqsr = 0;
    int iqsr = 0;
    size_t nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());

#ifdef VVL
    size_t cpte3t = 0;
    int ie3t = 0;
    size_t ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());
#endif

    // iterator for the output
    int iout = 0;
    int cptout = 0;

    // initialisation of the MPI decomposition.
    init_mpi_domains();

    int nx = get_nx(mpiRank);
    int ny = get_ny(mpiRank);

    // Init. the input arrays
    ma3f tmask(boost::extents[NZ][ny][nx]);
    ma3f e3t(boost::extents[NZ][ny][nx]);
    ma3f chl(boost::extents[NZ][ny][nx]);
    ma2f qsr(boost::extents[ny][nx]);

    // Reading variable for e3t
    read_var(e3t, mesh_mask, "e3t_0", 0);

    for (int t = 0; t < 1; t++) {

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
#ifdef VVL
        read_var(e3t, list_e3t_files[ie3t].c_str(), e3t_var, cpte3t);
#endif

        if (iout == 0) {
            define_output_file(cptout);
        }

        write_step(cptout, iout, chl);
        iout++;

        if (iout == output_frequency) {
            iout = 0;
            cptout++;
        }

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

    for (int i = 0; i < LON_MPI; i++) {
        printf("++++++++++++++++ i=%d, istart=%ld, iend=%ld\n", i, istart[i], iend[i]);
    }

    for (int i = 0; i < LON_MPI; i++) {
        printf("++++++++++++++++ j=%d, jstart=%ld, jend=%ld\n", i, jstart[i], jend[i]);
    }
}
