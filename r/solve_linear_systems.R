library("sets")

solve_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()
    ct <- solve(at) %*% bt
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

solve_rec <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()
    ct <- solve(at, bt)
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

solve_linear_systems <- function(b, ...){

    res1 <- benchmark('solve_nai', solve_nai, ...)
    res2 <- benchmark('solve_rec', solve_rec, ...)
    cat(c("Solve correctness: ", all.equal(res1, res2), "\n"), sep="")

    args <- list(...)
    A <- args[[1]]
    Bt <- args[[2]]
    B <- matrix(rnorm(5 * nrow(Bt) * nrow(A)), nrow=nrow(Bt), ncol=(5 * nrow(A)))
    res3 <- benchmark('solve_large_nai', solve_nai, A, B)
    res4 <- benchmark('solve_large_rec', solve_rec, A, B)
    cat(c("Solve large correctness: ", all.equal(res3, res4), "\n"), sep="")
}

