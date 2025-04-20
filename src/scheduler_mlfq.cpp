#include "scheduler.h"
#include <vector>
#include <deque>

// MULTI_LEVEL_FEEDBACK_QUEUE
struct MLFQ_Scheduler : Scheduler {
   // define multiple priority queuers

   void add_to_ready(PCB* p) override
   {
      // TODO: place p into highest‑priority queue
   }

   PCB* select_next(uint64_t current_time) override 
   {
   // TODO scan top queues top down enforce timeslice per level
      return nullptr;
   }

   const char* name() const override 
   {
      return "MLFQ";
   }
};
