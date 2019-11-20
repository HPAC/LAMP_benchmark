#!/bin/bash

module purge
module load DEVELOP
module load intel/19.0
module load gcc/8

source ~/.zshrc.local
cd ${LAMP_EXPERIMENTS}/cpp/eigen

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

make clean
make -j 10
./bench_eigen
make clean
