#include "scheduler.h"
#include <deque>


// FIRST COME FIRST SERVE
struct FCFS_Scheduler : Scheduler {
   std::dequeue<PCB*> q;

   void add_to_ready(PCB *p) override
   {
      q.push_back(p);
   }

   PCB* select_next(uint64_t /*current_time*/) override
   {
      if (q.empty())
      {
         return nullptr;
      }
      
      PCB *p = q.front();
      q.pop_front();
      return p;
   }

   const char* name() const override
   {
      return "FCFS"
   }
}
