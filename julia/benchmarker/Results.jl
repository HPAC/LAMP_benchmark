##############
#  Results   #
##############

struct Results
  samples::Int
  min_time::Float64
  timings::Array{Float64, 1}
end

function Results(n::Int, timings::Array{Float64, 1})
  samples = n
  min_time = minimum(timings)

  return Results(samples, min_time, timings)
end
