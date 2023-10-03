Compilation
===============

Boost library
++++++++++++++++

You first need to download the Boost library (https://www.boost.org/).

Download the most recent version and uncompress the archive file

Building the tool
++++++++++++++++++

There is two ways for building the program: using ``make`` and using ``cmake``

Using ``make``
----------------------

To compile the program using ``make``, you first need to create a
``Makefile.inc`` file containing library paths, compiler options, etc.

Some templates are provided in the ``arch`` folder. For instance, to
compile the program on Ubuntu using GCC, copy the ``arch/Makefile.inc.gcc``
file in the current folder:

.. code-block:: bash

    cp arch/Makefile.inc.gcc Makefile.inc

Next, simply type:

.. code-block:: bash

    make

If the user wants to activate the parallel feature of the NetCDF library, the
``PAR_NETCDF`` precompiler option must be added.

Using ``cmake``
----------------------

To compile the program using ``cmake``, first create a ``build`` folder:

.. code-block:: bash

    mkdir build

Now move to this folder:

.. code-block:: bash

    cd build

The next step is to configure ``cmake``. This is done as follows:

.. code-block:: bash

    cmake ..

Cmake will automatically detect the NetCDF and HDF5 library. If Boost libraries
are not found, create the ``BOOST_ROOT`` environment variable:

.. code-block::

    export BOOST_ROOT=/home/barrier/Libs/Cpp/boost_1_78_0

and re-reun the ``cmake`` command.

Note that using Cmake allows the user to specify some compile options using ``-D``:

.. code-block:: bash

    cmake .. -DBOOST_ASSERT=true -DBUILD_MODE=debug

The list of options is provided below:

.. list-table:: Cmake options
    :header-rows: 1

    * - Option
      - Description
      - Values
    * - ``BUILD_MODE``
      - Defines optimization process
      - ``release`` (optimized), ``debug``, else intermediate (optimized with debug informations)
    * - ``BOOST_ASSERT``
      - Defines whether Boost should check for out-of-bound errors in arrays
      - ``false`` (optimized) or ``true`` (for debugging purposes)
    * - ``USE_PARALLEL_NETCDF``
      - Defines whether parallel NetCDF should be used
      - ``false`` or ``true``
    * - ``RUNNING_TESTS``
      - Defines whether tests should be run or not.
      - ``true`` or ``false``
