library("sets")

add <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
    start.time <- Sys.time()
    bt <- at + bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), bt))
}

scal <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    cache_scrub()
    start.time <- Sys.time()
    at <- 3.0 * at
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), at))
}

add_scal <- function(b, ...){
    res1 <- benchmark('add', add, ...)
    res2 <- benchmark('scal', scal, ...)
}
