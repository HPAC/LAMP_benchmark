#! /bin/bash

module purge
module load DEVELOP
module load intel/18.0
module load gcc/8

cd ${HPC_DIR}/src
wget https://cran.r-project.org/src/base/R-3/R-3.5.3.tar.gz
tar xvf R-3.5.3.tar.gz
rm R-3.5.3.tar.gz
cd R-3.5.3
#sudo apt install build-essential\
 #zlib1g-dev                     \
 #libbz2-dev                     \
 #liblzma-dev                    \
 #libpcre2-dev                   \
 #libreadline-dev                \
 #libpcre3-dev                   \
 #libcurl4-openssl-dev
BLAS_LIBS="-m64 -I$MKLROOT/include -L$MKLROOT/lib/intel64 -Wl,--no-as-needed -lmkl_gf_lp64 -Wl,--start-group -lmkl_sequential -lmkl_core -Wl,--end-group -fopenmp -ldl -lpthread -lm" ./configure --with-blas="$BLAS_LIBS" --with-lapack="$BLAS_LIBS" --with-x=no --prefix=${HPC_DIR}/lib | grep BLAS
make -j 16
make install
