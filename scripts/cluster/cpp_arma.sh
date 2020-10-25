#!/bin/bash

source ~/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/cpp/armadillo

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

echo ${LAMP_OUTPUT_DIR}

make clean
make -j 24
./bench_armadillo
make clean
