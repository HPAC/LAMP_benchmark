library("sets")

mc_l_r_orig <- function(m, A, B){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  mt <- matrix(m, ncol=ncol(m), nrow=nrow(m))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(0, nrow=dim(m)[1], ncol=dim(B)[2])
  cache_scrub()
 start.time <- Sys.time()
  ct <- mt %*% at %*% bt
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), ct))
}

mc_l_r_guid <- function(m, A, B){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  mt <- matrix(m, ncol=ncol(m), nrow=nrow(m))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(0, nrow=dim(m)[1], ncol=dim(B)[2])
  cache_scrub()
 start.time <- Sys.time()
  ct <- (mt %*% at) %*% bt
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), ct))
}

mc_r_l_orig <- function(m, A, B){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  mt <- matrix(m, ncol=ncol(m), nrow=nrow(m))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(0, nrow=dim(A)[1], ncol=dim(m)[2])
  cache_scrub()
 start.time <- Sys.time()
  ct <- at %*% bt %*% mt
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), ct))
}

mc_r_l_guid <- function(m, A, B){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  mt <- matrix(m, ncol=ncol(m), nrow=nrow(m))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(0, nrow=dim(A)[1], ncol=dim(m)[2])
  cache_scrub()
 start.time <- Sys.time()
  ct <- at %*% (bt %*% mt)
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), ct))
}

mc_mixed_orig <- function(A, B, C, D){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
  dt <- matrix(D, ncol=ncol(D), nrow=nrow(D))
  res <- matrix(0, nrow=dim(A)[1], ncol=dim(D)[2])
  cache_scrub()
 start.time <- Sys.time()
  res <- at %*% bt %*% ct %*% dt
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), res))
}

mc_mixed_guid <- function(A, B, C, D){

  at <- matrix(A, ncol=ncol(A), nrow=nrow(A))
  bt <- matrix(B, ncol=ncol(B), nrow=nrow(B))
  ct <- matrix(C, ncol=ncol(C), nrow=nrow(C))
  dt <- matrix(D, ncol=ncol(D), nrow=nrow(D))
  res <- matrix(0, nrow=dim(A)[1], ncol=dim(D)[2])
  cache_scrub()
 start.time <- Sys.time()
  res <- (at %*% bt) %*% (ct %*% dt)
  end.time <- Sys.time()

  return(tuple(as.double(end.time-start.time), res))
}

matrix_chain <- function(b, ...){

  args = list(...)

  n = dim(args[[1]])[1]

  m1 <- matrix(data = rnorm((n/5)*n), nrow = n/5, ncol = n)
  res1 <- benchmark('mc_l_r_orig', mc_l_r_orig, m1, ...)
  res2 <- benchmark('mc_l_r_guid', mc_l_r_guid, m1, ...)
  cat(c("mc_l_r correctness: ", all.equal(res1, res2), "\n"), sep="")

  m2 <- matrix(data = rnorm((n/5)*n), nrow = n, ncol = n/5)
  res1 <- benchmark('mc_r_l_orig', mc_r_l_orig, m2, ...)
  res2 <- benchmark('mc_r_l_guid', mc_r_l_guid, m2, ...)
  cat(c("mc_r_l correctness: ", all.equal(res1, res2), "\n"), sep="")

  Al <- matrix(data = rnorm(n*n), nrow = n, ncol = n)
  Bl <- matrix(data = rnorm(n*(n/5)), nrow = n, ncol = n/5)
  Cl <- matrix(data = rnorm((n/5)*n), nrow = n/5, ncol = n)
  Dl <- matrix(data = rnorm(n*n), nrow = n, ncol = n)
  res1 <- benchmark('mc_mixed_orig', mc_mixed_orig, Al, Bl, Cl, Dl)
  res2 <- benchmark('mc_mixed_guid', mc_mixed_guid, Al, Bl, Cl, Dl)
  cat(c("mc_mixed correctness: ", all.equal(res1, res2), "\n"), sep="")

}
