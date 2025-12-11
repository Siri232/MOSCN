#include <stdio.h>
#include <stdlib.h>

int min(int a,int b){ return (a<b)?a:b; }

int main(){
    int n = 4;                 // number of processes 
    int tq = 4;                // time quantum

    int pid[] = {1,2,3,4};
    int at[]  = {3,0,4,1};     // arrival times corresponding to pid order
    int bt[]  = {9,5,2,7};     // burst times
    int i;
    int rem[n];
    for(i=0;i<n;i++) rem[i] = bt[i];

    int t = 0;                 // current time
    int completed = 0;
    int last_exec = -1;

    int ct[n]; // completion times
    for(i=0;i<n;i++) ct[i] = -1;

    int qsize = 1000;
    int queue[qsize];
    int front = 0, rear = 0;

    
    for(i=0;i<n;i++){
        if(at[i] == 0){
            queue[rear++] = i;
            if(rear==qsize) rear=0;
        }
    }

    // If no process at t=0, move time to earliest arrival and enqueue those at that time
    if(front==rear){
        int earliest = at[0];
        for(i=1;i<n;i++) if(at[i] < earliest) earliest = at[i];
        t = earliest;
        for(i=0;i<n;i++) if(at[i]==t){
            queue[rear++] = i; if(rear==qsize) rear=0;
        }
    }

    #define MAXG 200
    int g_pid[MAXG], g_start[MAXG], g_end[MAXG], gcount=0;

    while(completed < n){
        if(front==rear){
            
            int next = 1e9;
            for(i=0;i<n;i++) if(rem[i]>0 && at[i] > t) next = min(next, at[i]);
            t = next;
            for(i=0;i<n;i++) if(at[i]==t){
                queue[rear++] = i; if(rear==qsize) rear=0;
            }
            continue;
        }

        int idx = queue[front++];
        if(front==qsize) front=0;

        // If process hasn't arrived yet, wait.
        if(at[idx] > t){
            // push back and advance time to its arrival (to avoid busy wait)
            queue[rear++] = idx; if(rear==qsize) rear=0;
            int next = at[idx];
            t = next;
            for(i=0;i<n;i++) if(at[i]==t){
                // enqueue newly arrived at this exact time (except idx which is already enqueued)
                if(i!=idx){
                    queue[rear++] = i; if(rear==qsize) rear=0;
                }
            }
            continue;
        }

        int exec = min(tq, rem[idx]);
        // recording Gantt chart entry (merge if same pid as last and contiguous)
        if(gcount>0 && g_pid[gcount-1] == pid[idx] && g_end[gcount-1]==t){
            g_end[gcount-1] += exec;
        } else {
            g_pid[gcount] = pid[idx];
            g_start[gcount] = t;
            g_end[gcount] = t + exec;
            gcount++;
        }

        t += exec;
        rem[idx] -= exec;

        // Enqueuing any processes that arrive exactly at new time t (after this quantum)
        for(i=0;i<n;i++){
            if(at[i] > t-exec && at[i] <= t && rem[i] > 0){
                
                if(i != idx){
                    queue[rear++] = i; if(rear==qsize) rear=0;
                }
            }
        }

        if(rem[idx] == 0){
            ct[idx] = t;
            completed++;
        } else {
            // not finished: enqueue to back
            queue[rear++] = idx; if(rear==qsize) rear=0;
        }
    }

    // Prints Gantt chart
    printf("\nGantt Chart:\n");
    for(i=0;i<gcount;i++){
        printf("| %2d - %2d ", g_start[i], g_end[i]);
    }
    printf("|\n");
    for(i=0;i<gcount;i++){
        printf("|  P%d   ", g_pid[i]);
    }
    printf("|\n\n");

    // Prints table
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    double sumtat=0, sumwt=0;
    for(i=0;i<n;i++){
        int tat = ct[i] - at[i];
        int wt  = tat - bt[i];
        sumtat += tat; sumwt += wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat, wt);
    }
    printf("\nAvg TAT = %.2f\nAvg WT  = %.2f\n", sumtat/n, sumwt/n);

    return 0;
}

