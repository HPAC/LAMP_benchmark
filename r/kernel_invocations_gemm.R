library("sets")

gemm_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()
    ct <- at %*% bt + ct
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

gemm_implicit_noup <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()
    ct <- at %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

gemm_implicit_coeff <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- 3.0 * at %*% bt + ct
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

gemm_implicit_double_coeff <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- 3.0 * at %*% bt + 3.0 * ct
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

symm_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- at %*% bt + ct
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

trmm_implicit <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()
    bt <- at %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), bt))
}

diagmm <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- at %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

kernel_invocations_gemm <- function(b, ...){
    res1 <- benchmark('gemm_implicit', gemm_implicit, ...)
    res2 <- benchmark('gemm_implicit_coeff', gemm_implicit_coeff, ...)
    res3 <- benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, ...)
    res4 <- benchmark('gemm_implicit_noup', gemm_implicit_noup, ...)

    args = list(...)
    n = dim(args[[1]])[1]
    A <- matrix(data=rnorm(n*n), ncol=n, nrow=n)
    B <- matrix(data=rnorm(n*n), ncol=ncol(A), nrow=nrow(A))
    C <- matrix(data=rnorm(n*n), ncol=ncol(A), nrow=nrow(A))

    A[upper.tri(A, diag=FALSE)] <- 0.0 # Transform A into a lower triangular matrix
    res5 <- benchmark('trmm_implicit', trmm_implicit, A, B)

    A <- diag(diag(A), nrow(A), ncol(A))
    res6 <- benchmark('diagmm', diagmm, A, B, C)
}

