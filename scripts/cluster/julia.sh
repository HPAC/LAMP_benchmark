#!/bin/bash

source ~/.zshrc.lamp

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

export LD_LIBRARY_PATH="/opt/intel/mkl/2019.0.117/lib/intel64:$LD_LIBRARY_PATH"
export LAMP_JULIA_DIR=${LAMP_EXPERIMENTS}/julia
cd $LAMP_JULIA_DIR
pwd

${JULIA_DIR}/julia --version
${JULIA_DIR}/julia main.jl
