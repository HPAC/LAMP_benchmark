library("sets")

naive_loop_tr <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()

    for (i in 1:dim(C)[2]){
        ct[, i] = at %*% bt[, i]
    }
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

recommended_loop_tr <- function(A, B, C){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
    cache_scrub()
    start.time <- Sys.time()
    ct = at %*% bt
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

loop_translation <- function(b, ...){

    res1 = benchmark("loop_translation_nai", naive_loop_tr, ...)
    res2 = benchmark("loop_translation_rec", recommended_loop_tr, ...)
    cat(c("LoopTranslation correctness: ", all.equal(res1, res2), "\n"), sep="")
}

