#pragma once

#include <vector>
#include <string>
#include "workload.h"   // defines PCB
#include "scheduler.h"  // defines Scheduler

// run_simulation:
//   sched         – scheduler instance to drive
//   jobs          – list of PCBs (with arrival times, burst lengths, etc.)
//   out_csv_path  – path to append metrics CSV
void run_simulation(Scheduler& sched,
                    const std::vector<PCB>& jobs,
                    const std::string& out_csv_path);

