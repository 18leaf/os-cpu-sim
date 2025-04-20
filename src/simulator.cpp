#include "../include/workload.h"
#include "../include/scheduler.h"
#include "../include/metrics.h"

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>

void run_simulation(Scheduler& sched,
                    const std::vector<PCB>& jobs,
                    const std::string& out_csv_path)
{
   std::vector<PCB> procs = jobs;

   size_t next_idx = 0;
   size_t completed = 0;
   uint64_t current_time = 0;

   Metrics M;

   std::ofstream out(out_csv_path, std::ios::app);
   if (!out)
   {
      std::cerr << "Cannot open output csv\n";
      return;
   }
   
   while (completed < procs.size())
   {
      // TODO 
   
   }

   M.compute(procs);
   M.export_csv(out, sched.name());

}
