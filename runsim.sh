#!/bin/bash

<<COMMENT1
	Script to run several simulations.

	Parameters are:

			1   2   3   4    5    6    7   8   9   10    11    12  13  14   15   16
			T  dtp  n  a0   d0  ksi  sar  a   w   Tag   Tab   Tr  Td   d  dtsave seed

COMMENT1

#run

# replications for figure in with w=0; a=0
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611281&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611283&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611285&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611289&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611267&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611247&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611227&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611207&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 1.5 0.1 50 5.0 50 1 1 345611217&

./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 145611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 245611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 345611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 445611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 545611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 645611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 745611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 845611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 945611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 2.0 0.1 50 5.0 50 1 1 045611287&

./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 315611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 325611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 335611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 345611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 355611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 365611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 375611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 385611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 395611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.0 0.1 50 5.0 50 1 1 305611287&

./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 341611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 342611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 343611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 344611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 345711287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 346611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 347611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 348611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 399611287&
./gillespie-ses 4001 0.1 40 0.05 0 1 0.25 0.0 3.5 0.1 50 5.0 50 1 1 311611287&











# replications for figure in the simplest case
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333533&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333513&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333515&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333517&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333519&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33353335&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333523&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333525&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333527&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333529&
#
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33333&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33313&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33315&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33317&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33319&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 333333&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33323&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33325&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33327&
# ./gillespie-ses 4000 0.1 40 0.05 0 1 0.25 0.0 6.0 0.1 50 5.0 50 8 1 33329&


# exploration for the weird things i've seen (i.e. w large with a small, and d large)
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 1 1 3111&
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 1 1 3113&
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 1 1 3115&
#
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 10 1 3111&
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 10 1 3113&
# ./gillespie-ses 2000 0.1 40 0.1 0 1 0.25 0.0 6.0 0.1 50 5 50 10 1 3115&




# ./gillespie-ses 2000 0.1 10 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 1&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 d1&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 d1&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 d1&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 d1&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.25 0.0 0.0 0.05 50 5 50 1 1 d1&
#
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.0 0.0 0.0 0.05 50 5 50 2 1 d2&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.1 0.0 0.0 0.05 50 5 50 2 1 d2&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.2 0.0 0.0 0.05 50 5 50 2 1 d2&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.3 0.0 0.0 0.05 50 5 50 2 1 d2&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.4 0.0 0.0 0.05 50 5 50 2 1 d2&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.5 0.0 0.0 0.05 50 5 50 2 1 d2&
#
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.0 0.0 0.0 0.05 50 5 50 3 1 d3&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.1 0.0 0.0 0.05 50 5 50 3 1 d3&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.2 0.0 0.0 0.05 50 5 50 3 1 d3&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.3 0.0 0.0 0.05 50 5 50 3 1 d3&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.4 0.0 0.0 0.05 50 5 50 3 1 d3&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.5 0.0 0.0 0.05 50 5 50 3 1 d3&
#
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.0 0.0 0.0 0.05 50 5 50 4 1 d4&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.1 0.0 0.0 0.05 50 5 50 4 1 d4&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.2 0.0 0.0 0.05 50 5 50 4 1 d4&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.3 0.0 0.0 0.05 50 5 50 4 1 d4&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.4 0.0 0.0 0.05 50 5 50 4 1 d4&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.5 0.0 0.0 0.05 50 5 50 4 1 d4&
#
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.0 0.0 0.0 0.05 50 5 50 5 1 d5&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.1 0.0 0.0 0.05 50 5 50 5 1 d5&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.2 0.0 0.0 0.05 50 5 50 5 1 d5&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.3 0.0 0.0 0.05 50 5 50 5 1 d5&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.4 0.0 0.0 0.05 50 5 50 5 1 d5&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.5 0.0 0.0 0.05 50 5 50 5 1 d5&
#
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.0 0.0 0.0 0.05 50 5 50 6 1 d6&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.1 0.0 0.0 0.05 50 5 50 6 1 d6&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.2 0.0 0.0 0.05 50 5 50 6 1 d6&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.3 0.0 0.0 0.05 50 5 50 6 1 d6&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.4 0.0 0.0 0.05 50 5 50 6 1 d6&
# ./gillespie-ses 2000 0.1 40 0.05 0 1 0.5 0.0 0.0 0.05 50 5 50 6 1 d6&
