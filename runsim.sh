#!/bin/bash

<<COMMENT1
	Script to run several simulations.

	Parameters are:

			1   2   3   4    5    6    7   8   9   10    11   12  13  14   15    16
			T  dtp  n  a0   d0  ksi  sar  a   w   Tag   Tab   Tr  Td  d  dtsave seed

COMMENT1

#run

# replications for figure in with w=0; a=0
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 0.2 1.0 10 1 1 186611287&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 0.4 1.0 10 1 1 186611281&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 0.8 1.0 10 1 1 186611283&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 1.6 1.0 10 1 1 186611285&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 3.2 1.0 10 1 1 186611289&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 6.4 1.0 10 1 1 186611267&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 12.8 1.0 10 1 1 186611247&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 25.6 1.0 10 1 1 186611227&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 51.2 1.0 10 1 1 186611207&
./gillespie-ses 4000 0.1 40 0.1 0 1 0.25 0.0 0.0 0.01 102.4 1.0 10 1 1 186611217&
