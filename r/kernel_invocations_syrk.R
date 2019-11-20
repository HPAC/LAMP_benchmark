library("sets")

syrk_implicit <- function(A, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()
    ct <- at %*% t(at) + ct
    end.time <- Sys.time()
    res = tuple(as.double(end.time-start.time), ct)

    return(res)
}

syrk_implicit_noup <- function(A, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()
    ct <- at %*% t(at)
    end.time <- Sys.time()
    res = tuple(as.double(end.time-start.time), ct)

    return(res)
}

kernel_invocations_syrk <- function(b, ...){
    res1 <- benchmark('syrk_implicit', syrk_implicit, ...)
    res2 <- benchmark('syrk_implicit_noup', syrk_implicit_noup, ...)
}
