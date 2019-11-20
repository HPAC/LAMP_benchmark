#include "tools.h"

using namespace std;

Benchmarker::Benchmarker(string name, char delim)
{
  this->file = new ofstream(string(LAMP_OUTPUT_DIR) + name + ".txt");
  this->file_timings = new ofstream(string(LAMP_OUTPUT_DIR) + name + "_timings.txt");
  this->delim = delim;
  if (this->file->is_open()) {
    *(this->file) << "algorithm" << this->delim;
    *(this->file) << "Eigen" << this->delim;
    *(this->file) << std::endl;
  } else {
    printf("ERROR: File not open");
  }
  this->cs = (double*)malloc(LAMP_L3_CACHE_SIZE * sizeof(double));
}

Benchmarker::~Benchmarker()
{
  this->file->close();
  this->file_timings->close();
  free(this->cs);
}

void Benchmarker::add(vector<double> data, string name)
{
  if (this->file->is_open()) {
    *(this->file) << name << this->delim;
    *(this->file) << *std::min_element(data.begin(), data.end()) << this->delim;
    *(this->file) << std::endl;
  } else {
    printf("ERROR: File not open");
  }

  if (this->file_timings->is_open()) {
    *(this->file_timings) << name << this->delim;
    for (auto it = data.begin(); it != data.end(); it++)
      *(this->file_timings) << *it << this->delim;
    *(this->file_timings) << std::endl;
  } else {
    printf("ERROR: Timings File not open");
  }
}

double Benchmarker::cache_scrub(void)
{
  std::chrono::high_resolution_clock::time_point t1, t2;
  t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < LAMP_L3_CACHE_SIZE; i++)
    this->cs[i] += 1e-3;
  t2 = std::chrono::high_resolution_clock::now();
  this->cs_time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;
  return this->cs_time;
}
