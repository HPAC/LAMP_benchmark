#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/julia

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
export GOMP_CPU_AFFINITY=$2

export LD_LIBRARY_PATH="/opt/intel/mkl/2019.0.117/lib/intel64:$LD_LIBRARY_PATH"  # Julia runtime cannot find libiomp5. Adding its location to LD_LIBRARY_PATH.

${JULIA_DIR}/julia --version
${JULIA_DIR}/julia main.jl
