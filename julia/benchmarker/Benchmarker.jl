module Benchmarker

export cachescrub, gcscrub

using Statistics
using DelimitedFiles

include("Results.jl")
include("CSV.jl")

gcscrub() = (GC.gc(); GC.gc(); GC.gc(); GC.gc())

A = rand(7500000)
cachescrub() = (A .+= 0.0001)

function measure(iters, f, args...)
  timings = Array{Float64}(undef, iters)

  local elapsed_time::Float64 = 0.0
  for i=1:iters
    elapsed_time, result = f(args...)
    timings[i] = elapsed_time
  end
  return Results(iters, timings)
end
end
