#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int n, observed[20], i, N, Expected;
  float Calculation[20], final, critical;
} Chisquare;

void initialize(Chisquare *c) {
  c->N = 0;
  c->final = 0.00;
}

void getdata(Chisquare *c) {
  printf("How many numbers?:\n");
  scanf("%d", &c->n);
  printf("Enter the observed frequency:\n");
  for (c->i = 0; c->i < c->n; c->i++) {
    scanf("%d", &c->observed[c->i]);
  }
}

void calculation(Chisquare *c)
{
  for (c->i = 0; c->i < c->n; c->i++) {
    c->N += c->observed[c->i];
  }
  c->Expected = c->N / c->n;
  for (c->i = 0; c->i < c->n; c->i++) {
    c->Calculation[c->i] = (float)((c->observed[c->i] - c->Expected) *
                                   (c->observed[c->i] - c -> Expected)) /
                           c->Expected;
    c->final += c->Calculation[c->i];
  }
}

void display(Chisquare *c) {
  printf("%5s%5s%5s%22s\n", "S.No", "Oi", "Ei", "((Oi-Ei)*(Oi-Ei))/Ei");
  for (c->i = 0; c->i < c->n; c->i++) {
    printf("%5d%5d%5d%10.2f\n", c->i + 1, c->observed[c->i], c->Expected,
           c->Calculation[c->i]);
  }
  printf("-------------------------------------------------------\n");
  printf("%10d%15.2f\n", c->N, c->final);
}

void conclusion(Chisquare *c) {
  printf("\nEnter the critical value:\n");
  scanf("%f", &c->critical);
  if (c->final < c->critical)

  {
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