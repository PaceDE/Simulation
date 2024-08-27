#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int observed[5];
    double expected[5];
    double calculation[5];
    double final_chi_square;
    double critical_value;
} Chisquare;

void initialize(Chisquare *c) {
    c->final_chi_square = 0.0;
    for (int i = 0; i < 5; i++) {
        c->calculation[i] = 0.0;
    }
}

void getdata(Chisquare *c) {
    int observed[] = {560, 394, 32, 13, 1};
    for (int i = 0; i < 5; i++) {
        c->observed[i] = observed[i];
    }

    double probabilities[] = {0.504, 0.432, 0.027, 0.036, 0.001};

    int total_observations = 1000;
    
    for (int i = 0; i < 5; i++) {
        c->expected[i] = probabilities[i] * total_observations;
    }
}

void calculation(Chisquare *c) {
    for (int i = 0; i < 5; i++) {
        double difference = c->observed[i] - c->expected[i];
        c->calculation[i] = (difference * difference) / c->expected[i];
        c->final_chi_square += c->calculation[i];
    }
}

void display(Chisquare *c) {
    printf("%5s%10s%10s%22s\n", "S.No", "Oi", "Ei", "((Oi-Ei)*(Oi-Ei))/Ei");
    for (int i = 0; i < 5; i++) {
        printf("%5d%10d%10.2f%22.2f\n", i + 1, c->observed[i], c->expected[i], c->calculation[i]);
    }
    printf("-------------------------------------------------------\n");
    printf("Chi-Square Value: %.2f\n", c->final_chi_square);
}

void conclusion(Chisquare *c) {
    printf("\nEnter the critical value:\n");
    scanf("%lf", &c->critical_value);
    if (c->final_chi_square < c->critical_value) {
        printf("The test is accepted\n");
    } else {
        printf("The test is rejected\n");
    }
}

int main() {
    Chisquare c;
    initialize(&c);
    getdata(&c);
    calculation(&c);
    display(&c);
    conclusion(&c);
    return 0;
}