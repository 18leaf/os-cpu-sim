WORKLOAD=workloads/large_workload.csv

echo "Running simulation on $WORKLOAD ..."
./cpu_sim "$WORKLOAD"


echo "Simulation Complete. Launching analysis"
python analyze/analyze.py

echo "Complete"
