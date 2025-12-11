#include <stdio.h>

int main() {
    int n = 5, tq = 3;
    int bt[5] = {7, 5, 3, 9, 4};
    int at[5] = {4, 0, 6, 2, 1};
    int rem_bt[5], ct[5], tat[5], wt[5];
    int time = 0, done = 0;

    for(int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    while(done < n) {
        for(int i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    done++;
                }
            }
        }
    }

    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nProcess\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i+1, ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f", avg_tat);
    printf("\nAverage WT = %.2f\n", avg_wt);

    return 0;
}

