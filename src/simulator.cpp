#include "../include/workload.h"
#include "../include/scheduler.h"
#include "../include/metrics.h"

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>


#include "scheduler_mlfq.cpp"    // for casting internal function time_slicE_for


void run_simulation(Scheduler& sched,
                    const std::vector<PCB>& jobs,
                    const std::string& out_csv_path)
{
   std::vector<PCB> procs = jobs;

   size_t next_idx = 0;
   size_t completed = 0;
   uint64_t current_time = 0;

   Metrics M;
   
   // generic metrics
   std::ofstream out(out_csv_path, std::ios::app);
   if (!out)
   {
      std::cerr << "Cannot open output csv\n";
      return;
   }

   // detaild metrics
   std::ofstream detail_out("results_detailed.csv", std::ios::app);
   if (!detail_out)
   {
      std::cerr << "Cannot open detailed CSV\n";
      return;
   }
   //header
    detail_out
      << "scheduler,id,arrival,burst,start,exit,waiting,turnaround,response\n";
   
   while (completed < procs.size())
   {
      // add newly arrived process
      while (next_idx < procs.size() &&
             procs[next_idx].arr_t <= current_time)
      {
         // mlfq scheduling
         if (auto *m = dynamic_cast<MLFQ_Scheduler*>(&sched))
         {
            m->enqueue(&procs[next_idx], current_time);
         }
         else
         {
            sched.add_to_ready(&procs[next_idx]);
         }
         ++next_idx;
      }

      // slecte next
      PCB *p = sched.select_next(current_time);
      if (p == nullptr)
      {
         // none ready, skip
         if (next_idx < procs.size())
         {
            current_time = procs[next_idx].arr_t;
         }
         continue;
      }

      // record first response time.. init to maxe
      if (p->start_t == std::numeric_limits<uint64_t>::max())
      {
         p->start_t = current_time;
      }

      // determine run time
      uint64_t run_length = p->rem_t;
      if (auto *m = dynamic_cast<MLFQ_Scheduler*>(&sched))
      {
         // use mlfq specific time slic
         run_length = m->time_slice_for(p);
      }

      // simulate run process
      current_time += run_length;
      p->rem_t -= run_length;

      // check for completed
      if (p->rem_t == 0)
      {
         p->exit_t = current_time;
         ++completed;
      }
      else
      {
         if (auto *m = dynamic_cast<MLFQ_Scheduler*>(&sched))
         {
            m->enqueue(p, current_time);
         }
         else
         {
            sched.add_to_ready(p);
         }
      } 
   }

   // 5. Dump per-process details
   for (const auto &p : procs)
   {
      uint64_t tat = p.exit_t - p.arr_t;
      uint64_t wt  = tat - p.burst_t;
      uint64_t rt  = (p.start_t == std::numeric_limits<uint64_t>::max())
                        ? 0
                        : (p.start_t - p.arr_t);

      detail_out
         << sched.name()   << ','
         << p.id           << ','
         << p.arr_t        << ','
         << p.burst_t      << ','
         << p.start_t      << ','
         << p.exit_t       << ','
         << wt             << ','
         << tat            << ','
         << rt             << '\n';
   }
   detail_out.close();

   // compute and write to csv
   M.compute(procs);
   M.export_csv(out, sched.name());

}
