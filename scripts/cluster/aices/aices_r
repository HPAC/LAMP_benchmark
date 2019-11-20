#!/bin/bash

module load DEVELOP
module load intel/19.0
module load gcc/8 # required for libgfortran

source ~/.zshrc.local
cd ${LAMP_EXPERIMENTS}/r

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

${R_SCRIPT} main.R

