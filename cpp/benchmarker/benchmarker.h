#ifndef LAMP_BENCHMARK_BENCHMARKER_H
#define LAMP_BENCHMARK_BENCHMARKER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using clockk = std::chrono::high_resolution_clock;
using time_point = std::chrono::high_resolution_clock::time_point;

class Benchmarker
{
  std::ofstream file;
  std::ofstream file_timings;
  int iterations{10};
  char delim{';'};

  vector<double> cs;
  double cs_time;

  time_point t1, t2;

public:
  Benchmarker();

  ~Benchmarker() = default;

  Benchmarker(string &name, string &file_name, string &file_timings_name, int cache_size,
              int iterations = 10, char delimiter = ';')
  {
    file = std::ofstream(file_name);
    file_timings = std::ofstream(file_timings_name);
    delim = delimiter;
    this->iterations = iterations;
    if (file.is_open())
      file << "algorithm" << delim << name << endl;
    else
      cerr << "ERROR: File not open" << endl;
    cs = vector<double>(cache_size, 0.0);
    cout << "Library:               " << name << endl;
    cout << "Output file:           " << file_name << endl;
    cout << "Output file (timings): " << file_timings_name << endl;
    cout << "Cache size:            " << cache_size << endl;
    cout << "Iterations:            " << iterations << endl;
    cout << "Delimiter:             " << delim << endl;

  }

  template<typename F, typename... Args>
  void benchmark(string &&name, F &&f, Args... args)
  {
    vector<double> timings(iterations, 0.0);
    for (auto & t : timings)
      t = benchmark_(f, args...);

    if (file.is_open())
      file << name << delim << *std::min_element(timings.begin(), timings.end()) << endl;
    else
      cerr << "ERROR: File not open" << endl;

    if (file_timings.is_open())
    {
      file_timings << name << delim;
      std::for_each(timings.begin(), timings.end(),
                    [&](const auto &t)
                    {
                      file_timings << t << delim;
                    });
      file_timings << endl;
    } else
      cerr << "ERROR: Timings File not open" << endl;
  }

private:

  template<typename F, typename... Args>
  double benchmark_(F &&f, Args... args)
  {
    cache_scrub_();
    t1 = clockk::now();
    std::forward<decltype(f)>(f)(args...);
    t2 = clockk::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;
  }

  inline void cache_scrub_(void)
  {
    t1 = clockk::now();
    for (auto &e : cs) e += 1e-3;
    t2 = clockk::now();
    cs_time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;
  };

};

#endif //LAMP_BENCHMARK_BENCHMARKER_H
