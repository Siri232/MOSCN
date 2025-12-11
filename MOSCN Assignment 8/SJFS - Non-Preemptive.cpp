#include <iostream>
#include <string>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
    bool completed;
};

int main() {

    int n = 4;  // Fixed number of processes

    Process p[4];

    // Assign process details manually to avoid unsupported features
    p[0].pid = "P1"; p[0].at = 0; p[0].bt = 8;
    p[1].pid = "P2"; p[1].at = 1; p[1].bt = 4;
    p[2].pid = "P3"; p[2].at = 2; p[2].bt = 9;
    p[3].pid = "P4"; p[3].at = 3; p[3].bt = 5;

    for (int i = 0; i < n; i++) {
        p[i].completed = false;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    int completed = 0;
    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    cout << "\n--- NON-PREEMPTIVE SJF SCHEDULING ---\n";

    // SJF Logic
    while (completed < n) {
        int idx = -1;
        int minBT = 999999;

        // Find shortest job that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // Execute the selected process
        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = true;

        totalTAT += p[idx].tat;
        totalWT += p[idx].wt;
        completed++;
    }

    // Output table
    cout << "\n---------------------------------------------------\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }
    cout << "---------------------------------------------------\n";

    cout << "Average TAT = " << totalTAT / n << endl;
    cout << "Average WT  = " << totalWT / n << endl;

    // Gantt Chart
    cout << "\n--- GANTT CHART ---\n";

    // Determine execution order manually using SJF logic results
    int start = 0;
    for (int step = 0; step < n; step++) {
        // Find next by completion order (increasing CT)
        int next = -1;
        int minCT = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].ct < minCT) {
                minCT = p[i].ct;
                next = i;
            }
        }

        // Mark so not picked again
        p[next].ct = 999999;

        // Print Gantt chart row
        cout << p[next].pid << " | ";
    }

    cout << "\n";

    return 0;
}
