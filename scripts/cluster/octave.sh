#!/bin/bash

source ${HOME}/.zshrc.lamp

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

export LAMP_OCTAVE_DIR="${LAMP_EXPERIMENTS}/octave"
cd $LAMP_OCTAVE_DIR

octave --version
octave main.m
