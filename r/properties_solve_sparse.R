library("sets")

solve_b <- function(A, B){

    ct <- matrix(0.0, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
    start.time <- Sys.time()
    ct <- solve(A, B)
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

properties_solve_sparse <- function(b, n, rhs, density){

    B <- matrix(data = rnorm(n * rhs), nrow=n, ncol=rhs)

    A <- matrix(0, nrow=n, ncol=n, sparse=TRUE)
    iz <- sample(1:(n * n), size = n * n * density, replace = FALSE)
    A[iz] <- rnorm(n*n*density)
    diag(A) <- diag(A) + 1.0
    cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
    res1 <- benchmark('solve_sp_gen', solve_b, A, B)

    A <- matrix(0, nrow=n, ncol=n, sparse=TRUE)
    iz <- sample(1:(n * n), size = n * n * density, replace = FALSE)
    A[iz] <- rnorm(n*n*density)
    A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
    diag(A) <- diag(A) + 2.0
    cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
    res2 <- benchmark('solve_sp_sym', solve_b, A, B)

    A <- matrix(0, nrow=n, ncol=n, sparse=TRUE)
    iz <- sample(1:(n * n), size = n * n * density, replace = FALSE)
    A[iz] <- rnorm(n*n*density)
    A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
    diag(A) <- diag(A) + m                # Make A Positive Definite
    cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
    res1 <- benchmark('solve_sp_spd', solve_b, A, B)

    A <- matrix(0, nrow=n, ncol=n, sparse=TRUE)
    iz <- sample(1:(n * n), size = n * n * density, replace = FALSE)
    A[iz] <- rnorm(n*n*density)
    A[upper.tri(A, diag=FALSE)] <- 0.0 # Transform A into a lower triangular matrix
    diag(A) <- diag(A) + 1
    res3 <- benchmark('solve_sp_tri', solve_b, A, B)
}
