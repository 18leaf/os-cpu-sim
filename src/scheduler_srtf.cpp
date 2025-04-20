#include "scheduler.h"
#include <vector>
#include <algorithm>


struct SRTF_Scheduler : Scheduler {
   std::vector<PCB*> q;

   void add_to_ready(PCB* p) override
   {
      // TODO insert p into q
   }

   PCB* select_next(uint64_t /*current_time*/) override
   {
      // TODO find PCB with smallest rem_t remove and return it
      return nullptr;
   }

   const char* name() const override
   {
      return "SRTF";
   }

};
