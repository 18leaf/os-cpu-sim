#include "metrics.h"
#include <numeric>   //std::accumulate
#include <limits> 
#include <iomanip>   // for formatting


void Metrics::compute(const std::vector<PCB>& jobs)
{
   if (jobs.empty())
   {
      avg_wait       = 0.0;
      avg_turnaround = 0.0;
      avg_response   = 0.0;
      throughput     = 0.0;
      cpu_util       = 0.0;
      return;
   }

   // Determine overall spans
   uint64_t first_arrival = jobs.front().arr_t;
   uint64_t last_exit     = 0;
   uint64_t total_burst   = 0;

   for (const auto &p : jobs)
   {
      if (p.exit_t > last_exit)
      {
         last_exit = p.exit_t;
      }
      total_burst += p.burst_t;
   }

   // Aggregate per‐process metrics
   double sum_wt  = 0.0;
   double sum_tat = 0.0;
   double sum_rt  = 0.0;
   const double N = static_cast<double>(jobs.size());

   for (const auto &p : jobs)
   {
      uint64_t tat = p.exit_t - p.arr_t;
      uint64_t wt  = tat - p.burst_t;
      uint64_t rt  = (p.start_t == std::numeric_limits<uint64_t>::max())
                       ? 0
                       : (p.start_t - p.arr_t);

      sum_tat += static_cast<double>(tat);
      sum_wt  += static_cast<double>(wt);
      sum_rt  += static_cast<double>(rt);
   }

   // Compute averages
   avg_turnaround = sum_tat / N;
   avg_wait       = sum_wt  / N;
   avg_response   = sum_rt  / N;

   // Compute throughput and CPU utilization
   double duration = static_cast<double>(last_exit - first_arrival);
   if (duration > 0.0)
   {
      throughput = N / duration;
      cpu_util   = static_cast<double>(total_burst) / duration;
   }
   else
   {
      throughput = 0.0;
      cpu_util   = 0.0;
   }
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
