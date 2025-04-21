#include "../include/workload.h"
#include "../include/scheduler.h"
#include "scheduler_fcfs.cpp"
#include "scheduler_srtf.cpp"
#include "scheduler_mlfq.cpp"
#include "../include/simulator.h"


int main(int argc, char** argv)
{
   if (argc != 2)
   {
      printf("usage ./cpu_sim path/to/<file.csv>");
      return 0;
   }
   
   auto jobs = load_workload(argv[1]);
   

   FCFS_Scheduler fcfs;
   run_simulation(fcfs, jobs, "results.csv");

   SRTF_Scheduler srtf;
   run_simulation(srtf, jobs, "results.csv");

   MLFQ_Scheduler mlfq;
   run_simulation(mlfq, jobs, "results.csv");

   return 0;
}
