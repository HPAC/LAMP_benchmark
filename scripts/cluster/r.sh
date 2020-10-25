#!/bin/bash

source ~/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/r

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

${R_SCRIPT} main.R

