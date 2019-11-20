#ifndef BENCH_EIGEN_TOOLS_H
#define BENCH_EIGEN_TOOLS_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef LAMP_OUTPUT_DIR
#define LAMP_OUTPUT_DIR "../results/"
#endif

#define BENCHMARK(benchmarker, function, container) \
  benchmarker.cache_scrub();                        \
  t1 = std::chrono::high_resolution_clock::now();   \
  function;                                         \
  t2 = std::chrono::high_resolution_clock::now();   \
  container = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

class Benchmarker {

  char delim;

  std::ofstream* file;
  std::ofstream* file_timings;

  double* cs;
  double cs_time;

  public:
  Benchmarker(){};
  Benchmarker(std::string name, char delim = ';');
  ~Benchmarker();

  void add(std::vector<double> data, std::string name = "default");
  double cache_scrub(void);
};

#endif //BENCH_EIGEN_TOOLS_H
