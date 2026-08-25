#include <stdio.h>

#define MAX 20

typedef struct
{
    int pid;
    int at;       // Arrival Time
    int bt;       // Burst Time
    int priority;
    int ct;       // Completion Time
    int tat;      // Turn Around Time
    int wt;       // Waiting Time
    int remaining;
} Process;


/* ---------- FCFS ---------- */

void fcfs(Process p[], int n)
{
    int time = 0;

    printf("\n========== FCFS ==========\n");

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }
}


/* ---------- SJF ---------- */

void sjf(Process p[], int n)
{
    int completed = 0;
    int time = 0;
    int done[MAX] = {0};

    printf("\n========== SJF ==========\n");

    while (completed < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].at <= time)
            {
                if (shortest == -1 ||
                    p[i].bt < p[shortest].bt)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        time += p[shortest].bt;

        p[shortest].ct = time;
        p[shortest].tat = p[shortest].ct - p[shortest].at;
        p[shortest].wt = p[shortest].tat - p[shortest].bt;

        done[shortest] = 1;
        completed++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }
}


/* ---------- Priority Scheduling ---------- */

void priorityScheduling(Process p[], int n)
{
    int completed = 0;
    int time = 0;
    int done[MAX] = {0};

    printf("\n========== PRIORITY ==========\n");

    while (completed < n)
    {
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].at <= time)
            {
                if (selected == -1 ||
                    p[i].priority < p[selected].priority)
                {
                    selected = i;
                }
            }
        }

        if (selected == -1)
        {
            time++;
            continue;
        }

        time += p[selected].bt;

        p[selected].ct = time;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;

        done[selected] = 1;
        completed++;
    }

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }
}


/* ---------- Round Robin ---------- */

void roundRobin(Process p[], int n, int quantum)
{
    int time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].bt;

    printf("\n========== ROUND ROBIN ==========\n");
    printf("Time Quantum = %d\n", quantum);

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining > 0 && p[i].at <= time)
            {
                executed = 1;

                if (p[i].remaining > quantum)
                {
                    time += quantum;
                    p[i].remaining -= quantum;
                }
                else
                {
                    time += p[i].remaining;
                    p[i].remaining = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;
                }
            }
        }

        if (!executed)
            time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }
}


/* ---------- Main ---------- */

int main()
{
    Process original[MAX];

    int n;
    int quantum;

    printf("CPU Scheduling Algorithms\n");

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        original[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &original[i].at);

        printf("Burst Time: ");
        scanf("%d", &original[i].bt);

        printf("Priority (smaller number = higher priority): ");
        scanf("%d", &original[i].priority);
    }

    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);


    /* Copies for each algorithm */

    Process fcfsData[MAX];
    Process sjfData[MAX];
    Process priorityData[MAX];
    Process rrData[MAX];

    for (int i = 0; i < n; i++)
    {
        fcfsData[i] = original[i];
        sjfData[i] = original[i];
        priorityData[i] = original[i];
        rrData[i] = original[i];
    }


    /* Run algorithms */

    fcfs(fcfsData, n);

    sjf(sjfData, n);

    priorityScheduling(priorityData, n);

    roundRobin(rrData, n, quantum);


    return 0;
}
