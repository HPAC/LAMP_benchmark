library("sets")
library(Matrix)

solve_b <- function(n, rhs, type) {

    print("selecting matrix")
    if ("gen" %in% type) {
      A <- rsparsematrix(n, n, density=density, rand.x=rnorm)
      diag(A) <- (diag(A) + 1.0)
      print(isSymmetric(A))
      print("gen")
    }
    else if  ("sym" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=density, rand.x=rnorm, symmetric=TRUE)
      A <- as(A, "sparseMatrix")
      diag(A) <- (diag(A) + 2.0)
      print(isSymmetric(A))
      print("sym")
    }
    else if ("spd" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=density, rand.x=rnorm, symmetric=TRUE)
      A <- as(A, "sparseMatrix")
      diag(A) <- (diag(A) + n)  # Make A Positive Definite
      print(isSymmetric(A))
      print("spd")
    }
    else if ("tri" %in% type) {
      A <- rsparsematrix(nrow=n, ncol=n, density=2.0*density, rand.x=rnorm)
      mat.summ   <- summary(A)
      lower.summ <- subset(mat.summ, i >= j)
      print(dim(A))
      A <- sparseMatrix(i = lower.summ$i, j = lower.summ$j, x = lower.summ$x, dims = dim(A))
      A <- as(A, "dtCMatrix")
      A <- as(A, "sparseMatrix")
      diag(A) <- (diag(A) + 1.0)
      print(isTriangular(A))
      print("tri")
    }
    # print(condest(A)$est)  # Comment out because R caches the factorization to use later to solve the linear system.
    print(nnzero(A))

    B <- matrix(data = rnorm(n * rhs), nrow=n, ncol=rhs)
    ct <- matrix(0.0, ncol=ncol(B), nrow=nrow(B))
    cstime_start <- Sys.time()
    cache_scrub()
    cstime_end <- Sys.time()
    print("cs_time:")
    print(as.double(cstime_end - cstime_start))

    solve_time_start <- Sys.time()
    ct <- solve(A, B)
    solve_time_end <- Sys.time()
    print("solve_time")
    print(as.double(solve_time_end-solve_time_start))
    return(tuple(as.double(solve_time_end-solve_time_start), ct))
}

properties_solve_sparse <- function(b, n, rhs, density){

  # I create the matrices withing the function being benchmarked every time because R caches the results somehow and I
  # can't find a function that would just perform a "deepcopy" equivalent to Python to the arguments supplied.
  res1 <- benchmark('solve_sp_gen', solve_b, n, rhs, "gen")
  res2 <- benchmark('solve_sp_sym', solve_b, n, rhs, "sym")
  res3 <- benchmark('solve_sp_spd', solve_b, n, rhs, "spd")
  res4 <- benchmark('solve_sp_tri', solve_b, n, rhs, "tri")
}
