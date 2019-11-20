library(sets)

diag_mult_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- diag(ct)
    cache_scrub()
    start.time <- Sys.time()
    ct <- diag(at %*% bt)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

diag_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- diag(ct)
    cache_scrub()
 start.time <- Sys.time()
    ct <- diag(at + bt)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

diag_rec <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- diag(ct)
    cache_scrub()
 start.time <- Sys.time()
    ct <- diag(at) + diag(bt)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

diagonal_elements <- function(b, ...){

    res3 <- benchmark('diag_mult_nai', diag_mult_nai, ...)
    res1 <- benchmark('diag_add_nai', diag_nai, ...)
    res2 <- benchmark('diag_add_rec', diag_rec, ...)
    cat(c("DiagonalElements correctness: ", all.equal(res1, res2), "\n"), sep="")
}

