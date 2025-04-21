#include "scheduler.h"
#include <vector>
#include <deque>

// MULTI_LEVEL_FEEDBACK_QUEUE
struct MLFQ_Scheduler : Scheduler {
   // 3 differnet queues
   std::vector<std::deque<PCB*>> queues_{ std::deque<PCB*>{},
                                          std::deque<PCB*>{},
                                          std::deque<PCB*>{}};
   
   // check which quantum each level uses
   const std::vector<uint64_t> quantums_{ 4, 8, 16 };

   void add_to_ready(PCB* p) override
   {
      queues_[0].push_back(p);
   }

   PCB* select_next(uint64_t current_time) override 
   {
      // find the first non‑empty queue
      for (size_t level = 0; level < queues_.size(); ++level)
      {
         auto &q = queues_[level];
         if (!q.empty())
         {
            PCB* p = q.front();
            q.pop_front();
            // record where to return after this slice:
            // embed level in p->priority as temp storage
            p->priority = static_cast<int>(level);
            return p;
         }
      }
      return nullptr;
   }

   const char* name() override 
   {
      return "MLFQ";
   }

   uint64_t time_slice_for(PCB* p) const
   {
      int level = p->priority;
      uint64_t q = quantums_[ level < static_cast<int>(quantums_.size()) ? level : quantums_.size() - 1 ];
      return (p->rem_t < q ? p->rem_t : q);
   }
};
