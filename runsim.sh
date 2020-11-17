#!/bin/bash

<<COMMENT1
	Script to run several simulations.

	Parameters are:

			1   2   3   4    5   6   7   8   9    10   11   12   13   14   15   16   17  18  19  20  21  22  23  24    25     26
			T  dtp  n  ao0  ai0  c0  r0  kg  kd  cmin  ys0  yn0  pSD  ori  ini  ess  a   w   g   m0  m   Ta  Tr  Td  dtsave   exp

COMMENT1

#run

# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 5.5 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 6.0 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 6.5 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 7.0 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 7.5 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 8.0 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 8.5 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 9.0 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 9.5 0 2 2 50 1 global&
# ./gillespie-ses 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 10 0 2 2 50 1 global&

./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 5.5 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 6.0 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 6.5 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 7.0 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 7.5 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 8.0 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 8.5 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 9.0 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 9.5 0 2 2 50 1 local&
./gillespie-ses-local 3000 0.1 40 0.1 0 1 1 0 0.5 0.5 25 18.75 0.0 0.2 0.8 1 1 0 0.1 10 0 2 2 50 1 local&
