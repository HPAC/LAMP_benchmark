#!/bin/bash

source ${HOME}/.zshrc.lamp
export LAMP_OCTAVE_DIR="${LAMP_EXPERIMENTS}/octave"
cd $LAMP_OCTAVE_DIR

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
export GOMP_CPU_AFFINITY=$2

octave --version
octave main.m
