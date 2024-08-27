#include <stdio.h>
#include <stdlib.h>

void calculate(int totalCustomers, double *arrivalTimes, double *serviceTimes) {
    double totalWaitingTime = 0.0;
    double totalServiceTime = 0.0;
    double totalBusyTime = 0.0;
    double totalTimeInSystem = 0.0;
    double currentTime = 0.0;

    for (int i = 0; i < totalCustomers; i++) {
        if (i == 0) {
            currentTime = arrivalTimes[i];
        } else {
            if (arrivalTimes[i] < currentTime) {
                totalWaitingTime += (currentTime - arrivalTimes[i]);
            } else {
                currentTime = arrivalTimes[i];
            }
        }

        currentTime += serviceTimes[i];
        totalServiceTime += serviceTimes[i];
        totalBusyTime += serviceTimes[i];
        totalTimeInSystem += (currentTime - arrivalTimes[i]);
    }

    double averageWaitingTime = totalWaitingTime / totalCustomers;
    double averageServiceTime = totalServiceTime / totalCustomers;
    double serverUtilization = totalBusyTime / currentTime;
    double averageQueueLength = totalWaitingTime / currentTime;

    // New calculations
    double averageTimeInSystem = totalTimeInSystem / totalCustomers;  // W
    double arrivalRate = (double)totalCustomers / currentTime;        // λ
    double averageNumberInSystem = arrivalRate * averageTimeInSystem; // L
    double averageNumberInQueue = arrivalRate * averageWaitingTime;   // Lq

    // Output results
    printf("Total Customers: %d\n", totalCustomers);
    printf("Average Waiting Time (Wq): %.2f\n", averageWaitingTime);
    printf("Average Service Time: %.2f\n", averageServiceTime);
    printf("Average Time Spent in System (W): %.2f\n", averageTimeInSystem);
    printf("Average Number of Customers in Queue (Lq): %.2f\n", averageNumberInQueue);
    printf("Average Number of Customers in System (L): %.2f\n", averageNumberInSystem);
    printf("Server Utilization: %.2f%%\n", serverUtilization * 100);
    printf("Average Queue Length: %.2f\n", averageQueueLength);
}

int main() {
    int totalCustomers;

    printf("Enter total number of customers: ");
    scanf("%d", &totalCustomers);
    double arrivalTimes[totalCustomers];
    double serviceTimes[totalCustomers];
    printf("Enter arrival times for each customer:\n");
    for (int i = 0; i < totalCustomers; i++) {
        printf("Arrival time for customer %d: ", i + 1);
        scanf("%lf", &arrivalTimes[i]);
    }
    printf("Enter service times for each customer:\n");
    for (int i = 0; i < totalCustomers; i++) {
        printf("Service time for customer %d: ", i + 1);
        scanf("%lf", &serviceTimes[i]);
    }
    calculate(totalCustomers, arrivalTimes, serviceTimes);
   return 0;
}