library(sets)

part_op_ele_mult_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    cache_scrub()
    start.time <- Sys.time()
    ct <- (at %*% bt)[2, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

part_op_ele_add_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    cache_scrub()
    start.time <- Sys.time()
    ct <- (at + bt)[2, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

part_op_ele_add_rec <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    ct <- diag(ct)
    cache_scrub()
    start.time <- Sys.time()
    ct <- at[2,2] + bt[2, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

part_op_col_mult_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    cache_scrub()
    start.time <- Sys.time()
    ct <- (at %*% bt)[, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

part_op_col_add_nai <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    cache_scrub()
    start.time <- Sys.time()
    ct <- (at + bt)[, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

part_op_col_add_rec <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=1)
    ct <- diag(ct)
    cache_scrub()
    start.time <- Sys.time()
    ct <- at[,2] + bt[, 2]
    end.time <- Sys.time()

    return(tuple(as.double(end.time-start.time), ct))
}

partial_operand <- function(b, ...){

    res3 <- benchmark('part_op_col_mult_nai', part_op_col_mult_nai, ...)
    res1 <- benchmark('part_op_col_add_nai', part_op_col_add_nai, ...)
    res2 <- benchmark('part_op_col_add_rec', part_op_col_add_rec, ...)
    cat(c("PartialOperand correctness: ", all.equal(res1, res2), "\n"), sep="")

    res6 <- benchmark('part_op_ele_mult_nai', part_op_ele_mult_nai, ...)
    res4 <- benchmark('part_op_ele_add_nai', part_op_ele_add_nai, ...)
    res5 <- benchmark('part_op_ele_add_rec', part_op_ele_add_rec, ...)
    cat(c("PartialOperand correctness: ", all.equal(res4, res5), "\n"), sep="")
}

