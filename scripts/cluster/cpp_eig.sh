#!/bin/bash

source ~/.zshrc.lamp

cd ${LAMP_EXPERIMENTS}/cpp/eigen

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

make clean
make -j 10
./bench_eigen
make clean
