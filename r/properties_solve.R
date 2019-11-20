library("sets")

solve_b <- function(A, B){

    at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
    bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    ct <- matrix(B, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
 start.time <- Sys.time()
    ct <- solve(at, bt)
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

properties_solve <- function(b, m, rhs){

    B <- matrix(data = rnorm(m * rhs), nrow=m, ncol=rhs)
    C <- matrix(data = rnorm(m * rhs), nrow=m, ncol=rhs)

    A <- matrix(data = rnorm(m * m), nrow=m, ncol=m)
    A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
    diag(A) <- diag(A) + m                # Make A Positive Definite
    cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
    res1 <- benchmark('solve_spd', solve_b, A, B)

    A <- matrix(data = rnorm(m * m), nrow=m, ncol=m)
    A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
    A[1, 1] <- -1.0
    cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
    res2 <- benchmark('solve_sym', solve_b, A, B)

    A <- matrix(data = rnorm(m * m), nrow=m, ncol=m)
    A[upper.tri(A, diag=FALSE)] <- 0.0 # Transform A into a lower triangular matrix
    diag(A) <- diag(A) + m                # Make A Positive Definite
    res3 <- benchmark('solve_tri', solve_b, A, B)

    A <- matrix(data = rnorm(m * m), nrow=m, ncol=m)
    A <- diag(diag(A), nrow(A), ncol(A))
    res4 <- benchmark('solve_dia', solve_b, A, B)

}
