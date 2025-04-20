#include "../include/workload.h"
#include "../include/scheduler.h"
#include "../include/scheduler_fcfs.cpp"
#include "../include/scheduler_srtf.cpp"
#include "../include/scheduler_mlfq.cpp"
#include "../include/simulator.cpp"

int main(int argc, char** argv)
{
   auto jobs = load_workload("workloads/test_fcfs.csv");

   FCFS_Scheduler fcfs;
   run_simulator(fcfs, jobs, "results.csv");

   //SRTF_Scheduler srtf;
   //run_simulator(srtf, jobs, "results.csv");

   //MLFQ_Scheduler mlfq;
   //run_simulator(mlfq, jobs. "results.csv");

   return 0;
}
