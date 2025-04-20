CXX		= g++
CXXFLAGS = -std=c++17 -O2 -Iinclude -Wall -Wextra -pedantic

SRC = \
	src/workload.cpp \
	src/scheduler_fcfs.cpp \
	src/scheduler_srtf.cpp \
	src/scheduler_mlfq.cpp \
	src/metrics.cpp \
	src/simulator.cpp \
	src/main.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = cpu_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

