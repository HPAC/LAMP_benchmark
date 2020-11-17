#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/julia

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
export JULIA_NUM_THREADS=$1
export LD_LIBRARY_PATH="${MKLROOT}/../lib/intel64:$LD_LIBRARY_PATH"  # Runtime cannot find libiomp5.

${JULIA} --version
${JULIA} main.jl
