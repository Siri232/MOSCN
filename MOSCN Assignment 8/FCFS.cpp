#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
};

bool sortByArrival(const Process &a, const Process &b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter ProcessID ArrivalTime BurstTime:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), sortByArrival);

    int currentTime = 0;
    double totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {

        // CPU idle handling
        if (currentTime < p[i].at)
            currentTime = p[i].at;

        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        currentTime = p[i].ct;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Display table
    cout << "\n---------------------------------------------------------\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    cout << "---------------------------------------------------------\n";

    cout << "Total TAT = " << totalTAT << endl;
    cout << "Total WT  = " << totalWT << endl;

    cout << fixed << setprecision(2);
    cout << "Average TAT = " << totalTAT / n << endl;
    cout << "Average WT  = " << totalWT / n << endl;

    return 0;
}

