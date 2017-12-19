#!/usr/bin/bash

module load OpenMPI/2.1.1-GCC-6.4.0-2.28
mpiCC bitonic-sort.cpp -o bitonic
mpirun -np 9 ./bitonic
