library("sets")

naive_loop <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()

    temp = matrix(0, nrow=dim(A)[1], ncol=dim(B)[2])
    for (i in 1:dim(C)[2]){
        temp = at %*% bt
        ct[i] = temp[i, i]
    }
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

recommended_loop <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
 start.time <- Sys.time()
    temp = at %*% bt
    for (i in 1:dim(C)[2]){
        ct[i] = temp[i, i]
    }
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

index_problems <- function(b, ...){

    res1 = benchmark("loop_nai", naive_loop, ...)
    res2 = benchmark("loop_rec", recommended_loop, ...)
    cat(c("IndexProblems correctness: ", all.equal(res1, res2), "\n"), sep="")
}

