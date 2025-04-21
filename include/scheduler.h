#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "pcb.h"
#include <cstdint>

// scheduler interface

struct Scheduler {
   virtual ~Scheduler() = default;

   virtual void add_to_ready(PCB *p) = 0;

   virtual PCB* select_next(uint64_t current_time) = 0;
   
   virtual const char* name() = 0;
};

#endif // SCHEDULER_H
