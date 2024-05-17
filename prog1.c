#include <stdio.h>

void fcfs(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    printf("First Come, First Served [FCFS] Scheduling Algorithm\n");
    printf("------------------------------------------------------\n");
    printf("Process\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)turnaround_time[n - 1] / n);
}

void sjf(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0;
    int temp[n], pos, temp_burst;

    for (int i = 0; i < n; i++) {
        temp[i] = burst_time[i];
    }

    for (int i = 0; i < n; i++) {
        pos = i;
        for (int j = i + 1; j < n; j++) {
            if (temp[j] < temp[pos])
                pos = j;
        }
        temp_burst = temp[i];
        temp[i] = temp[pos];
        temp[pos] = temp_burst;

        temp_burst = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp_burst;
    }

    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    printf("Shortest Job First [SJF] Scheduling Algorithm\n");
    printf("----------------------------------------------\n");
    printf("Process\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)turnaround_time[n - 1] / n);
}

void priority_schedule(int processes[], int n, int burst_time[], int priority[]) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0;
    int temp[n], pos, temp_burst, temp_prior;

    for (int i = 0; i < n; i++) {
        temp[i] = priority[i];
    }

    for (int i = 0; i < n; i++) {
        pos = i;
        for (int j = i + 1; j < n; j++) {
            if (temp[j] < temp[pos])
                pos = j;
        }
        temp_burst = burst_time[i];
        burst_time[i] = burst_time[pos];
        burst_time[pos] = temp_burst;

        temp_burst = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp_burst;

        temp_prior = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp_prior;
    }

    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }

    printf("Priority Scheduling Algorithm\n");
    printf("-----------------------------\n");
    printf("Process\t Burst Time\t Priority\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)turnaround_time[n - 1] / n);
}

void round_robin(int processes[], int n, int burst_time[], int quantum) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0;
    int remaining_time[n];

    for (int i = 0; i < n; i++)
        remaining_time[i] = burst_time[i];

    int t = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > quantum) {
                    t += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    t = t + remaining_time[i];
                    waiting_time[i] = t - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_waiting_time += waiting_time[i];
    }

    printf("Round Robin Scheduling Algorithm\n");
    printf("--------------------------------\n");
    printf("Process\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n\n", (float)turnaround_time[n - 1] / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], process_priority[n];
    printf("Enter the burst time and priority for each process\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &process_priority[i]);
        processes[i] = i + 1;
    }

    int quantum;
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    fcfs(processes, n, burst_time);
    sjf(processes, n, burst_time);
    priority_schedule(processes, n, burst_time, process_priority);
    round_robin(processes, n, burst_time, quantum);

    return 0;
}

