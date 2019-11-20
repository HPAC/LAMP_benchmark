library("sets")

subexpr_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    kt <- matrix(0L, ncol=ncol(B), nrow=nrow(A))
    xt <- matrix(0L, ncol=ncol(B), nrow=nrow(A))
    cache_scrub()
 start.time <- Sys.time()
    kt <- at %*% bt + at %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), kt))
}

subexpr_rec <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    kt <- matrix(0L, ncol=ncol(B), nrow=nrow(A))
    xt <- matrix(0L, ncol=ncol(B), nrow=nrow(A))
    cache_scrub()
 start.time <- Sys.time()
    kt <- at %*% bt
    kt <- kt + kt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), kt))
}

common_subexpressions <- function(b, ...){
    res1 = benchmark('subexpr_nai', subexpr_nai, ...)
    res2 = benchmark('subexpr_rec', subexpr_rec, ...)
    cat(c("Common Subexpressions correct: ", all.equal(res1, res2), "\n"), sep="")
}
