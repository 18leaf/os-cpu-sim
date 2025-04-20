#include "metrics.h"
#include <numeric>   //std::accumulate
#include <limits> 
#include <iomanip>   // for formatting


void Metrics::compute(const std::vector<PCB>& jobs)
{
   // TODO HERE
}


void Metrics::export_csv(std::ostream& os, const char* scheduler_name)
{
   // .csv columns
   os << scheduler_name << ','
      << avg_wait       << ','
      << avg_turnaround << ','
      << avg_response   << ','
      << throughput     << ','
      << cpu_util       << '\n';
}
