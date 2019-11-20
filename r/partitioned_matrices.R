library("sets")

blocked_solve_naive <- function(A1, A2, B){

    a1t <- matrix(A1, ncol=ncol(A1), nrow=nrow(A1))
    a2t <- matrix(A2, ncol=ncol(A2), nrow=nrow(A2))
    bt  <- matrix(B,  ncol=ncol(B),  nrow=nrow(B))
    ct  <- matrix(0,  ncol=ncol(B),  nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()

    ct <- solve(rbind(cbind(a1t, matrix(0, nrow=dim(a1t)[1], ncol=dim(a1t)[2])),
                      cbind(matrix(0, nrow=dim(a2t)[1], ncol=dim(a2t)[2]), a2t)), bt)

    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

blocked_solve_recommended <- function(A1, A2, B){
    a1t <- matrix(A1, ncol=ncol(A1), nrow=nrow(A1))
    a2t <- matrix(A2, ncol=ncol(A2), nrow=nrow(A2))
    bt  <- matrix(B,  ncol=ncol(B),  nrow=nrow(B))
    ct  <- matrix(0,  ncol=ncol(B),  nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()

    b1 <- bt[1:dim(a1t)[1]             , 1:dim(bt)[2], drop=FALSE]
    b2 <- bt[(dim(a1t)[1]+1):dim(bt)[1], 1:dim(bt)[2], drop=FALSE]
    #cat(c("b1: ", dim(b1), "\n"), sep="")
    #cat(c("b2: ", dim(b2), "\n"), sep="")
    ct   <- rbind(solve(A1, b1), solve(A2, b2))

    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

partitioned_matrices <- function(b, ...){

    res1 <- benchmark("compact", blocked_solve_naive, ...)
    res2 <- benchmark("blocked", blocked_solve_recommended, ...)
    cat(c("PartitionedMatrices correctness: ", all.equal(res1, res2), "\n"), sep="")
}
