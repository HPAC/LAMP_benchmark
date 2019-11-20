library("sets")

tr_tt_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct = t(at) %*% t(bt)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

tr_nt_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct = at %*% t(bt)
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

tr_tn_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct = t(at) %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

tr_nn_implicit <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    ct = at %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

transposition <- function(b, ...){
    res <- benchmark('tr_nn_implicit', tr_nn_implicit, ...)
    res <- benchmark('tr_tn_implicit', tr_tn_implicit, ...)
    res <- benchmark('tr_nt_implicit', tr_nt_implicit, ...)
    res <- benchmark('tr_tt_implicit', tr_tt_implicit, ...)
}
