#include "scheduler.h"
#include <vector>
#include <algorithm>


struct SRTF_Scheduler : Scheduler {
   std::vector<PCB*> q;

   void add_to_ready(PCB* p) override
   {
      q.push_back(p);
   }

   PCB* select_next(uint64_t /*current_time*/) override
   {
      if (q.empty())
      {
         return nullptr;
      }

      // find process with smallest remaining time
      auto it = std::min_element(
         q.begin(), q.end(),
         [](PCB* a, PCB* b)
         {
            return a->rem_t < b->rem_t;
         });

      PCB* p = *it;
      q.erase(it);
      return p;   
   }

   const char* name() override
   {
      return "SRTF";
   }
};
