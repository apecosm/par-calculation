Running
===============

The tool can be run as follows:

.. code-block:: bash

    ./par_calculation configuration_file.conf

The argument specifies the configuration file, which must contain
the following parameters:

.. list-table:: Configuration options
    :header-rows: 1

    * - Option
      - Description
    * - ``mesh_mask``
      - Localisation of the NEMO mesh mask
    * - ``chl_pattern``
      - Regular expression to list the total chlorophyll files.
    * - ``chl_var``
      - Name of the chlorophyll variable
    * - ``conversion_chl``
      - Chlorophyll conversion coefficient
    * - ``qsr_pattern``
      - Regular expression to list the solar radiation files.
    * - ``qsr_var``
      - Name of the solar radiation variable
    * - ``conversion_qsr``
      - Solar radiation conversion coefficient
    * - ``time_dimension``
      - Name of the time dimension (inferred from forcing files)
    * - ``x_dimension``
      - Name of the x dimension (inferred from the mesh files)
    * - ``y_dimension``
      - Name of the y dimension (inferred from the mesh files)
    * - ``z_dimension``
      - Name of the z dimension (inferred from the mesh files)
    * - ``lon_mpi``
      - Number of processes along the x dimension
    * - ``lat_mpi``
      - Number of processes along the y dimension
    * - ``output_prefix``
      -  Prefix of the output file
    * - ``output_var``
      - Name of the ouput variable
    * - ``output_frequency``
      - Number of time steps per output file.

.. danger::

    Chlorophyll must be in :math:`gChl.m^{-3}` and solar radiation in
    :math:`W.m^{-2}`



constant_parfrac = 0.43
