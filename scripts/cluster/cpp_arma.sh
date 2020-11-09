#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/cpp/armadillo

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
#export GOMP_CPU_AFFINITY=$2
#export KMP_AFFINITY=compact,verbose
#export KMP_AFFINITY=verbose,granularity=core,proclist=[$2],explicit
#export LD_LIBRARY_PATH="${MKLROOT}/../lib/intel64:$LD_LIBRARY_PATH"  # Runtime cannot find libiomp5.

make clean
make -j 24
numactl -N 0 ./bench_armadillo
make clean
