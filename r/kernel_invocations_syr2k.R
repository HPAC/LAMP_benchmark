library("sets")

syr2k_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- at %*% t(bt) + bt %*% t(at) + ct
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

syr2k_implicit_noup <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct <- at %*% t(bt) + bt %*% t(at)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

kernel_invocations_syr2k <- function(b, ...){
    res1 = benchmark('syr2k_implicit', syr2k_implicit, ...)
    res2 = benchmark('syr2k_implicit_noup', syr2k_implicit_noup, ...)
}
