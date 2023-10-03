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

If the user provides the following parameters:

.. list-table:: Configuration options: par fraction file
    :header-rows: 1

    * - Option
      - Description
    * - ``parfrac_file``
      - Localisation of PAR fraction file
    * - ``parfrac_var``
      - Name of the PAR fraction variable

then the program assumes that the fraction of qsr that will
be used in the light attenuation algorithm varies over time and
space.

If one of the above argument is missing, then a constant par fraction
will be applied. It is provided by the following
parameter:

.. list-table:: Configuration options: par fraction file
    :header-rows: 1

    * - Option
      - Description
    * - ``constant_parfrac``
      - Fraction of the qsr fraction used in the PAR par calculation

If the user provides the following parameters:

.. list-table:: Configuration options: VVL
    :header-rows: 1

    * - Option
      - Description
    * - ``e3t_pattern``
      - Regular expression to list the cell thickness files.
    * - ``e3t_var``
      - Name of the cell thickness variable

the program assumes that the cell thickness vary over time and space.
It will read the cell thickness variables and use it in the PAR
vertical attenuation.

If one of the above variable is missing, then the cell thickness is
read from the mesh mask.
