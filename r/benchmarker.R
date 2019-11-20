reps <- as.numeric(Sys.getenv("LAMP_REPS"))
output_dir <- Sys.getenv("LAMP_OUTPUT_DIR")
l3_size <- as.numeric(Sys.getenv("LAMP_L3_CACHE_SIZE"))
file_out  <- "default"
file_time <- "default_time"

cs <- matrix(data = rnorm(l3_size), nrow = 1, ncol = l3_size)

cache_scrub <- function(){
  for (j in 1:dim(cs)[2]){
    cs[j] <<- cs[j] + 1e-3
  }
}

init_benchmarker <- function(filename){

  file_out  <<- paste(output_dir, filename, ".txt", sep="")
  file_time <<- paste(output_dir, filename, "_timings.txt", sep="")

  cat("algorithm;R;\n", file=file_out, sep=";")
  cat("", file=file_time, sep=";")

  cat(c("Benchmarker initialized:", file_out, file_time, reps, "\n"), sep=" ")
}

benchmark <- function(name, func, ...){

  times <- matrix(0, nrow=1, ncol=reps)
  result <- ""
  for (i in 1:reps){
      res = func(...)
      times[i] <- res[[1]]
      result <- res[[2]]
  }

  cat(c(name, apply(times, 1, min), "\n"), file=file_out, sep=";", append=TRUE)
  cat(c(name, times, "\n"), file=file_time, sep=";", append=TRUE)

  return(result)
}
