#include <math.h>
#include <mpi.h>
#include <netcdf.h>
#include <stdio.h>
#include <vector>
#include "main.h"
#include "boost_def.h"
#include "ncio.h"
#include "string_util.h"
#include "variables.h"
#include "par.h"

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
    
    // Init the RGB attenuation coefficients
    init_zrgb();

    vector<string> list_chl_files = get_files(chl_pattern);
    vector<string> list_qsr_files = get_files(qsr_pattern);
#ifdef VVL
    vector<string> list_e3t_files = get_files(e3t_pattern);
#endif

    // count the number of read for the given file
    // ichl = index of the file in the list of files
    // stepchl = time step being read in the file
    // nchl = number of time steps in the file
    size_t stepchl = 0;
    int ichl = 0;
    size_t nchl = get_ntime_file(list_chl_files[ichl].c_str());

    size_t stepqsr = 0;
    int iqsr = 0;
    size_t nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());

#ifdef VVL
    size_t stepe3t = 0;
    int ie3t = 0;
    size_t ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());
#endif

    // iterator for the output
    int iout = 0;
    int stepout = 0;

    // initialisation of the MPI decomposition.
    init_mpi_domains();

    int nx = get_nx(mpiRank);
    int ny = get_ny(mpiRank);

    // Init. the input arrays
    ma3f tmask(boost::extents[NZ][ny][nx]);
    ma3f e3t(boost::extents[NZ][ny][nx]);
    ma3f chl(boost::extents[NZ][ny][nx]);
    ma2f qsr(boost::extents[ny][nx]);
    ma3f par(boost::extents[NZ][ny][nx]);
#ifdef PARFRAC
    ma3f parfrac(boost::extents[NFRAC][ny][nx]);
    read_parfrac(parfrac, parfrac_file, parfrac_var);
#endif

    // Reading variable for e3t
    read_gridvar(e3t, mesh_mask, "e3t_0");
    read_gridvar(tmask, mesh_mask, "tmask");

    if (mpiRank == 0)
        printf("+++++++++++++++++++++++++++++++ Starting computations\n");

    for (int time = 0; time < NTIME; time++) {

        if (stepchl == nchl) {
            ichl++;
            stepchl = 0;
            nchl = get_ntime_file(list_chl_files[ichl].c_str());
        }

        if (stepqsr == nqsr) {
            iqsr++;
            stepqsr = 0;
            nqsr = get_ntime_file(list_qsr_files[iqsr].c_str());
        }

#ifdef VVL
        if (stepe3t == ne3t) {
            ie3t++;
            stepe3t = 0;
            ne3t = get_ntime_file(list_e3t_files[ie3t].c_str());
        }
#endif

        if(mpiRank == 0) printf("++++++ time = %d\n", time);

        read_var(qsr, list_qsr_files[iqsr].c_str(), qsr_var, stepqsr);
        read_var(chl, list_chl_files[ichl].c_str(), chl_var, stepchl, conversion_chl);
#ifdef VVL
        read_var(e3t, list_e3t_files[ie3t].c_str(), e3t_var, stepe3t);
#endif

#ifdef PARFRAC
        int ifrac = time % NFRAC;
        if(mpiRank == 0) printf("ifrac = %d\n", ifrac);
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                if(tmask[0][j][i] == 0) continue;
                qsr[j][i] *= parfrac[ifrac][j][i];
            }
        }
#endif

        // computation of PAR.
        compute_par_c(par, chl, qsr, e3t, tmask);

        if (iout == 0) {
            define_output_file(stepout);
        }

        write_step(stepout, iout, par, time);
        iout++;

        if (iout == output_frequency) {
            iout = 0;
            stepout++;
        }

        stepchl++;
        stepqsr++;
#ifdef VVL
        stepe3t++;
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

    if (mpiRank == 0) {
        printf("++++++++++++++++++++++++ Init MPI decomposition\n");
        for (int i = 0; i < LON_MPI * LAT_MPI; i++) {
            printf("++++ i=%d, istart=%ld, iend=%ld, jstart=%ld, jend=%ld\n", i, get_istart(i), get_iend(i), get_jstart(i), get_jend(i));
        }
    }
}
