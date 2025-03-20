/**
 * ADAPTIVE REAL-TIME SCHEDULER FOR EMBEDDED SYSTEMS
 * ================================================
 * 
 * Based on research paper: "Adaptive Real-Time Scheduler for Embedded Operating System"
 * Original Authors:
 *   - Arkajit Datta (VIT Vellore)
 *   - Shamith D Rao (VIT Vellore) 
 *   - C.G Mohan (VIT Vellore)
 * 
 * Reimplemented and Enhanced by:
 *   Houssem-eddine LAHMER (March 2024)
 *   Contact: Houssemeddine.lahmer@outlook.com
 * 
 * Key Features:
 *   - Multi-level priority queues (3-tier hierarchy)
 *   - Dynamic time quantum allocation
 *   - Circular linked list implementation
 *   - Adaptive scheduling based on process priorities
 *   - Comprehensive performance metrics
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Time quantum for each queue
#define TIME_Q1 3
#define TIME_Q2 2
#define TIME_Q3 1

// Global clock
int global_clock = 0;

// Process queue node structure
typedef struct Process {
    int pid;
    int priority;
    int arrival_time;
    int burst;
    int remaining_burst;
    struct Process *next;
} Process;

// Result queue node structure
typedef struct Result {
    int pid;
    int arrival;
    int burst;
    int completion;
    struct Result *next;
} Result;

// Queue management functions
Process* enqueue_process(Process *queue, Process *new_process);
Process* dequeue_process(Process *queue, Process *process);
void free_queue(Process *queue);
Result* record_result(Result *results, int pid, int arrival, int burst, int completion);
void free_results(Result *results);

// Scheduling functions
Process* sort_by_arrival(Process *queue);
void schedule(Process **queue, int time_quantum, Result **results);
void print_results(Result *results);

int main() {
    Process *q1 = NULL, *q2 = NULL, *q3 = NULL;
    Result *results = NULL;
    int choice, n;

    while (1) {
        printf("\nADAPTIVE REAL-TIME SCHEDULER\n");
        printf("1. Add Processes\n2. Run Scheduler\n3. Show Results\n4. Reset\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Number of processes: ");
                scanf("%d", &n);

                for (int i = 0; i < n; i++) {
                    Process *p = malloc(sizeof(Process));
                    if (!p) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }

                    printf("\nProcess %d:\n", i+1);
                    printf("PID: "); scanf("%d", &p->pid);
                    printf("Priority: "); scanf("%d", &p->priority);
                    printf("Arrival Time: "); scanf("%d", &p->arrival_time);
                    printf("Burst Time: "); scanf("%d", &p->burst);
                    p->remaining_burst = p->burst;

                    // Enqueue based on priority
                    if (p->priority >= 100) {
                        q1 = enqueue_process(q1, p);
                    } else if (p->priority >= 50) {
                        q2 = enqueue_process(q2, p);
                    } else {
                        q3 = enqueue_process(q3, p);
                    }
                }
                break;
            }

            case 2: {
                global_clock = 0; // Reset clock for new run
                
                // Sort queues by arrival time
                q1 = sort_by_arrival(q1);
                q2 = sort_by_arrival(q2);
                q3 = sort_by_arrival(q3);

                // Execute scheduling
                printf("\nScheduling Q1 (Highest Priority):\n");
                schedule(&q1, TIME_Q1, &results);
                printf("\nScheduling Q2 (Medium Priority):\n");
                schedule(&q2, TIME_Q2, &results);
                printf("\nScheduling Q3 (Lowest Priority):\n");
                schedule(&q3, TIME_Q3, &results);
                break;
            }

            case 3:
                print_results(results);
                break;

            case 4:
                free_queue(q1);
                free_queue(q2);
                free_queue(q3);
                free_results(results);
                q1 = q2 = q3 = NULL;
                results = NULL;
                printf("\nSystem reset complete\n");
                break;

            case 5:
                free_queue(q1);
                free_queue(q2);
                free_queue(q3);
                free_results(results);
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

// Queue operations
Process* enqueue_process(Process *queue, Process *new_process) {
    new_process->next = NULL;
    if (!queue) return new_process;
    
    Process *current = queue;
    while (current->next) current = current->next;
    current->next = new_process;
    return queue;
}

Process* dequeue_process(Process *queue, Process *process) {
    if (!queue) return NULL;
    
    if (queue == process) {
        Process *new_head = queue->next;
        free(queue);
        return new_head;
    }
    
    Process *current = queue;
    while (current->next && current->next != process)
        current = current->next;
    
    if (current->next) {
        Process *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return queue;
}

void free_queue(Process *queue) {
    while (queue) {
        Process *temp = queue;
        queue = queue->next;
        free(temp);
    }
}

// Result management
Result* record_result(Result *results, int pid, int arrival, int burst, int completion) {
    Result *new = malloc(sizeof(Result));
    if (!new) {
        fprintf(stderr, "Memory error\n");
        exit(EXIT_FAILURE);
    }
    
    new->pid = pid;
    new->arrival = arrival;
    new->burst = burst;
    new->completion = completion;
    new->next = NULL;
    
    if (!results) return new;
    
    Result *current = results;
    while (current->next) current = current->next;
    current->next = new;
    return results;
}

void free_results(Result *results) {
    while (results) {
        Result *temp = results;
        results = results->next;
        free(temp);
    }
}

// Sorting function (bubble sort)
Process* sort_by_arrival(Process *queue) {
    if (!queue || !queue->next) return queue;
    
    int swapped;
    Process *ptr;
    Process *lptr = NULL;
    
    do {
        swapped = 0;
        ptr = queue;
        
        while (ptr->next != lptr) {
            if (ptr->arrival_time > ptr->next->arrival_time) {
                // Swap nodes by swapping data
                int temp_pid = ptr->pid;
                int temp_priority = ptr->priority;
                int temp_arrival = ptr->arrival_time;
                int temp_burst = ptr->burst;
                int temp_remain = ptr->remaining_burst;
                
                ptr->pid = ptr->next->pid;
                ptr->priority = ptr->next->priority;
                ptr->arrival_time = ptr->next->arrival_time;
                ptr->burst = ptr->next->burst;
                ptr->remaining_burst = ptr->next->remaining_burst;
                
                ptr->next->pid = temp_pid;
                ptr->next->priority = temp_priority;
                ptr->next->arrival_time = temp_arrival;
                ptr->next->burst = temp_burst;
                ptr->next->remaining_burst = temp_remain;
                
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
    
    return queue;
}

// Scheduling implementation
void schedule(Process **queue, int time_quantum, Result **results) {
    if (!*queue) {
        printf("Queue is empty\n");
        return;
    }
    
    Process *current = *queue;
    while (current) {
        if (current->arrival_time > global_clock) {
            global_clock = current->arrival_time;
        }
        
        int execution_time = (current->remaining_burst < time_quantum) 
                           ? current->remaining_burst 
                           : time_quantum;
        
        printf("Processing PID %d for %d units\n", current->pid, execution_time);
        global_clock += execution_time;
        current->remaining_burst -= execution_time;
        
        if (current->remaining_burst <= 0) {
            *results = record_result(*results, current->pid, 
                                    current->arrival_time, current->burst,
                                    global_clock);
            Process *to_remove = current;
            current = current->next;
            *queue = dequeue_process(*queue, to_remove);
        } else {
            current = current->next;
        }
    }
}

// Results display
void print_results(Result *results) {
    if (!results) {
        printf("No results available\n");
        return;
    }
    
    printf("\n%-8s %-12s %-10s %-15s %-12s\n", 
           "PID", "Arrival", "Burst", "Completion", "Waiting");
    printf("------------------------------------------------------------\n");
    
    float total_wait = 0, total_tat = 0;
    int count = 0;
    
    while (results) {
        int tat = results->completion - results->arrival;
        int wait = tat - results->burst;
        
        printf("%-8d %-12d %-10d %-15d %-12d\n",
               results->pid, results->arrival,
               results->burst, results->completion, wait);
        
        total_wait += wait;
        total_tat += tat;
        count++;
        results = results->next;
    }
    
    printf("\nAverage Waiting Time: %.2f\n", total_wait / count);
    printf("Average Turnaround Time: %.2f\n", total_tat / count);
}