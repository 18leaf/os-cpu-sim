#include "../include/scheduler.h"
#include <vector>
#include <deque>
#include <cstdint>

// MULTI‑LEVEL FEEDBACK QUEUE with simple aging
struct MLFQ_Scheduler : Scheduler
{
   static constexpr uint64_t AGING_THRESHOLD = 20; //100;  // ticks to promote
   static constexpr uint64_t BOOST_INTERVAL  = 80;  // ticks between globabl boosts

   // three priority levels
   std::vector<std::deque<PCB*>> queues_{ std::deque<PCB*>{},
                                          std::deque<PCB*>{},
                                          std::deque<PCB*>{} };

   // time slices per level
   const std::vector<uint64_t> quantums_{ 3, 23, 65 };

   // enqueue with timestamp
   void enqueue(PCB* p, uint64_t current_time)
   {
      size_t lvl = static_cast<size_t>(p->priority);
      if (lvl >= queues_.size())
      {
         lvl = queues_.size() - 1;
         p->priority = static_cast<int>(lvl);
      }
      queues_[lvl].push_back(p);
      p->last_enq_t = current_time;
   }

   // default... unused for mlfq
   void add_to_ready(PCB* p) override
   {
      queues_[0].push_back(p);
   }

   PCB* select_next(uint64_t current_time) override
   {
      //periodice global boost
      static uint64_t last_boost = 0;
      if (current_time - last_boost >= BOOST_INTERVAL)
      {
         for (size_t lvl = 1; lvl < queues_.size(); ++lvl)
         {
            for (PCB* p : queues_[lvl])
            {
               p->priority   = 0;
               queues_[0].push_back(p);
               p->last_enq_t = current_time;
            }
            queues_[lvl].clear();
         }
         last_boost = current_time;
      }


      // promote any processed that have aged
      for (size_t lvl = 1; lvl < queues_.size(); ++lvl)
      {
         auto &q = queues_[lvl];
         for (auto it = q.begin(); it != q.end(); )
         {
            PCB* p = *it;
            if (current_time - p->last_enq_t >= AGING_THRESHOLD)
            {
               // promote to next higher queue
               p->priority = static_cast<int>(lvl - 1);
               queues_[lvl - 1].push_back(p);
               p->last_enq_t = current_time;
               it = q.erase(it);
            }
            else
            {
               ++it;
            }
         }
      }

      // select from highest priority queue that isnt empty
      for (size_t lvl = 0; lvl < queues_.size(); ++lvl)
      {
         auto &q = queues_[lvl];
         if (!q.empty())
         {
            PCB* p = q.front();
            q.pop_front();
            p->priority = static_cast<int>(lvl);
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
      size_t lvl = static_cast<size_t>(p->priority);
      if (lvl >= quantums_.size())
         lvl = quantums_.size() - 1;
      uint64_t q = quantums_[lvl];
      return (p->rem_t < q ? p->rem_t : q);
   }
};

