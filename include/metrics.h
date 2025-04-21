#ifndef METRICS_H
#define METRICS_H

#include "pcb.h"
#include <vector>
#include <ostream>

struct Metrics {
   double avg_wait;
   double avg_turnaround;
   double avg_response;
   double throughput;
   double cpu_util;

   // compute metrics for all jobs
   void compute(const std::vector<PCB>& jobs);

   // add line for metrics to csv
   void export_csv(std::ostream& os, const char* scheduler_name);
};

#endif // METRICS_H
