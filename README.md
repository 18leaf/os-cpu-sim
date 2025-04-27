# OS-CPU Scheduling Simulator

A modular C++ simulator for evaluating classic CPU scheduling policies on synthetic workloads. It implements:

- **FCFS** (First-Come, First-Serve)  
- **SRTF** (Shortest Remaining Time First)  
- **MLFQ** (Multi-Level Feedback Queue) with aging and global boosts  

Workloads are defined in CSV, and the simulator produces both summary and per-job CSV outputs. A companion Python script generates visualizations (histogram, scatter plot, bar chart) to compare algorithm trade-offs.

---

## Features

- Clean Scheduler interface supporting preemptive and non-preemptive policies  
- Three scheduling strategies with customizable parameters  
- CSV-based I/O for easy integration with other tools  
- Automatic metric computation:  
  - Average waiting time  
  - Average turnaround time  
  - Average response time  
  - CPU utilization  
  - Throughput  
- Python/Plotly visualization script for quick graphical analysis

---

## Requirements

- **C++17** compiler (e.g. `g++`)  
- **Make** (for the provided `Makefile`)  
- **Python 3** with the following packages:  
  ```bash
  pip install pandas plotly
  ```

---

## Repository Layout

```
.
├── include/            # Header files (PCB, Scheduler interface, workload, simulator, metrics)
├── src/                # C++ implementations and main program
├── analyze/            # Python visualization (analyze.py) and run script
├── workloads/          # Example CSV workload traces
├── results/            # Generated output CSVs
├── Makefile            # Build instructions
├── runvis.sh           # Helper script for full run + visualization
└── README.md           # This file
```

---

## Building

```bash
make
```

Produces the `cpu_sim` executable.

---

## Running Simulations

```bash
./cpu_sim workloads/<your_workload.csv>
```

- **Input:** `id, arrival, burst[, priority]`  
- **Outputs:**  
  - `results/results.csv` – aggregated metrics per scheduler  
  - `results/results_detailed.csv` – per-job timing details  

---

## Visualization

```bash
cd analyze
python analyze.py ../results/results_detailed.csv
```

Opens plots in individual browser tabs.

Alternatively:

```bash
./runvis.sh workloads/<your_workload.csv>
```

---


## References

- GeeksforGeeks: [MLFQ Scheduling](https://www.geeksforgeeks.org/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/)  
- Mistry, A.: [Multi-Level Feedback Queue Scheduling](https://medium.com/@akshat.mistry/multi-level-feedback-queue-mlfq-scheduling-142a6c85e2ad)  
- Arpaci-Dusseau, R. H. & Arpaci-Dusseau, A. C.: [CPU Scheduling (OSTEP)](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf)   
