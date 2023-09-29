Introduction
===============

In CMIP6 outputs, the 3D light penetration or photosynthetic
active radiation (PAR) outputs are generally not available. Therefore,
they need to be reconstructed offline. This is the aim of the present tool.

The objective is to use the chlorophyll and solar radiation outputs,
provided by CMIP6, and eventually the time-varying cell thickness to
compute this 3D light penetration.

To do so, the simplified three wavebands algorithm, described
in :cite:t:`lengaigne2007influence`, is used. This choice is consistent with
most of the NEMO simulations.
