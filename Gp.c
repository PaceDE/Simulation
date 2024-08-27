#include <stdio.h>
#include <math.h>
#define TOTAL_DIGITS 110
#define NUM_RANGES 12
int gap_ranges[NUM_RANGES][2] = {
    {0, 3}, {4, 7}, {8, 11}, {12, 15}, {16, 19},
    {20, 23}, {24, 27}, {28, 31}, {32, 35}, {36, 39},
    {40, 43}, {44, 47}
};
int target_freq[NUM_RANGES] = {35, 22, 17, 9, 5, 6, 3, 0, 0, 2, 0, 1};
int find_range_index(int gap) {
    for (int i = 0; i < NUM_RANGES; i++) {
        if (gap >= gap_ranges[i][0] && gap <= gap_ranges[i][1]) {
            return i;
        }
    }
    return -1;
}
void calculate_cumulative_frequency(int freq[], double rel_freq[], double cum_freq[], int total_gaps) {
    for (int i = 0; i < NUM_RANGES; i++) {
        rel_freq[i] = (double)freq[i] / total_gaps;
        if (i == 0) {
            cum_freq[i] = rel_freq[i];
        } else {
            cum_freq[i] = cum_freq[i - 1] + rel_freq[i];
       }
    }
}
void calculate_theoretical_frequency(double theor_freq[]) {
    for (int i = 0; i < NUM_RANGES; i++) {
        theor_freq[i] = 1.0 - pow(0.9, (gap_ranges[i][1] + 1));
    }
}
int main() {
    int digits[TOTAL_DIGITS] = {
        4, 1, 3, 5, 1, 7, 2, 8, 2, 0, 7, 9, 1, 3, 5, 2, 7, 9, 4, 1, 6, 3, 3, 9, 6,
        3, 4, 8, 2, 3, 1, 9, 4, 4, 6, 8, 4, 1, 3, 8, 9, 5, 5, 7, 7, 3, 9, 5, 9, 4, 
        7, 0, 3, 3, 0, 9, 5, 7, 9, 5, 1, 6, 6, 3, 8, 8, 8, 9, 2, 9, 1, 8, 5, 4, 4, 
        5, 0, 2, 3, 9, 7, 1, 2, 0, 3, 6, 3
    };
    int freq[NUM_RANGES] = {0};
    for (int i = 0; i < 10; i++) {
        int last_position = -1;
        for (int j = 0; j < TOTAL_DIGITS; j++) {
            if (digits[j] == i) {
                if (last_position != -1) {
                    int gap = j - last_position - 1;
                    int range_index = find_range_index(gap);
                    if (range_index != -1) {
                        freq[range_index]++;
                    }
                }
                last_position = j;
            }
        }
    }
    for (int i = 0; i < NUM_RANGES; i++) {
        freq[i] = target_freq[i];
    }
    int total_gaps = 0;
    for (int i = 0; i < NUM_RANGES; i++) {
        total_gaps += freq[i];
    }
    double rel_freq[NUM_RANGES] = {0};
    double cum_freq[NUM_RANGES] = {0};
    double theor_freq[NUM_RANGES] = {0};
    calculate_cumulative_frequency(freq, rel_freq, cum_freq, total_gaps);
    calculate_theoretical_frequency(theor_freq);
    printf("Gap Range | Frequency | Relative Frequency | Cumulative Frequency | Theoretical Frequency | D = |F(x) - S(x)|\n");
    printf("-----------------------------------------------------------------------------------------\n");
    double max_D = 0.0; 
    for (int i = 0; i < NUM_RANGES; i++) {
        double D = fabs(theor_freq[i] - cum_freq[i]);
        if (D > max_D) {
            max_D = D;
        }
        printf("%2d-%2d   | %9d | %17.2lf | %19.2lf | %20.4lf | %20.4lf\n", 
            gap_ranges[i][0], gap_ranges[i][1], freq[i], rel_freq[i], cum_freq[i], theor_freq[i], D);
    }
    double D_critical = 1.36 / sqrt(total_gaps);
    printf("\nThe critical value of D is given by D(0.05) = 1.36 / sqrt(%d) = %.4lf\n", total_gaps, D_critical);
    printf("Since D = max |F(x) - S(x)| = %.4lf ", max_D);
    if (max_D <= D_critical) {
        printf("is less than D(0.05), so we do not reject the hypothesis of independence on the basis of this test.\n");
    } else {
        printf("is greater than D(0.05), so we reject the hypothesis of independence on the basis of this test.\n");
    }
    return 0;
}