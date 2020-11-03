#!/bin/bash

<<COMMENT1
	Script to run several simulations.

	Parameters are:

      1    2   3  4    5    6  7   8  9  10  11  12   13   14  15   16		17	18
      T   dtp  n  a0  cg0  r0  y0  a  w  m   g   Ta   phi  Tr  Td  dtsave  k  Ti

			1   2   3   4    5   6   7   8   9    10   11  12  13   14  15  16  17  18  19  20  21    22    23
			T  dtp  n  ao0  ai0  c0  r0  kg  kd  cmin  y0  k   phi  a   w   g   m   Ti  Ta  Tr  Td  dtsave  exp

COMMENT1

# test local maintenance in new degradation model

./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.0 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.1 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.2 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.3 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.4 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.6 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.7 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.8 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 0.9 0 0.5 1.1 20 2 2 50 1 vara&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0 0 0.5 5 10 3 1.0 0 0.5 1.1 20 2 2 50 1 vara&

./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.05 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.10 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.20 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.40 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.80 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 1.60 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 3.20 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 6.40 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 12.8 1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkg&

./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.0 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.1 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.2 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.3 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.4 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.5 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.6 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.7 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.8 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 0.9 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&
./gillespie-ses 4000 0.1 40 0.10 0.05 1 1 0.1 1.0 0.5 5 10 3 0.5 0 0.5 1.1 20 2 2 50 1 varkd&

# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.2 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.3 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.4 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.5 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.6 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.7 0 1.1 0.1 2 3 2 50 1 10 10 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.8 0 1.1 0.1 2 3 2 50 1 10 10 &
#
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.2 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.3 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.4 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.5 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.6 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.7 0 1.1 0.1 2 3 2 50 1 10 20 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.8 0 1.1 0.1 2 3 2 50 1 10 20 &
#
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.2 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.3 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.4 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.5 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.6 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.7 0 1.1 0.1 2 3 2 50 1 10 40 &
# ./gillespie-ses 2000 0.1 40 0.10 1 1 5 0.8 0 1.1 0.1 2 3 2 50 1 10 40 &
