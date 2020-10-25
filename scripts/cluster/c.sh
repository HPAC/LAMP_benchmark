#!/bin/bash

module purge
module load DEVELOP
module load intel/19.0
module load gcc/8

source ${HOME}/.zshrc.local
cd ${LAMP_EXPERIMENTS}/c

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1
export output=results/c.txt

make clean
make all -j 10

echo "algorithm;m;k;n;C;cs_time" > ${output}
export LAMP_m=3000
export LAMP_k=550
export LAMP_n=3000
./bin/gemm.x       $LAMP_m $LAMP_k $LAMP_n >> ${output}
./bin/gemm.x       $LAMP_n $LAMP_n $LAMP_n large >> ${output}
./bin/gemm_noup.x  $LAMP_m $LAMP_k $LAMP_n >> ${output}

./bin/syrk.x       $LAMP_n $LAMP_k >> ${output}
./bin/syrk_noup.x  $LAMP_n $LAMP_k >> ${output}

./bin/syr2k.x      $LAMP_n $LAMP_k >> ${output}
./bin/syr2k_noup.x $LAMP_n $LAMP_k >> ${output}

./bin/trmm.x       $LAMP_m $LAMP_n >> ${output}
./bin/diagmm.x     $LAMP_n >> ${output}

./bin/subexpr_nai.x $LAMP_m $LAMP_k >> ${output}
./bin/subexpr_rec.x $LAMP_m $LAMP_k >> ${output}

./bin/mc_mixed.x $LAMP_m $LAMP_k $LAMP_n >> ${output}

export LAMP_tr_m=80
export LAMP_tr_k=80
export LAMP_tr_n=80
./bin/transposition.x $LAMP_tr_m $LAMP_tr_k $LAMP_tr_n >> ${output}

export LAMP_rhs_small=100
./bin/solve_naive.x       $LAMP_n $LAMP_rhs_small >> ${output}
./bin/solve_recommended.x $LAMP_n $LAMP_rhs_small >> ${output}

./bin/solve_recommended_spd.x $LAMP_n $LAMP_rhs_small >> ${output}
./bin/solve_recommended_sym.x $LAMP_n $LAMP_rhs_small >> ${output}
./bin/solve_recommended_tri.x $LAMP_n $LAMP_rhs_small >> ${output}
./bin/solve_recommended_dia.x $LAMP_n $LAMP_rhs_small >> ${output}

export LAMP_rhs_large=6000
./bin/solve_naive.x       $LAMP_n $LAMP_rhs_large large >> ${output}
./bin/solve_recommended.x $LAMP_n $LAMP_rhs_large large >> ${output}
