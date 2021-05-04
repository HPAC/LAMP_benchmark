#!/bin/bash

source ${HOME}/.zshrc.lamp

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1

module purge
module load DEVELOP
module load intel/19.0

cd ${LAMP_EXPERIMENTS}/python/numpy
${PYTHON} main.py
cd ${LAMP_EXPERIMENTS}/python/torch
${PYTHON} main.py
cd ${LAMP_EXPERIMENTS}/python/tensorflow
${PYTHON} main.py
