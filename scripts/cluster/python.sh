#!/bin/bash

source ~/.zshrc.lamp
module load DEVELOP
module load pythoni/3.6.2019

cd ${LAMP_EXPERIMENTS}/python

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

${MKL_PYTHON} main.py

