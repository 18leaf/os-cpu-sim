#ifndef PCB_H
#define PCB_H

#include <cstdint>         // for uint64_t


struct PCB {
   int         id;         // unique ID for the process
   uint64_t    arr_t;      // arrival time
   uint64_t    burst_t;    // burst time
   uint64_t    rem_t;      // remaining time
   int         priority;   // lower num == higher priority
   uint64_t    start_t;    // tick when task was first scheduled
   uint64_t    exit_t;     // tick when finished
};



#endif // PCB_H
