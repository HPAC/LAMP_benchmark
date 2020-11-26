library("sets")
library(Matrix)

solve_b <- function(n, rhs, type) {

    if ("gen" %in% type) {
      A <- rsparsematrix(n, n, density=density, rand.x=rnorm)
      diag(A) <- diag(A) + 1.0
      print("gen")
    }
    else if  ("sym" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=density, rand.x=rnorm)
      A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
      diag(A) <- (diag(A) + 2.0)
      cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
      print("sym")
    }
    else if ("spd" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=density)
      A[lower.tri(A)] <- t(A)[lower.tri(A)] # Transform A into a symmetric matrix
      diag(A) <- (diag(A) + n)              # Make A Positive Definite
      cat(c("A symmetric: ", all.equal(A, t(A)), "\n"), sep="")
      print("spd")
    }
    else if ("tri" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=2.0*density)
      A[upper.tri(A, diag=FALSE)] <- 0.0 # Transform A into a lower triangular matrix
      diag(A) <- (diag(A) + 1.0)
      print("tri")
    }
    print(condest(A)$est)
    print(nnzero(A))

    B <- matrix(data = rnorm(n * rhs), nrow=n, ncol=rhs)
    ct <- matrix(0.0, ncol=ncol(B), nrow=nrow(B))
    cache_scrub()
    start.time <- Sys.time()
    ct <- solve(A, B)
    end.time <- Sys.time()
    return(tuple(as.double(end.time-start.time), ct))
}

properties_solve_sparse <- function(b, n, rhs, density){

  # I create the matrices withing the function being benchmarked every time because R caches the results somehow and I
  # can't find a function that would just perform a "deepcopy" equivalent to Python to the arguments supplied.
  res1 <- benchmark('solve_sp_gen', solve_b, n, rhs, "gen")
  res2 <- benchmark('solve_sp_sym', solve_b, n, rhs, "sym")
  res3 <- benchmark('solve_sp_spd', solve_b, n, rhs, "spd")
  res4 <- benchmark('solve_sp_tri', solve_b, n, rhs, "tri")
}
