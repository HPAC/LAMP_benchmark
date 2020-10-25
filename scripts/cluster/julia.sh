#!/bin/bash

source ~/.zshrc.lamp

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

export LAMP_JULIA_DIR=${LAMP_EXPERIMENTS}/julia
cd $LAMP_JULIA_DIR
pwd

${JULIA_DIR}/julia main.jl
