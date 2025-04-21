/*
   src/workload.cpp
   open file and reads list of processes
   creates a PCB struct for each record
   return a vectory<PCB> for simulating
*/
#include "../include/workload.h"
#include "../include/pcb.h"
#include <fstream>      // std::ifstream
#include <sstream>      // std::stringstream
#include <iostream>     // std::cerr
#include <algorithm>    // std::sort
#include <limits>       // std::numeric_limits
#include <cstdint>


std::vector<PCB> load_workload(const std::string& path)
{
   // open .csv file
   // each line
      // split by comma {id,arr_t,burst_t,(optional priority default = 0)}
      // create PCB object + populate with above
      // apply dynamic fields as well
      // append PCB to vector
   // return vector<PCB>
   
   // define vector pcb to return
   std::vector<PCB> jobs;

   // open file + handle error
   std::ifstream infile(path);
   if (!infile)
   {
      std::cerr << "Error: opening workload file: '" << path << "'\n";
      return jobs;
   }
   
   // read each line, create PCB object
   std::string line;
   while (std::getline(infile, line))
   {
      if (line.empty() || line[0] == '#') continue;   // emtpy line or comment, skip
      
      // init string stream and PCB object
      std::stringstream ss(line);
      PCB p;

      // parse mandatory fields
      // token seperated by , in order = {id,arrival,burst,[optional priority]}
      std::string token;
      try
      {
         std::getline(ss, token, ',');    // split save first to token
         p.id = std::stoi(token);         // set p.id to valueo f first token
         std::getline(ss, token, ',');
         p.arr_t = std::stoull(token);    // get arrival tick (uint64_t)
         std::getline(ss, token, ',');
         p.burst_t = std::stoull(token);  // burst tick (uint64_t)
      
         // optional priority field -> conditional set to value or 0
         if (std::getline(ss, token, ','))
         {
            p.priority = std::stoi(token);
         }
         else
         {
            p.priority = 0;   
         }

         p.rem_t = p.burst_t;
         p.start_t = std::numeric_limits<uint64_t>::max();  // start and exit ticks to max value for now (not complete)
         p.exit_t = std::numeric_limits<uint64_t>::max();
      
         // append to jobs
         jobs.push_back(p);
      }
      //catch any error with a line (malfunctioning)
      //go ot next line
      catch (...) { continue; }
   }
   // sort by arrival time
   std::sort(jobs.begin(), jobs.end(),
   [](const PCB &a, const PCB &b)
   {
      return a.arr_t < b.arr_t;
   }
   );

   return jobs;
};
