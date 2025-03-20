# Adaptive Real-Time Scheduler for Embedded Systems


A reimplementation of the adaptive real-time scheduler described in the research paper *"Adaptive Real-Time Scheduler for Embedded Operating System"* (2nd Indian International Conference on Industrial Engineering and Operations Management, 2022). Enhanced with modular code structure, dynamic process management, and comprehensive performance metrics.

---

## 📜 Project Overview
This scheduler combines **multi-level priority queues** with **round-robin scheduling** to optimize CPU utilization and energy efficiency in embedded systems. It dynamically adjusts task execution based on process priorities and incorporates three-tier queue management.

### System Architecture
![Multilevel Feedback Queue Demonstration](images/Multilevel%20Feedback%20Queue%20demonstration.png)  
*Figure 1: Multilevel Feedback Queue Structure (Priority-based tiers with dynamic time quanta)*

![Adaptive Scheduler Workflow](images/Adaptive%20scheduler%20flow%20diagram.png)  
*Figure 2: Adaptive Scheduling Logic with Decision Module*

**Key Features**:
- **3-tier priority queues** (High/Medium/Low with ranges 100-150, 50-100, 0-50)
- **Adaptive time quanta** (3/2/1 units per queue)
- **Sleep function integration** for low-priority tasks (energy optimization)
- **Circular linked list** implementation for efficient process management
- **Interactive CLI** for process input and scheduling
- **Performance metrics**: Average waiting time, turnaround time, and completion tracking

---

## 📥 Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/adaptive-real-time-scheduler.git
   cd adaptive-real-time-scheduler
   ```
2. **Compile the code** (requires GCC):
   ```bash
   gcc adaptive_scheduler.c -o scheduler
   ```

---

## 🚀 Usage
Run the executable and follow the interactive menu:
```bash
./scheduler
```

**Menu Options**:
1. **Add Processes**: Input PID, priority, arrival time, and burst time.
2. **Run Scheduler**: Execute processes across priority queues (Q1 > Q2 > Q3).
3. **Show Results**: Display completion times, waiting times, and averages.
4. **Reset**: Clear all queues and results.
5. **Exit**: Terminate the program.

**Example Input** (from the research paper):
```
Process 1: PID=101, Priority=110, Arrival=0, Burst=10
Process 2: PID=102, Priority=120, Arrival=1, Burst=15
Process 3: PID=103, Priority=80, Arrival=2, Burst=20
Process 4: PID=104, Priority=71, Arrival=3, Burst=10
Process 5: PID=105, Priority=10, Arrival=4, Burst=25
Process 6: PID=106, Priority=15, Arrival=5, Burst=16
```

---

## 📊 Results
The scheduler outputs:
- **Completion Time**: When each process finishes.
- **Waiting Time**: Total time spent waiting in queues.
- **Turnaround Time**: Total time from arrival to completion.

Example Output (matches paper's Table 1):
```
PID     Arrival      Burst      Completion    Waiting
----------------------------------------------------
101     0            10         21            11
102     1            15         27            11
104     3            10         45            32
103     2            20         57            35
106     5            16         150           129
105     4            25         180           151

Average Waiting Time: 61.00
Average Turnaround Time: 80.00
```

---

## 📖 References
- **Original Paper**: [Adaptive Real-Time Scheduler for Embedded Operating System](https://ieomsociety.org/proceedings/2022india/191.pdf)
- **Research Code**: [Arkajit Datta's Original Implementation](https://github.com/Arkajit-Datta/ADAPTIVE-REAL-TIME-SCHEDULING-ALGORITHM)

---

## 🛠️ Limitations & Future Work
- **Sleep Function**: The energy-saving `sleep()` feature described in the paper is not yet implemented.
- **Preemption**: Current implementation assumes non-preemptive scheduling within queues.
- **Metrics**: CPU utilization calculation can be added for deeper analysis.
- **Dynamic Priorities**: Support for priority adjustments during runtime.


**Reimplemented by**: Houssem-eddine LAHMER  
**Contact**: [houssemeddine.lahmer@outlook.com](mailto:houssemeddine.lahmer@outlook.com)  

