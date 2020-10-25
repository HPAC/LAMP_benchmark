#!/bin/bash

source $HOME/.zshrc.lamp

export LAMP_LOG_DIR=${LAMP_EXPERIMENTS}/scripts/cluster/log

#sbatch -J Matlab -o ${LAMP_LOG_DIR}/matlab.log    -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/matlab.sh
#sbatch -J Octave -o ${LAMP_LOG_DIR}/octave.log    -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/octave.sh
#sbatch -J Julia  -o ${LAMP_LOG_DIR}/julia.log     -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/aices/aices_julia
#sbatch -J C      -o ${LAMP_LOG_DIR}/c.log         -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/c.sh
sbatch -J CppArm -o ${LAMP_LOG_DIR}/cpp_arma.log -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_arma.sh
#sbatch -J CppEig -o ${LAMP_LOG_DIR}/cpp_eigen.log -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_eig.sh
#sbatch -J Python -o ${LAMP_LOG_DIR}/python.log    -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/python.sh
#sbatch -J R      -o ${LAMP_LOG_DIR}/R.log         -N 1 -n 1 --mem=5000 -t 02:00:00 --partition=ih -A aices2 -C hwx2680 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/r.sh
