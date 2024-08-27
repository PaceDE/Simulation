#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sum / n;
}

double autocorrelation(double data[], int n, int lag, double mean, double var) {
    double sum = 0.0;
    for (int i = 0; i < n - lag; i++) {
        sum += (data[i] - mean) * (data[i + lag] - mean);
    }
    return sum / ((n - lag) * var);
}

double calculate_Sim(double data[], int n, int M, int i, int m) {
    double meanValue = mean(data, n);
    double varValue = variance(data, n, meanValue);
    double Sim = 0.0;
    double R1, R2;
    int k;
    
    for (k = 0; k <= M; k++) {
        R1 = autocorrelation(data, n, i + k * m, meanValue, varValue);
        R2 = autocorrelation(data, n, i + (k + 1) * m, meanValue, varValue);
        Sim += R1 * R2;
    }
    
    Sim /= (M + 1);
    Sim -= 0.25;
    
    return Sim;
}

double calculate_sigma_Sim(int M) {
    double sigma_Sim = sqrt((13 * M + 7.0) / (12 * (M + 1.0)));
    return sigma_Sim;
}

int main() {
    int n = 50;
    int i = 2;
    int M = 8;
    int m = 5;

    double data[50] = {
        0.19, 0.16, 0.82, 0.63, 0.04, 0.16, 0.3, 0.22, 0.88, 0.48, 0.23, 0.56, 0.44,
        0.05, 0.81, 0.38, 0.59, 0.37, 0.75, 0.43, 0.92, 0.45, 0.57, 0.99, 0.2, 0.14, 0.64,
        0.5, 0.73, 0.15, 0.02, 0.49, 0.86, 0.24, 0.09, 0.74, 0.41, 0.09, 0.86, 0.42, 0.16,
        0.23, 0.77, 0.08, 0.69, 0.46, 0.39, 0.18, 0.21, 0.98
    };

    printf("Data:\n");
    for (int j = 0; j < n; j++) {
        printf("%.2f ", data[j]);
        if ((j + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    double Sim = calculate_Sim(data, n, M, i, m);
    double sigma_Sim = calculate_sigma_Sim(M);
    double Z0 = Sim / sigma_Sim;

    printf("Sim: %f\n", Sim);
    printf("Sigma_Sim: %f\n", sigma_Sim);
    printf("Z0: %f\n", Z0);

    double critical_value = 1.96;
    if (fabs(Z0) <= critical_value) {
        printf("Since, calculated value Z0 is less than the tabulated value Z. The numbers are independent.\n");
    } else {
        printf("Since, calculated value Z0 is more than the tabulated value Z.The numbers are not independent.\n");
    }

    return 0;
}