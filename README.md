# Offline computation of Photosynthetically Active Radiation (PAR)

Tool dedicated to the offline computation of PAR from Chlorophyl and ocean cell thickness. The light attenuation is identical to 
the one used in NEMO Ocean model (`p4zopt.F90` file).

## Requirements
- `boost/multi_array.hpp`
- NetCDF **built in parallel mode** (`netcdf_par.h`)

## Compilation

- Edit the `variables.h` file and modify paths, variable names, etc.
- Copy one of the file in the `arch` directory in the root directory, rename it `Makefile.inc`.
- Run `make`

**Warning: you need to recompile the code any time you modify the `variables.h` file**
