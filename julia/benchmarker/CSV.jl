##############
#    CSV     #
##############

mutable struct CSV
  file::IOStream
  file_timings::IOStream
  delimiter::Char
end

function CSV(file_name::String, delimiter::Char = ';')
  labels = reshape(["algorithm", "Julia"], (1, :))

  f = open(string(file_name, ".txt"), "w")
  writedlm(f, labels, delimiter)

  ft = open(string(file_name, "_timings.txt"), "w")
  return CSV(f, ft, delimiter)
end

function add_data(c::CSV, name::AbstractString, results::Results) where P
  data = [reshape([name], (1, :)) [results.min_time]]
  writedlm(c.file, data, c.delimiter)

  data = [reshape([name], (1, :)) transpose(results.timings)]
  writedlm(c.file_timings, data, c.delimiter)
end

function close(c::CSV)
  close(c.file)
  close(c.file_timings)
end
